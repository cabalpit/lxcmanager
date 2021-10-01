#include "lxcview.h"

using namespace businesslayer;

LxcView::LxcView(QWidget *parent) : QTableView(parent)
{
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
	{
		for (int i = 0; i < m_allCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = NULL;
		}

		delete [] m_containers;
	}
	delete m_lxc;
	delete m_config;
}

void LxcView::populateModel(bool populate)
{
	if(!populate)
		return;

	if(m_containers)
	{
		for (int i = 0; i < 2; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = NULL;
		}

		delete [] m_containers;
		m_containers = NULL;
	}

	m_model.clear();
	m_containers = m_lxc->allContainersList();
	m_allCount = m_lxc->lxcCountAll();

	for (int i = 0; i < m_allCount; i++)
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

		items.append(new QStandardItem(QIcon(":icons/snapshot_black"), QString()));

		m_model.appendRow(items);
	}

	/*
	 * Avoid losing emit on start application.
	 * I don't know why on start application the slot is not ready and emit is lost.
	 */
	QTimer::singleShot(1000, this, [=] { emit populateChanged(m_model); });
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
	bool exists = false;

	if(m_containers)
	{
		for (int i = 0; i < m_lxc->lxcCountAll() && !exists; i++)
		{
			if(m_containers[i] && m_containers[i]->name)
			{
				if(qstrcmp(m_containers[i]->name, container.value("name").toLatin1().data()) == 0)
					exists = true;
			}
		}
	}


	if(exists)
		emit lxcCreated(false, tr("Name Already exists"));

	else
		m_lxc->createContainer(c);
}

void LxcView::cloneContainer(const int idx, const QString &name, const int cloneType)
{
	m_lxc->clone(m_containers[idx], const_cast<char *>(name.toLatin1().data()), cloneType);
}

void LxcView::destroyContainer(int idx)
{
	 m_lxc->destroy(m_containers[idx]);
}

void LxcView::initObjects()
{
	m_containers = nullptr;
	m_allCount = 0;

	m_lxc = new LxcContainer(this);
	m_config = new ConfigFile;

	setModel(&m_model);
	m_model.clear();

	setFixedHeight(395);
}

void LxcView::initConnections()
{
	connect(m_lxc, &LxcContainer::containerCreated, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerCreated, this, &LxcView::messageCreate);

	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStart);

	connect(m_lxc, &LxcContainer::containerStopped, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStop);

	connect(m_lxc, &LxcContainer::containerCloned, this, &LxcView::messageClone);
	connect(m_lxc, &LxcContainer::containerCloned, this, &LxcView::populateModel);

	connect(m_lxc, &LxcContainer::containerDestroyed, this, &LxcView::messageDestroy);
	connect(m_lxc, &LxcContainer::containerDestroyed, this, &LxcView::populateModel);

	connect(m_lxc, &LxcContainer::containerSnapshoted, this, &LxcView::messageSnapshot);
	connect(m_lxc, &LxcContainer::containerSnapshoted, this, &LxcView::populateModel);
}


void LxcView::paintEvent(QPaintEvent *event)
{
	int headerWidth = verticalHeader()->geometry().width();
	int width = (geometry().width() - (56 + headerWidth)) / 3;

	setColumnWidth(0, width);
	setColumnWidth(1, width);
	setColumnWidth(2, width);
	setColumnWidth(3, 28);
	setColumnWidth(4, 28);

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
	else if(current.column() == 4)
	{
		bool ok;
		QString comment = QInputDialog::getMultiLineText(qobject_cast<QWidget *>(parent()), tr("Snapshot Comment"), tr("Provide Snapshot comment:"), QString(), &ok);

		if(ok)
		{
			QString snapCommentFolder = m_config->find("snapcommentfolder", QDir::homePath() + "/Snaps");
			m_lxc->snapshot(m_containers[current.row()], snapCommentFolder.toLatin1().data(), comment.toLatin1().data());
		}
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

void LxcView::messageStop(bool success)
{
	if(!success)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc stop failed"), tr("Failed to stop container please try again"));
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

void LxcView::messageClone(bool success)
{
	QString message;
	message = (success ? tr("Newly-allocated copy of container success") : tr("Newly-allocated copy of container failed"));

	emit lxcCloned(success, message);
}

void LxcView::messageDestroy(bool success)
{
	QString message;
	message = (success ? tr("Container removed and destroy with success") : tr("Container Cannot be destroy"));

	emit lxcDestroyed(success, message);
}

void LxcView::messageSnapshot(bool success)
{
	QString message = success ? tr("Snapshot done with success.") : tr("Snapshot failed please try again later.");
	QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Snapshot"), message);
}
