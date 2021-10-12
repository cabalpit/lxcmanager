#include "removerdialog.h"

using namespace businesslayer;

/*!
 * \fn RemoverDialog::RemoverDialog(QWidget *parent)
 * \brief RemoverDialog::RemoverDialog constructor
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
RemoverDialog::RemoverDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();

	setWindowTitle(tr("Destroy container"));
}

/*!
 * \fn RemoverDialog::~RemoverDialog()
 * \brief RemoverDialog::~RemoverDialog destructor
 *
 * Default destructor
 */
RemoverDialog::~RemoverDialog()
{
	delete m_infoLabel;
	delete m_alert;
	delete m_containerCombobox;
	delete m_cancel;
	delete m_destroy;

	delete m_layout;
	delete m_loader;

	delete m_lxc;

	if(m_containers)
	{
		for(int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
	}
}

/*!
 * \fn RemoverDialog::updateContainers(bool populate)
 * \brief RemoverDialog::updateContainers update containers list
 *
 * The \a updateContainers method updates containers list to display in combobox.
 *
 * \param populate waits true to populate.
 */
void RemoverDialog::updateContainers(bool populate)
{
	if(!populate)
		return;

	m_containerCombobox->clear();

	if(m_containers)
	{
		for (int i = 0; i < m_containersCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
	}

	m_containers = m_lxc->allContainersList();
	m_containersCount = m_lxc->lxcCountAll();

	if(m_containers)
	{
		m_containerCombobox->addItem(tr("Select Container ..."));

		for (int i = 0; i < m_containersCount; i++)
			m_containerCombobox->addItem(m_containers[i]->name);
	}
}

/*!
 * \fn RemoverDialog::showAlert(bool success)
 * \brief RemoverDialog::showAlert display an alert label.
 *
 * This method displays an \c Alert object. The \a message it will be display.
 * Two alert are possible success or danger alert.
 *
 * \param status true for success alert, false for danger alert
 */
void RemoverDialog::showAlert(bool status)
{
	clear();

	if(status)
		m_alert->success(tr("Container destroyed with success, this action cannot be undone!"));

	else
		m_alert->danger(tr("Failed to destroy container please try again!"));
}

/*!
 * \fn RemoverDialog::initObjects
 * \brief RemoverDialog::initObjects initialize objects
 *
 * This method creates and initializes all objects of this class.
 */
void RemoverDialog::initObjects()
{
	m_lxc = new LxcContainer((new ConfigFile)->find("lxcpath", QDir::homePath() + DEFAULT_FOLDER).toLatin1().data(), this);
	m_containers = nullptr;
	m_containersCount = 0;

	m_loader = new Loader;
	m_loader->setColor(QColor(95, 158, 160));
	m_loader->setArcRect(QRectF(-12, -12, 24, 24));

	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Please select a container to destroy. Destroy a container cannot be undone."), this);
	m_infoLabel->setWordWrap(true);

	m_alert = new Alert(this);
	m_alert->setMinimumHeight(45);

	m_containerCombobox = new QComboBox(this);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_destroy = new QPushButton(tr("Destroy"), this);
	m_destroy->setStyleSheet(m_css["primary-button"]);

	updateContainers(true);
}

/*!
 * \fn RemoverDialog::initDisposal
 * \brief RemoverDialog::initDisposal dispose object in ui
 *
 * This method disposes the object into layer.
 */
void RemoverDialog::initDisposal()
{
	m_layout->addWidget(m_infoLabel, 0, 0, 1, 3);
	m_layout->addWidget(m_alert, 1, 0, 1, 3);
	m_layout->addWidget(m_containerCombobox, 2, 0, 1, 3);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 3, 0);

	m_layout->addWidget(m_cancel, 3, 1);
	m_layout->addWidget(m_destroy, 3, 2);

	setFixedSize(QSize(380, 200));
	setStyleSheet(m_css["body"]);
	setLayout(m_layout);
}

/*!
 * \fn RemoverDialog::initConnections
 * \brief RemoverDialog::initConnections
 *
 * This method connect the objects.
 */
void RemoverDialog::initConnections()
{
	connect(m_loader, &Loader::timerChanged, this, QOverload<>::of(&RemoverDialog::update));
	connect(m_cancel, &QPushButton::clicked, this, &RemoverDialog::cancelClick);
	connect(m_destroy, &QPushButton::clicked, this, &RemoverDialog::remove);
	connect(m_lxc, &LxcContainer::containerDestroyed, this, [&](bool status) {showAlert(status); updateContainers(status); emit containerDestroyed(status); });
}

/*!
 * \fn RemoverDialog::paintEvent
 * \brief RemoverDialog::paintEvent paint loader
 *
 * Override method it paint the loader when loading attribute is set to true,
 * otherwize if loading attribute is false, the loader will be not paint.
 *
 * \param event received from \a event.
 */
void RemoverDialog::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);

	if(m_loader->isLoading())
	{
		QPointF pos(m_destroy->geometry().center().rx(), m_destroy->geometry().center().ry());
		m_loader->spinner(painter, pos);
	}

	painter->end();

	QDialog::paintEvent(event);
}

/*!
 * \fn RemoverDialog::closeEvent
 * \brief RemoverDialog::closeEvent close action event
 *
 * Override method, the method clears the items before to close.
 * If loader is going the \a event ignore closing.
 *
 * \param event received from \a event
 */
void RemoverDialog::closeEvent(QCloseEvent *event)
{
	if(m_loader->isLoading())
	{
		event->ignore();
		return;
	}

	clear();
	QDialog::closeEvent(event);
}

/*!
 * \fn RemoverDialog::remove
 * \brief RemoverDialog::remove removes containers
 *
 * This method removes containers and the action cannot be undo.
 * The container can be destroy only if it not contains snapshots.
 */
void RemoverDialog::remove()
{
	int idx = m_containerCombobox->currentIndex() - 1;

	if(idx < 0)
	{
		m_alert->information(tr("Please make a selection first!"));
		return;
	}

	lxc_snapshot *snapshot = nullptr;
	int count = m_containers[idx]->snapshot_list(m_containers[idx], &snapshot);

	if(count)
	{
		m_alert->warning(tr("This container contains snapshot, please remove snapshots first!"));

		delete [] snapshot;
		snapshot = nullptr;

		return;
	}

	m_loader->start();
	m_destroy->setVisible(false);

	m_lxc->destroy(m_containers[idx]);
}

/*!
 * \fn RemoverDialog::cancelClick
 * \brief RemoverDialog::cancelClick clear element on cancel click
 *
 * This method is triggered when cancel button is clicked.
 * If loading is running the event will be ignore.
 */
void RemoverDialog::cancelClick()
{
	if(!m_loader->isLoading())
		clear();
}

/*!
 * \fn RemoverDialog::clear
 * \brief RemoverDialog::clear clears items
 *
 * This method will clear all items of the class.
 */
void RemoverDialog::clear()
{
	m_containerCombobox->setCurrentIndex(0);
	m_alert->clean();

	m_loader->stop();
	m_destroy->setVisible(true);
}


