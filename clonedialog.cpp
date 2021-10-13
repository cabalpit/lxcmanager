#include "clonedialog.h"

using namespace businesslayer;

/*!
 * \brief CloneDialog::CloneDialog
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
CloneDialog::CloneDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();

	setWindowTitle(tr("Duplicate Container"));
}

/*!
 * \brief CloneDialog::~CloneDialog
 *
 * Default destructor.
 */
CloneDialog::~CloneDialog()
{
	delete m_titleLabel;
	delete m_alert;
	delete m_containerLabel;
	delete m_copyLabel;
	delete m_cloneTypeLabel;
	delete m_containersCombo;
	delete m_cloneTypeCombo;
	delete m_newContainerNameLine;
	delete m_cancel;
	delete m_create;

	delete m_layout;
	delete m_lxc;
	delete m_loader;

	if(m_containers)
	{
		for (int i = 0; i < m_containerCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
	}
}

/*!
 * \brief CloneDialog::updateContainers
 *
 * This method populates containers list.
 *
 * \param populate if \c true to populate container list, otherwize \c false.
 */
void CloneDialog::updateContainers(bool populate)
{
	if(!populate)
		return;

	m_containersCombo->clear();
	m_containersCombo->addItem(tr("Select container ..."));

	if(m_containers)
	{
		for (int i = 0; i < m_containerCount; i++)
		{
			lxc_container_put(m_containers[i]);
			m_containers[i] = nullptr;
		}

		delete [] m_containers;
	}

	m_containers = m_lxc->allContainersList();
	m_containerCount = m_lxc->lxcCountAll();

	for(int i = 0; i < m_containerCount; i++)
		m_containersCombo->addItem(m_containers[i]->name);
}

/*!
 * \brief showAlert::showAlert
 *
 * This method displays an \c Alert object. The \a message it will be display.
 * Two alert are possible success or danger alert.
 *
 * \param status \c true for success alert, \c false for danger alert.
 */
void CloneDialog::showAlert(bool success)
{
	clear();

	if(success)
		m_alert->success(tr("Newly-allocated copy of container success!"));

	else
		m_alert->danger(tr("Newly-allocated copy of container failed!"));
}

/*!
 * \brief CloneDialog::initObjects
 *
 * This method creates all objects of this class.
 */
void CloneDialog::initObjects()
{
	m_lxc = new LxcContainer((new ConfigFile)->find("lxcpath", QDir::homePath() + DEFAULT_FOLDER).toByteArray().data(),this);

	m_containers = nullptr;
	m_containerCount = 0;

	m_loader = new Loader;
	m_loader->setColor(QColor(95, 158, 160));
	m_loader->setArcRect(QRectF(-12, -12, 24, 24));

	m_layout = new QGridLayout(this);

	m_titleLabel = new QLabel(tr("Duplicate an existing container"), this);
	m_alert = new Alert(this);
	m_alert->setMinimumHeight(45);

	m_containerLabel = new QLabel(tr("Containers:"), this);
	m_copyLabel = new QLabel(tr("New Container name:"), this);
	m_cloneTypeLabel = new QLabel(tr("Clone type:"), this);

	m_containersCombo = new QComboBox(this);

	m_cloneTypeCombo = new QComboBox(this);
	m_cloneTypeCombo->addItem(tr("Select clone type ..."));
	m_cloneTypeCombo->addItem(tr("Copy container"), 0);
	m_cloneTypeCombo->addItem(tr("Clone Snapshot"), 6);

	m_newContainerNameLine = new QLineEdit(this);
	m_newContainerNameLine->setPlaceholderText(tr("Container Name"));

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_create = new QPushButton(tr("Create"), this);
	m_create->setStyleSheet(m_css["primary-button"]);

	updateContainers(true);
}

/*!
 * \brief CloneDialog::initDisposal
 *
 * This method disposes the object into layer.
 */
void CloneDialog::initDisposal()
{
	m_layout->addWidget(m_titleLabel, 0, 0, 1, 6);
	m_layout->addWidget(m_alert, 1, 0, 1, 6);

	m_layout->addWidget(m_containerLabel, 2, 0, 1, 2);
	m_layout->addWidget(m_copyLabel, 2, 2, 1, 2);
	m_layout->addWidget(m_cloneTypeLabel, 2, 4, 1, 2);

	m_layout->addWidget(m_containersCombo, 3, 0, 1, 2);
	m_layout->addWidget(m_newContainerNameLine, 3, 2, 1, 2);
	m_layout->addWidget(m_cloneTypeCombo, 3, 4, 1, 2);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 4, 0, 1, 4);
	m_layout->addWidget(m_cancel, 4, 4);
	m_layout->addWidget(m_create, 4, 5);

	setStyleSheet(m_css["body"]);
	setFixedSize(QSize(550, 200));
	setLayout(m_layout);
}

/*!
 * \brief CloneDialog::initConnections
 *
 * This method connect the objects.
 */
void CloneDialog::initConnections()
{
	connect(m_loader, &Loader::timerChanged, this, QOverload<>::of(&CloneDialog::update));
	connect(m_cancel, &QPushButton::clicked, this, &CloneDialog::cancelClick);
	connect(m_create, &QPushButton::clicked, this, &CloneDialog::clone);
	connect(m_lxc, &LxcContainer::containerCloned, this, [&](bool status) { showAlert(status); updateContainers(status); emit containerCloned(status); });
}

/*!
 * \brief CloneDialog::paintEvent
 *
 * Override method it paint the loader when loading attribute is set to true,
 * otherwize if loading attribute is false, the loader will be not paint.
 *
 * \param event received from \a event.
 */
void CloneDialog::paintEvent(QPaintEvent *event)
{
	if(m_loader->isLoading())
	{
		QPainter *painter = new QPainter(this);
		painter->setRenderHint(QPainter::Antialiasing, true);

		QPointF pos(m_create->geometry().center().rx(), m_create->geometry().center().ry());
		m_loader->spinner(painter, pos);

		painter->end();
	}

	QDialog::paintEvent(event);
}

/*!
 * \brief CloneDialog::closeEvent
 *
 * Override method, the method clears the items before to close.
 * If loader is going the \a event ignore closing.
 *
 * \param event received from \a event
 */
void CloneDialog::closeEvent(QCloseEvent *event)
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
 * \brief CloneDialog::clone
 *
 * This method checks if all condition are filled before to clone a container.
 * If condition are filled, the method will clone the container.
 */
void CloneDialog::clone()
{
	m_alert->clean();

	uint idxContainer = m_containersCombo->currentIndex();
	uint idxType = m_cloneTypeCombo->currentIndex();
	QString name = m_newContainerNameLine->text().trimmed();
	QRegularExpression regex("[\\s!@#$%^&*()+=\\\\\\/?<>,.]+");

	if(!idxContainer || name.isEmpty() || !idxType)
	{
		m_alert->danger(tr("Please Select a container or define a name"));
		return;
	}

	if(name.contains(regex))
	{
		m_alert->danger(tr("Container name format not allow space or the following special character !@#$%^&*()+=\\/?<>,.!"));
		return;
	}

	if(m_containersCombo->findText(name) > -1)
	{
		m_alert->danger(tr("The container name already exists"));
		return;
	}

	m_loader->start();
	m_create->setVisible(false);

	m_lxc->clone(m_containers[idxContainer - 1], name.toLatin1().data(), m_cloneTypeCombo->currentData().toInt());
}

/*!
 * \brief CloneDialog::cancelClick
 *
 * This method is triggered when cancel button is clicked.
 * If loading is running the event will be ignore.
 */
void CloneDialog::cancelClick()
{
	if(!m_loader->isLoading())
		clear();
}

/*!
 * \brief CloneDialog::clear
 *
 * This method will clear all items of the class.
 */
void CloneDialog::clear()
{
	m_loader->stop();
	m_create->setVisible(true);
	m_alert->clean();
	m_newContainerNameLine->clear();
	m_containersCombo->setCurrentIndex(0);
	m_cloneTypeCombo->setCurrentIndex(0);
}

