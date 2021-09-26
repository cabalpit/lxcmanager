#include "lxcview.h"

using namespace businesslayer;

LxcView::LxcView(QWidget *parent) : QTableView(parent)
{
	m_containers = nullptr;
	initObjects();
	initConnections();
	populateModel();

	horizontalHeader()->setVisible(false);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setStyleSheet(m_css["table"]);
}

LxcView::~LxcView()
{
	if(m_containers)
		delete m_containers;

	delete m_lxc;
	delete m_config;
}

void LxcView::populateModel(bool populate)
{
	if(!populate)
		return;

	if(m_containers)
	{
		delete m_containers;
		m_containers = NULL;
	}

	m_model.clear();
	m_containers = m_lxc->allContainersList();
	int allCount = m_lxc->lxcCountAll();

	for (int i = 0; i < allCount; i++)
	{
		QList<QStandardItem *> items;
		items.append(new QStandardItem(m_containers[i]->name));

		const char *state = m_containers[i]->state(m_containers[i]);

		items.append(new QStandardItem(state));

		// get all ips
		if(qstrcmp(state, "RUNNING") == 0)
		{
			QStringList ipsList = QStringList();

			char **interfaces = m_containers[i]->get_interfaces(m_containers[i]);

			if(interfaces != nullptr)
			{
				for(int j = 0; interfaces[j] != nullptr; j++)
				{
					char *interface = interfaces[j];
					char **ips = m_containers[i]->get_ips(m_containers[i], interface, "inet", 0);

					if(ips != nullptr)
					{
						for(int k = 0; ips[k] != nullptr; k++)
						{
							if(qstrcmp(ips[k], "127.0.0.1") != 0)
								ipsList.append(ips[k]);
						}
					}
				}
			}

			if(!ipsList.empty())
			{
				items.append(new QStandardItem(ipsList.join(";")));
			}
			else
			{
				items.append(new QStandardItem("-"));
			}
		}
		else
		{
			items.append(new QStandardItem("-"));
		}


		QIcon playPause = qstrcmp(state, "RUNNING") == 0 ? QIcon(":/icons/stop_black") : QIcon(":/icons/play_black");
		items.append(new QStandardItem(playPause, QString()));

		m_model.appendRow(items);
	}
}

void LxcView::createContainer(const QMap<QString, QString> &container)
{
	Container c = {
		.name = container.value("name").toLatin1().data(),
		.distribution = container.value("distribution").toLatin1().data(),
		.release = container.value("release").toLatin1().data(),
		.arch = container.value("architecture").toLatin1().data(),
		.variant = container.value("variant").toLatin1().data(),
		.hkp = m_config->find("hkp").toLatin1().data()
	};

	//check if container name exists
	bool found = false;

	if(m_containers)
	{
		for (int i = 0; m_containers[i] != NULL && found; i++)
		{
			if(m_containers[i])
			{
				if(qstrcmp(m_containers[i]->name, container.value("name").toLatin1().data()) == 0)
					found = true;
			}
		}
	}

	qDebug() << c.hkp;

	if(!found)
	{
		// m_lxc->createContainer(c);
	}
	else
	{
		emit lxcCreated(false, tr("Name Already exists"));
	}
}


void LxcView::initObjects()
{
	m_lxc = new LxcContainer(this);
	m_config = new ConfigFile;

	setModel(&m_model);
	m_model.clear();
}

void LxcView::initConnections()
{
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStart);
	connect(m_lxc, &LxcContainer::containerStopped, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerCreated, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerCreated, this, &LxcView::messageCreate);
}


void LxcView::paintEvent(QPaintEvent *event)
{
	int headerWidth = verticalHeader()->geometry().width();
	int width = (geometry().width() - (28 + headerWidth)) / 3;

	setColumnWidth(0, width);
	setColumnWidth(1, width);
	setColumnWidth(2, width);
	setColumnWidth(3, 28);

	QTableView::paintEvent(event);
}

void LxcView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
	if(current.column() == 3)
	{
		QStandardItem *item = m_model.item(current.row(), 1);

		if(item->data(Qt::DisplayRole) == "RUNNING")
			m_lxc->stop(m_containers[current.row()]);

		else
			m_lxc->start(m_containers[current.row()]);
	}

	QTableView::currentChanged(current, previous);
}

void LxcView::messageStart(bool success)
{
	if(!success)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc start Failed"), tr("Failed to start container please try again"));
	}
}

void LxcView::messageCreate(bool success)
{
	if(!success)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc Create Failed"), tr("Failed to create container please try again"));
	}

	emit lxcCreated(success);
}




