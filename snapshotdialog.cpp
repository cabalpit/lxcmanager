#include "snapshotdialog.h"

using namespace businesslayer;

/*!
 * \fn SnapshotDialog::SnapshotDialog
 * \brief SnapshotDialog::SnapshotDialog
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param type waits \c SnapType to display the right ui, and connect the right method.
 * \param parent waits parent widget, default \a nullptr
 */
SnapshotDialog::SnapshotDialog(SnapType type, QWidget *parent): QDialog(parent)
{
	m_type = type;
	initObejcts();
	initDisposal();
	initConnections();

	switch (m_type)
	{
		case RESTORE:
			setWindowTitle(tr("Restore Snapshot"));
		break;

		case REMOVE:
			setWindowTitle(tr("Destroy Snapshot"));
		break;
	}
}

/*!
 * \fn SnapshotDialog::~SnapshotDialog
 * \brief SnapshotDialog::~SnapshotDialog
 *
 * Default destructor
 */
SnapshotDialog::~SnapshotDialog()
{
	delete m_alert;
	delete m_titleLabel;
	delete m_containerLabel;
	delete m_snapLabel;

	delete m_containersCombo;
	delete m_snapshotView;

	if(m_nameLabel)
		delete m_nameLabel;

	if(m_nameLineEdit)
		delete m_nameLineEdit;

	delete m_cancel;
	delete m_save;

	delete m_lxc;

	if(m_containers)
	{
		for (int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
		m_containers = nullptr;
	}

	delete m_loader;

	delete m_layout;
}

/*!
 * \fn SnapshotDialog::updateContainers
 * \brief SnapshotDialog::updateContainers
 *
 * This method update containers list to display.
 *
 * \param populate waits true to populate.
 */
void SnapshotDialog::updateContainers(bool populate)
{
	if(!populate)
		return;

	disconnect(m_containersCombo, &QComboBox::currentIndexChanged, this, &SnapshotDialog::populateSnapshotView);

	if(m_containers)
	{
		for (int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
	}

	clearAll();
	m_containersCombo->clear();

	m_containersCount = m_lxc->lxcCountAll();
	m_containers = m_lxc->allContainersList();

	if(m_containers)
	{
		m_containersCombo->addItem(tr("Select a container ..."));

		for (int i = 0; i < m_containersCount; i++)
		{
			lxc_snapshot *snapshot = nullptr;
			int snapCount = m_containers[i]->snapshot_list(m_containers[i], &snapshot);

			if(snapCount)
			{
				m_containersCombo->addItem(m_containers[i]->name, i);
				delete [] snapshot;
			}
		}
	}

	connect(m_containersCombo, &QComboBox::currentIndexChanged, this, &SnapshotDialog::populateSnapshotView);
}

/*!
 * \fn SnapshotDialog::showAlert
 * \brief SnapshotDialog::showAlert display alert message.
 *
 * This method displays an \c Alert object. The \a message it will be display.
 * Two alert are possible success or danger alert.
 *
 * \param status true for success alert, false for danger alert
 * \param message waits the text to display
 */
void SnapshotDialog::showAlert(bool status, const QString &message)
{
	clear();

	if(status)
		m_alert->success(message);

	else
		m_alert->danger(message);
}

/*!
 * \fn SnapshotDialog::initObejcts
 * \brief SnapshotDialog::initObejcts initialize objects.
 *
 * This method creates all objects of this class.
 */
void SnapshotDialog::initObejcts()
{
	m_holdCurrentData = -1;
	m_lxc = new LxcContainer((new ConfigFile)->find("lxcpath", QDir::homePath() + "/.local/share/lxc").toLatin1().data(), this);
	m_containers = nullptr;
	m_containersCount = 0;

	m_layout = new QGridLayout(this);

	m_alert = new Alert(this);
	m_alert->setMinimumHeight(45);

	QString title = m_type == RESTORE ? tr("Restore containers from a snapshot") : tr("Remove Snapshots cannot be undone!");
	m_titleLabel = new QLabel(title, this);

	m_containerLabel = new QLabel(tr("Containers with snapshot:"), this);

	QString snapText = m_type == RESTORE ? tr("Select a snapshot to restore:") : tr("Select a snapshot to destroy:");
	m_snapLabel = new QLabel(snapText, this);


	m_containersCombo = new QComboBox(this);
	m_containersCombo->setFixedWidth(250);

	m_model.clear();
	m_snapshotView= new QListView(this);
	m_snapshotView->setAutoScroll(true);
	m_snapshotView->setDragDropMode(QAbstractItemView::NoDragDrop);
	m_snapshotView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_snapshotView->setModel(&m_model);

	if(m_type == RESTORE)
	{
		m_nameLabel = new QLabel(tr("New name (optional):"), this);
		m_nameLineEdit = new QLineEdit(this);
	}
	else
	{
		m_nameLabel = nullptr;
		m_nameLineEdit = nullptr;
	}

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	QString saveText = m_type == RESTORE ? tr("Restore") : tr("Remove");
	m_save = new QPushButton(saveText, this);
	m_save->setStyleSheet(m_css["primary-button"]);

	m_loader = new Loader;
	m_loader->setColor(QColor(95, 158, 160));
	m_loader->setArcRect(QRectF(-12, -12, 24, 24));

	updateContainers(true);
}

/*!
 * \fn SnapshotDialog::initDisposal
 * \brief SnapshotDialog::initDisposal arrange object into layer
 *
 * This method disposes the object into layer.
 */
void SnapshotDialog::initDisposal()
{
	m_layout->addWidget(m_titleLabel, 0, 0, 1, 4);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 0, 1, 4);
	m_layout->addWidget(m_alert, 2, 0, 1, 4);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 3, 0, 1, 4);

	m_layout->addWidget(m_containerLabel, 4, 0, 1, 2);
	m_layout->addWidget(m_snapLabel, 4, 2, 1, 2);
	m_layout->addWidget(m_containersCombo, 5, 0, 1, 2, Qt::AlignTop);
	m_layout->addWidget(m_snapshotView, 5, 2, 1, 2);

	if(m_type == RESTORE)
	{
		m_layout->addWidget(m_nameLabel, 6, 0, 1, 2, Qt::AlignRight);
		m_layout->addWidget(m_nameLineEdit, 6, 2, 1, 2);
	}

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 7, 0, 1, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 7, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 7, 3);

	m_layout->addWidget(m_cancel, 8, 2);
	m_layout->addWidget(m_save, 8, 3);

	setStyleSheet(m_css["body"]);
	setFixedSize(570, 410);
	setLayout(m_layout);
}

/*!
 * \brief SnapshotDialog::initConnection
 *
 * This method connect the objects.
 */
void SnapshotDialog::initConnections()
{
	connect(m_loader, &Loader::timerChanged, this, QOverload<>::of(&SnapshotDialog::update));
	connect(m_cancel, &QPushButton::clicked, this, &SnapshotDialog::cancelClick);
	connect(m_save, &QPushButton::clicked, this, &SnapshotDialog::save);

	switch (m_type)
	{
		case RESTORE:
			connect(m_lxc, &LxcContainer::containerRestrored, this, [=] (bool status, const QString &message) { showAlert(status, message); emit snapshotRestored(status); });
		break;

		case REMOVE:
			connect(m_lxc, &LxcContainer::containerSnapshotDestroyed, this, [=](bool status, const QString &message) { updateAfterRemoved(); showAlert(status, message); });
		break;

		default:
		break;
	}
}

/*!
 * \fn SnapshotDialog::paintEvent
 * \brief SnapshotDialog::paintEvent paint loader
 *
 * Override \c QDialog::paintEvent method, it paint the loader when loading attribute is set to true,
 * otherwize if loading attribute is false, the loader will be not paint.
 *
 * \param event received from \a event.
 */
void SnapshotDialog::paintEvent(QPaintEvent *event)
{
	if(m_loader->isLoading())
	{
		QPainter *painter = new QPainter(this);
		painter->setRenderHints(QPainter::Antialiasing);

		painter->save();

		QPointF pos(m_save->geometry().center().rx(), m_save->geometry().center().ry());
		m_loader->spinner(painter, pos);

		painter->restore();
		painter->end();
		delete painter;
	}

	QDialog::paintEvent(event);
}

/*!
 * \fn SnapshotDialog::closeEvent
 * \brief SnapshotDialog::closeEvent prevent close event
 *
 * Override method, the method clears the items before to close.
 * If loader is going the \a close event will be ignored.
 *
 * \param event received from \a event
 */
void SnapshotDialog::closeEvent(QCloseEvent *event)
{
	if(m_loader->isLoading())
	{
		event->ignore();
		return;
	}

	clearAll();
	QDialog::closeEvent(event);
}

/*!
 * \fn SnapshotDialog::populateSnapshotView
 * \brief SnapshotDialog::populateSnapshotView populate \a snapshotView
 *
 * This method poppulate the view with snapshot list. If no container selected,
 * the method will not populate the \c model object.
 */
void SnapshotDialog::populateSnapshotView()
{
	m_model.clear();

	if(!m_containersCombo->currentIndex())
		return;

	int idx = m_containersCombo->currentData().toInt();

	lxc_snapshot *snapshots = nullptr;
	int count = m_containers[idx]->snapshot_list(m_containers[idx], &snapshots);

	if(count && snapshots)
	{
		QList<QStandardItem *>items;

		for(int i = 0; i < count; i++)
		{
			QString name = QString("%1\t%2").arg(snapshots[i].name, snapshots[i].timestamp);
			items.append(new QStandardItem(QIcon(":/icons/image_black"), name));
		}
		m_model.appendColumn(items);
		delete [] snapshots;
	}
	else
		m_alert->information(tr("This container does not contains snapshot!"));
}

/*!
 * \fn SnapshotDialog::save
 * \brief SnapshotDialog::save exectute lxc method.
 *
 * This method restore or delete a snapshot, depending of selected type.
 * If selected type is \a RESTORE the \c SnapshotDialog::save will trigger \a restoresnapshot,
 * otherwize if \a REMOVE the \c SnapshotDialog::save will trigger \a removesnapshot.
 */
void SnapshotDialog::save()
{
	m_alert->clean();

	int idxC = !m_containersCombo->currentIndex() ? -1 : m_containersCombo->currentData().toInt();
	int idxS = m_snapshotView->currentIndex().row();

	if(idxC < 0 || idxS < 0)
	{
		m_alert->information(tr("Please select a container and snapshot first!"));
		return;
	}

	switch (m_type)
	{
		case RESTORE:
		{
			QString newName = m_nameLineEdit->text().trimmed();
			QRegularExpression regex("[\\s!@#$%^&*()+=\\\\\\/?<>,.]+");

			if(!newName.isEmpty() && newName.contains(regex))
			{
				m_alert->information(tr("The container name format does not allow the following spaces or special characters '@#$%^&*()+=\\/?<>,.!'"));

				return;
			}

			m_loader->start();
			m_save->setVisible(false);
			m_lxc->restoreSnapshot(m_containers[idxC], idxS, newName.toLatin1().data());
		}
		break;

		case REMOVE:
		{
			m_loader->start();
			m_save->setVisible(false);
			m_holdCurrentData = idxC;
			m_lxc->destroySnapshot(m_containers[idxC], idxS);
		}
		break;
	}
}

/*!
 * \fn SnapshotDialog::updateAfterRemoved
 * \brief SnapshotDialog::updateAfterRemoved update view or combobox after remove snapshot.
 *
 * This method update \a snapshotView after snapshot destroyed.
 *
 * \note The \a snapshotView will be update only if the \a containerCombobox \c currentIndex is equale to \a holdCurrentIndex
 * and if the container still contains snapshot(s). Otherwize the method will update \a containerCombobox
 */
void SnapshotDialog::updateAfterRemoved()
{
	int idx = m_containersCombo->currentData().toInt();

	if(idx < 0 && idx != m_holdCurrentData)
	{
		clearAll();
		updateContainers(true);
		return;
	}

	lxc_snapshot *snapshots = nullptr;
	int count = m_containers[idx]->snapshot_list(m_containers[idx], &snapshots);

	if(!count)
		updateContainers(true);

	else
	{
		populateSnapshotView();
		delete [] snapshots;
	}
}

/*!
 * \fn SnapshotDialog::cancelClick
 * \brief SnapshotDialog::cancelClick cancel trigger.
 *
 * This method is fiered up when the cancel button is clicked.
 */
void SnapshotDialog::cancelClick()
{
	if(m_loader->isLoading())
		return;

	clearAll();
}

/*!
 * \fn SnapshotDialog::clear
 * \brief SnapshotDialog::clear clears items
 *
 * This method clears nameEdit, alert, and stop loader.
 */
void SnapshotDialog::clear()
{
	if(m_type == RESTORE)
		m_nameLineEdit->clear();

	m_loader->stop();
	m_save->setVisible(true);
	m_alert->clean();
}

/*!
 * \fn SnapshotDialog::clearAll
 * \brief SnapshotDialog::clearAll resets all items.
 *
 * This method clears nameEdit, model, alert, stop loader, and make combo index to 0.
 */
void SnapshotDialog::clearAll()
{
	if(m_type == RESTORE)
		m_nameLineEdit->clear();

	m_loader->stop();
	m_save->setVisible(true);
	m_containersCombo->setCurrentIndex(0);
	m_model.clear();
	m_alert->clean();
}

