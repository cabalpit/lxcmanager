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

		bool checked = m_lxc->isStartauto(m_containers[i]);
		QStandardItem *startauto = new QStandardItem(tr("autostart"));
		startauto->setCheckable(true);
		startauto->setCheckState(checked ? Qt::Checked : Qt::Unchecked);

		items.append(startauto);

		QIcon playPause = qstrcmp(state, "RUNNING") == 0 ? QIcon(":/icons/stop_black") : QIcon(":/icons/play_black");
		items.append(new QStandardItem(playPause, QString()));

		items.append(new QStandardItem(QIcon(":icons/snapshot_black"), QString()));

		m_model.appendRow(items);
	}
}

void LxcView::initObjects()
{
	m_containers = nullptr;
	m_allCount = 0;

	m_config = new ConfigFile;
	m_lxc = new LxcContainer(m_config->find("lxcpath", QDir::homePath() + "/.local/share/lxc").toLatin1().data(), this);

	setModel(&m_model);
	m_model.clear();

	setFixedHeight(395);
}

void LxcView::initConnections()
{
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStart);

	connect(m_lxc, &LxcContainer::containerStopped, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStop);

	connect(m_lxc, &LxcContainer::containerSnapshoted, this, &LxcView::messageSnapshot);
	connect(this, &QTableView::clicked, this, &LxcView::changes);
}


void LxcView::paintEvent(QPaintEvent *event)
{
	int headerWidth = verticalHeader()->geometry().width();
	int width = (geometry().width() - (56 + headerWidth)) / 4;


	setColumnWidth(0, width);
	setColumnWidth(1, width);
	setColumnWidth(2, width);
	setColumnWidth(3, width);
	setColumnWidth(4, 28);
	setColumnWidth(5, 28);

	QTableView::paintEvent(event);
}

void LxcView::messageStart(bool status)
{
	if(!status)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc start Failed"), tr("Failed to start container please try again"));
	}
}

void LxcView::messageStop(bool status)
{
	if(!status)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc stop failed"), tr("Failed to stop container please try again"));
	}
}

void LxcView::messageSnapshot(bool status)
{
	if(status)
	{
		QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Lxc snapshoted"), tr("Snapshot created with success"));
		emit snapshotCreated(true);
	}
	else
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc snapshot failed"), tr("Failed to create snapshot please try again later!"));
	}
}

void LxcView::changes(const QModelIndex &index)
{
	if(index.column() < 3)
		return;

	if(index.column() == 3)
	{
		bool autostart = m_lxc->isStartauto(m_containers[index.row()]);

		QStandardItem *itemAutostart = m_model.item(index.row(), 3);
		itemAutostart->setCheckState(!autostart ? Qt::Checked : Qt::Unchecked);

		m_lxc->setStartauto(m_containers[index.row()], !autostart);
	}
	else if(index.column() == 4)
	{
		QStandardItem *item = m_model.item(index.row(), 1);

		if(item->data(Qt::DisplayRole) == "RUNNING")
			m_lxc->stop(m_containers[index.row()]);

		else
			m_lxc->start(m_containers[index.row()]);
	}
	else if(index.column() == 5)
	{
		QString comment = QInputDialog::getMultiLineText(qobject_cast<QWidget *>(parent()), tr("Lxc Snapshot Comment"), tr("Create Comment for this snapshot:"));

		if(!comment.isEmpty())
			m_lxc->snapshot(m_containers[index.row()], m_config->find("snapcommentfolder", QDir::homePath() + "/Snaps").toLatin1().data(), comment.toLatin1().data());
	}
}

