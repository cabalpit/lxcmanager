#include "creatorwidget.h"

using namespace businesslayer;
using namespace model;

/*!
 * \brief CreatorWidget::CreatorWidget
 *
 * Construct the class with default objects.
 * \param parent waits parent \c QWidget, default \a nullptr
 */
CreatorWidget::CreatorWidget(QWidget *parent) : QWidget(parent)
{
	initObjects();
	initDisposal();
	initConnections();
}

/*!
 * \brief CreatorWidget::~CreatorWidget
 *
 * Destructor
 */
CreatorWidget::~CreatorWidget()
{
	delete m_controller;
	delete m_lxc;

	delete m_titleIcon;
	delete m_titleLabel;
	delete m_alert;
	delete m_nameLabel;
	delete m_distribLabel;
	delete m_releaseLabel;
	delete m_archLabel;
	delete m_variantLabel;

	delete m_nameEdit;
	delete m_distribCombo;
	delete m_releaseCombo;
	delete m_archCombo;
	delete m_variantCombo;

	delete m_cancel;
	delete m_create;
	delete m_grid;

	delete m_loader;
}

/*!
 * \brief CreatorWidget::showAlert
 *
 * This slot show alert on success or on failure. It stop and clear all elements too.
 *
 * \param success waits state true for success, or false on failure.
 * \param message waits the message to display.
 */
void CreatorWidget::showAlert(bool success, const QString &message)
{
	clearAll();

	if(success)
		m_alert->success(tr("Container created with success! ") + message);

	else
		m_alert->danger(tr("Container creation failed! ") + message);
}

/*!
 * \brief CreatorWidget::initObjects
 *
 * This method creates all objects of this class and initializes them.
 */
void CreatorWidget::initObjects()
{
	m_lxc = new LxcContainer((new ConfigFile())->find("lxcpath", QString(QDir::homePath() + DEFAULT_FOLDER)).toLatin1().data(), this);

	m_loading = false;
	m_loader = new Loader;
	m_loader->setColor(QColor(95, 158, 160));
	m_loader->setArcRect(QRectF(-12, -12, 24, 24));

	m_controller = new Controller(this);

	m_grid = new QGridLayout(this);

	m_titleLabel = new QLabel(tr("Create Container"), this);

	m_titleIcon = new QLabel(this);
	m_titleIcon->setPixmap(QPixmap(":/icons/lxc_plus_black"));

	m_alert = new Alert(this);

	m_nameLabel = new QLabel(tr("Container name:"), this);
	m_distribLabel = new QLabel(tr("Distribution:"), this);
	m_releaseLabel = new QLabel(tr("Release:"), this);
	m_archLabel = new QLabel(tr("Architecture:"), this);
	m_variantLabel = new QLabel(tr("Variant:"), this);

	m_distribCombo = new QComboBox(this);
	m_distribCombo->addItem(tr("Select distribution ..."));

	QListIterator<Distribution> it(m_controller->distributions());

	while(it.hasNext())
	{
		Distribution distrib = it.next();

		QPixmap pxmap;
		pxmap.loadFromData(QByteArray::fromBase64(distrib.icon));

		m_distribCombo->addItem(QIcon(pxmap), distrib.name, distrib.id);
	}

	m_nameEdit = new QLineEdit(this);
	m_nameEdit->setPlaceholderText("container name");
	m_releaseCombo = new QComboBox(this);
	m_archCombo = new QComboBox(this);
	m_variantCombo = new QComboBox(this);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_create = new QPushButton(tr("Create"), this);
	m_create->setStyleSheet(m_css["primary-button"]);
}

/*!
 * \brief CreatorWidget::initDisposal
 *
 * This method initializes the disposition of the object for ui.
 */
void CreatorWidget::initDisposal()
{
	m_grid->addWidget(m_titleIcon, 0, 0, Qt::AlignCenter);
	m_grid->addWidget(m_titleLabel, 0, 1, Qt::AlignLeft);

	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 0, 1, 3);
	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 2, 1, 3);

	m_grid->addWidget(m_alert, 2, 0, 1, 5);

	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 3, 0, 1, 3);
	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 3, 2, 1, 3);

	m_grid->addWidget(m_nameLabel, 4, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_nameEdit, 4, 2, 1, 3);

	m_grid->addWidget(m_distribLabel, 5, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_distribCombo, 5, 2, 1, 3);

	m_grid->addWidget(m_releaseLabel, 6, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_releaseCombo, 6, 2, 1, 3);

	m_grid->addWidget(m_archLabel, 7, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_archCombo, 7, 2, 1, 3);

	m_grid->addWidget(m_variantLabel, 8, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_variantCombo, 8, 2, 1, 3);

	m_grid->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed), 9, 0, 1, 2);
	m_grid->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed), 9, 2, 1, 3);

	m_grid->addWidget(m_cancel, 10, 3);
	m_grid->addWidget(m_create, 10, 4);

	setLayout(m_grid);

	setFixedSize(420, 395);
	setStyleSheet(m_css["card"]);
	setAutoFillBackground(true);
}

/*!
 * \brief CreatorWidget::initConnections
 *
 * This method initializes the connection between the objects.
 */
void CreatorWidget::initConnections()
{
	connect(m_loader, &Loader::timerChanged, this, QOverload<>::of(&CreatorWidget::update));
	connect(m_distribCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::cancelClick);
	connect(m_distribCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateRelease);
	connect(m_create, &QPushButton::clicked, this, &CreatorWidget::create);
	connect(m_cancel, &QPushButton::clicked, this, &CreatorWidget::clearAll);
	connect(m_lxc, &LxcContainer::containerCreated, this, [&] (bool status, const QString &message) { showAlert(status, message); emit containerCreated(status); });
}

/*!
 * \brief CreatorWidget::paintEvent
 *
 * overrided method \c \see QWidget::paintEvent(QPaintEvent *).
 *
 * The method draw the background and draw spinner when is started.
 *
 * \param event waits event \c QPaintEvent provided by Qt
 */
void CreatorWidget::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);

	//	background
	painter->save();
	painter->fillRect(event->rect(), QBrush(Qt::white, Qt::SolidPattern));
	painter->restore();

	// spinner
	if(m_loading)
	{
		QPointF pos(m_create->geometry().center().rx(), m_create->geometry().center().ry());
		m_loader->spinner(painter, pos);
	}

	painter->end();

	QWidget::paintEvent(event);
}

/*!
 * \brief CreatorWidget::updateRelease
 *
 * This method updates releases combobox.
 */
void CreatorWidget::updateRelease(int)
{
	QHashIterator<int, QVariant>releases(m_controller->release(m_distribCombo->currentData().toInt()));

	m_releaseCombo->clear();
	m_releaseCombo->addItem(tr("Select release ..."));

	while (releases.hasNext())
	{
		releases.next();
		m_releaseCombo->addItem(releases.value().toString(), releases.key());
	}

	connect(m_releaseCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateArch);
}

/*!
 * \brief CreatorWidget::updateArch
 *
 * This method update Architecture combobox.
 */
void CreatorWidget::updateArch(int)
{
	QHashIterator<int, QVariant>arches(m_controller->architectures(m_distribCombo->currentData().toInt(), m_releaseCombo->currentData().toInt()));

	m_archCombo->clear();
	m_archCombo->addItem(tr("Select architecture ..."));


	while (arches.hasNext())
	{
		arches.next();
		m_archCombo->addItem(arches.value().toString(), arches.key());
	}

	connect(m_archCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateVariant);
}

/*!
 * \brief CreatorWidget::updateVariant
 *
 * This method update Variant combobox.
 */
void CreatorWidget::updateVariant(int)
{
	QHashIterator<int, QVariant>variants(m_controller->variants(m_distribCombo->currentData().toInt(), m_releaseCombo->currentData().toInt(), m_archCombo->currentData().toInt()));

	m_variantCombo->clear();
	m_variantCombo->addItem(tr("Select variant ..."));

	while (variants.hasNext())
	{
		variants.next();
		m_variantCombo->addItem(variants.value().toString(), variants.key());
	}
}

/*!
 * \brief CreatorWidget::create
 *
 * This method will check if all condition are validate before to emit the signal \c createClicked()
 * for container creation.
 */
void CreatorWidget::create()
{
	m_alert->clean();

	int name = m_nameEdit->text().trimmed().length();
	int dist = m_distribCombo->currentIndex();
	int rels = m_releaseCombo->currentIndex();
	int arch = m_archCombo->currentIndex();
	int variant = m_variantCombo->currentIndex();

	QRegularExpression regex("[\\s!@#$%^&*()+=\\\\\\/?<>,.]+");

	if(name <= 2 || m_nameEdit->text().contains(regex))
	{
		m_alert->warning(tr("The container name format not allow space or the following special character !@#$%^&*()+=\\/?<>,.!"));
		return;
	}
	else if(dist <= 0 || rels <= 0 || arch <= 0 || variant <= 0)
	{
		m_alert->warning(tr("Selection missing!"));
		return;
	}
	else if(m_lxc->containerExists(m_nameEdit->text().toLatin1().data()))
	{
		m_alert->danger(tr("Container name already exists!"));
		return;
	}

	startLoader();

	Container container = {
		.name = m_nameEdit->text(),
		.distribution = m_distribCombo->currentText(),
		.release = m_releaseCombo->currentText(),
		.arch = m_archCombo->currentText(),
		.variant = m_variantCombo->currentText(),
		.hkp = ConfigFile().find("hkp")
	};

	m_lxc->createContainer(container);
}

/*!
 * \brief CreatorWidget::cancelClick
 *
 * This method clear object combobox and disconnect release and arch combobox.
 */
void CreatorWidget::cancelClick()
{
	disconnect(m_releaseCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateArch);
	disconnect(m_archCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateVariant);

	m_releaseCombo->clear();
	m_archCombo->clear();
	m_variantCombo->clear();

	stopLoader();
}

/*!
 * \brief CreatorWidget::clearAll
 *
 * This method clear all object.
 */
void CreatorWidget::clearAll()
{
	m_alert->clean();
	m_distribCombo->setCurrentIndex(0);
	m_nameEdit->clear();

	cancelClick();
}

/*!
 * \brief CreatorWidget::startSpinner
 *
 * Start loader.
 */
void CreatorWidget::startLoader()
{
	m_loading = true;
	m_loader->start();
	m_create->setVisible(false);
}

/*!
 * \brief CreatorWidget::stopSpinner
 *
 * This method stop loader.
 */
void CreatorWidget::stopLoader()
{
	m_loading = false;
	m_loader->stop();
	m_create->setVisible(true);
}


