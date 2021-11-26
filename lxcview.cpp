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
	setAlternatingRowColors(true);
	setWordWrap(true);
	setShowGrid(false);
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

		QString state = m_containers[i]->state(m_containers[i]);

		items.append(new QStandardItem(state));

		// get all ips
		if(state == "RUNNING"  || state == "FROZEN")
		{
			QStringList *ipslist = ips(m_containers[i]);
			items.append(new QStandardItem(ipslist->isEmpty() ? "-" : ipslist->join("; ")));
			delete ipslist;
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

		/// using delegate for painting the values \see businesslayer::ImageDelegate
		int value = (state == "RUNNING");
		items.append(new QStandardItem(QString::number(value)));							//play pause column
		items.append(new QStandardItem(QString::number(0)));								// stop column
		items.append(new QStandardItem(QString::number(0)));								// snapshot column

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
	m_lxc = new LxcContainer(m_config->find("lxcpath", QDir::homePath() + "/.local/share/lxc").toByteArray().data(), this);

	setItemDelegate(new ImageDelegate(this));

	m_model.clear();
	setModel(&m_model);
	verticalHeader()->setDefaultSectionSize(45);
}

/*!
 * \brief LxcView::initConnections
 *
 * This method connect the objects.
 */
void LxcView::initConnections()
{
	connect(m_lxc, &LxcContainer::containerStarted, this, &LxcView::messageStart);
	connect(m_lxc, &LxcContainer::containerStopped, this, &LxcView::messageStop);
	connect(m_lxc, &LxcContainer::containerFreezed, this, &LxcView::messageFreeze);
	connect(m_lxc, &LxcContainer::containerUnfreezed, this, &LxcView::messageUnFreeze);
	connect(m_lxc, &LxcContainer::containerSnapshoted, this, &LxcView::messageSnapshot);
	connect(this, &QTableView::clicked, this, &LxcView::changes);
}

/*!
 * \brief LxcView::updateContainer
 *
 * This method updates container to view.
 * \param name waits the name to search and update.
 */
void LxcView::updateContainer(const QString &name)
{
	int idx = m_lxc->containerExists(name.toLatin1().data());

	if(idx < 0)
		return;

	QString state = m_containers[idx]->state(m_containers[idx]);

	m_model.item(idx, 1)->setData(QVariant(state), Qt::DisplayRole);

	if(state != "STOPPED")
	{
		QStringList *ipslist = ips(m_containers[idx]);
		m_model.item(idx, 2)->setData(ipslist->empty() ? "-" : ipslist->join("; "), Qt::DisplayRole);
	}
	else
		m_model.item(idx, 2)->setData("-", Qt::DisplayRole);

	m_model.item(idx, 4)->setData(QVariant((int)(state == "RUNNING")), Qt::DisplayRole);
	m_model.item(idx, 5)->setData(QVariant(0), Qt::DisplayRole);
	m_model.item(idx, 6)->setData(QVariant(0), Qt::DisplayRole);
}

/*!
 * \brief LxcView::ips
 *
 * This method retrieves all ips of running container.
 *
 * \param c waits running container
 * \return an ips list if exists otherwize empty list.
 */
QStringList *LxcView::ips(lxc_container *c)
{
	QStringList *ipslist = new QStringList;

	char **interfaces = c->get_interfaces(c);

	if(interfaces != nullptr)
	{
		for(int j = 0; interfaces[j] != nullptr; j++)
		{
			char **ips = c->get_ips(c, interfaces[j], "inet", 0);

			if(ips != nullptr)
			{
				for(int k = 0; ips[k] != nullptr; k++)
				{
					if(qstrcmp(ips[k], "127.0.0.1") != 0)
						*ipslist << (const char *)ips[k];

					delete [] ips[k];
					ips[k] = nullptr;
				}

				delete [] ips;
			}

			delete [] interfaces[j];
		}

		delete [] interfaces;
	}

	return ipslist;
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
void LxcView::messageStart(bool status, const QString &name)
{
	if(!status)
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc start Failed"), tr("Failed to start container please try again"));

	if(!name.isNull() && !name.isEmpty())
		updateContainer(name);

	emit containerStarted(status);
}

/*!
 * \brief LxcView::messageStop
 *
 * This method displays \c QMessage box in case of failure to stop a container.
 *
 * \param status waits \c false to display the message/
 */
void LxcView::messageStop(bool status, const QString &name)
{
	if(!status)
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc stop failed"), tr("Failed to stop container please try again"));

	if(!name.isNull() && !name.isEmpty())
		updateContainer(name);

	emit containerStopped(status);
}

/*!
 * \brief LxcView::messageFreeze
 *
 * This method shows up message box if freeze container failed
 *
 * \param status \c false displays message
 */
void LxcView::messageFreeze(bool status, const QString &name)
{
	if(!status)
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc freeze failed"), tr("Failed to freeze container please try again"));

	if(!name.isNull() && !name.isEmpty())
		updateContainer(name);
}

/*!
 * \brief LxcView::messageUnFreeze
 *
 * This method shows up message box if freeze container failed
 *
 * \param status \c false displays message
 */
void LxcView::messageUnFreeze(bool status, const QString &name)
{
	if(!status)
		QMessageBox::warning(qobject_cast<QWidget *>(parent()), tr("Lxc unfreeze failed"), tr("Failed to unfreeze container please try again"));

	if(!name.isNull() && !name.isEmpty())
		updateContainer(name);
}

/*!
 * \brief LxcView::messageSnapshot
 *
 * This method displays \c QMessage box for the snapshot state.
 *
 * \param status \c true will displays success message box, \c false to display danger message box.
 */
void LxcView::messageSnapshot(bool status, const QString &name)
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

	int idx = m_lxc->containerExists(name.toLatin1().data());
	m_model.item(idx, 6)->setData(QVariant(0), Qt::DisplayRole);
}

/*!
 * \brief LxcView::changes
 * \param index
 */
void LxcView::changes(const QModelIndex &index)
{
	QString status = m_model.item(index.row(), 1)->data(Qt::DisplayRole).toString();
	QStandardItem *value = m_model.item(index.row(), index.column());

	if(index.column() < 3)
		return;

	if(index.column() == 3)
	{
		bool autostart = m_lxc->isStartauto(m_containers[index.row()]);

		QStandardItem *itemAutostart = m_model.item(index.row(), 3);
		itemAutostart->setCheckState(!autostart ? Qt::Checked : Qt::Unchecked);

		m_lxc->setStartauto(m_containers[index.row()], !autostart);
	}

	if(index.column() == 4 && value->data().toInt() != 2)
	{
		value->setData(QVariant(2), Qt::DisplayRole);

		if(status == "STOPPED")
		{
			m_lxc->start(m_containers[index.row()]);
		}
		else if(status == "RUNNING")
		{
			m_lxc->freeze(m_containers[index.row()]);
		}
		else if(status == "FROZEN")
		{
			m_lxc->unfreeze(m_containers[index.row()]);
		}
	}
	else if(index.column() == 5 && value->data().toInt() != 2)
	{
		if(status != "STOPPED")
		{
			value->setData(QVariant(2), Qt::DisplayRole);
			m_lxc->stop(m_containers[index.row()]);
		}
	}
	else if(index.column() == 6 && value->data().toInt() != 2)
	{
		QString comment = QInputDialog::getMultiLineText(qobject_cast<QWidget *>(parent()), tr("Lxc Snapshot Comment"), tr("Create Comment for this snapshot:"));

		if(!comment.isEmpty())
		{
			value->setData(QVariant(2), Qt::DisplayRole);
			m_lxc->snapshot(m_containers[index.row()], m_config->find("snapcommentfolder", QDir::homePath() + "/Snaps").toByteArray().data(), comment.toLatin1().data());
		}
	}
}

