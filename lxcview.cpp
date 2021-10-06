#include "lxcview.h"

using namespace businesslayer;

/*!
 * \brief LxcView::LxcView
 *
 * Construct a \c LxcView object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
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

/*!
 * \brief LxcView::~LxcView
 *
 * Default destructor
 */
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

/*!
 * \brief LxcView::populateModel
 *
 * This method fills model with containers list.
 *
 * \param populate if \a true the model will be \a populate.
 */
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
		if(qstrcmp(state, "RUNNING") == 0 || qstrcmp(state, "FROZEN") == 0)
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

//		QIcon playPause = (!qstrcmp(state, "FROZEN") || !qstrcmp(state, "STOPPED"))? QIcon(":/icons/play_black") : QIcon(":/icons/pause_black");
//		items.append(new QStandardItem(playPause, QString()));

//		items.append(new QStandardItem(QIcon(":icons/stop_black"), QString()));
//		items.append(new QStandardItem(QIcon(":icons/snapshot_black"), QString()));

		/// new using delegate for painting
		int value = (int) !qstrcmp(state, "RUNNING");
		items.append(new QStandardItem(QString::number(value)));
		items.append(new QStandardItem(QString::number(0)));

		m_model.appendRow(items);
	}
}

/*!
 * \brief LxcView::initObjects
 *
 * This method creates all objects of this class.
 */
void LxcView::initObjects()
{
	m_containers = nullptr;
	m_allCount = 0;

	m_config = new ConfigFile;
	m_lxc = new LxcContainer(m_config->find("lxcpath", QDir::homePath() + "/.local/share/lxc").toLatin1().data(), this);

	setItemDelegate(new ImageDelegate(this));
	setModel(&m_model);
	m_model.clear();

	setFixedHeight(395);
}

/*!
 * \brief LxcView::initConnections
 *
 * This method connect the objects.
 */
void LxcView::initConnections()
{
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStart);

	connect(m_lxc, &LxcContainer::containerStopped, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStop);

	connect(m_lxc, &LxcContainer::containerFreezed, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerFreezed, this, &LxcView::messageFreeze);

	connect(m_lxc, &LxcContainer::containerUnfreezed, this, &LxcView::populateModel);
	connect(m_lxc, &LxcContainer::containerUnfreezed, this, &LxcView::messageUnFreeze);

	connect(m_lxc, &LxcContainer::containerSnapshoted, this, &LxcView::messageSnapshot);
	connect(this, &QTableView::clicked, this, &LxcView::changes);
}

/*!
 * \brief RemoveSnapDialog::paintEvent
 *
 * Override method it resizes column on event resize.
 *
 * \param event received from \a event.
 */
void LxcView::resizeEvent(QResizeEvent *event)
{
	int headerWidth = verticalHeader()->geometry().width();
	int width = (geometry().width() - (32 * 3 + headerWidth)) / 4;

	setColumnWidth(0, width);
	setColumnWidth(1, width);
	setColumnWidth(2, width);
	setColumnWidth(3, width);
	setColumnWidth(4, 32);
	setColumnWidth(5, 32);
	setColumnWidth(6, 32);

	QTableView::resizeEvent(event);
}

/*!
 * \brief LxcView::messageStart
 *
 * This method displays \c QMessage box in case of failure to start a container.
 *
 * \param status waits \c false to display the message/
 */
void LxcView::messageStart(bool status)
{
	if(!status)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc start Failed"), tr("Failed to start container please try again"));
	}
}

/*!
 * \brief LxcView::messageStop
 *
 * This method displays \c QMessage box in case of failure to stop a container.
 *
 * \param status waits \c false to display the message/
 */
void LxcView::messageStop(bool status)
{
	if(!status)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc stop failed"), tr("Failed to stop container please try again"));
	}
}

/*!
 * \brief LxcView::messageSnapshot
 *
 * This method displays \c QMessage box for the snapshot state.
 *
 * \param status \c true will displays success message box, \c false to display danger message box.
 */
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

/*!
 * \brief LxcView::messageFreeze
 *
 * This method shows up message box if freeze container failed
 *
 * \param status \c false displays message
 */
void LxcView::messageFreeze(bool status)
{
	if(!status)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc freeze failed"), tr("Failed to freeze container please try again"));
	}
}

/*!
 * \brief LxcView::messageUnFreeze
 *
 * This method shows up message box if freeze container failed
 *
 * \param status \c false displays message
 */
void LxcView::messageUnFreeze(bool status)
{
	if(!status)
	{
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc unfreeze failed"), tr("Failed to unfreeze container please try again"));
	}
}

/*!
 * \brief LxcView::changes
 * \param index
 */
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
		QString status = m_model.item(index.row(), 1)->data(Qt::DisplayRole).toString();
		QStandardItem *value = m_model.item(index.row(), index.column());
		value->setData(QVariant(2), Qt::DisplayRole);


		if(status == "RUNNING")
			m_lxc->stop(m_containers[index.row()]);

		else
			m_lxc->start(m_containers[index.row()]);

	}
	else if(index.column() == 5)
	{
		QStandardItem *item = m_model.item(index.row(), 1);

		if(item->data(Qt::DisplayRole) != "STOPPED")
			m_lxc->stop(m_containers[index.row()]);
	}
	else if(index.column() == 6)
	{
		QString comment = QInputDialog::getMultiLineText(qobject_cast<QWidget *>(parent()), tr("Lxc Snapshot Comment"), tr("Create Comment for this snapshot:"));

		if(!comment.isEmpty())
			m_lxc->snapshot(m_containers[index.row()], m_config->find("snapcommentfolder", QDir::homePath() + "/Snaps").toLatin1().data(), comment.toLatin1().data());
	}
}

