#include "creatorwidget.h"

using namespace businesslayer;

CreatorWidget::CreatorWidget(QWidget *parent) : QWidget(parent)
{
	initObjects();
	initDisposal();
	initConnections();
}

CreatorWidget::~CreatorWidget()
{
	delete m_controller;

	delete m_titleIcon;
	delete m_titleLabel;
	delete m_alertLabel;
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
}

void CreatorWidget::containerCreated(bool create, const QString &message)
{
	clearAll();

	if(create)
	{
		m_alertLabel->setStyleSheet(m_css["alert-success"]);
		m_alertLabel->setText(tr("Container created with success! ") + message);
	}
	else
	{
		m_alertLabel->setStyleSheet(m_css["alert-danger"]);
		m_alertLabel->setText(tr("Container creation failed! ") + message);
	}
}

void CreatorWidget::initObjects()
{
	m_spinner = false;
	m_spinnerRotation = 0;

	m_controller = new Controller();

	m_grid = new QGridLayout(this);

	m_titleLabel = new QLabel(tr("Create Container"), this);

	m_titleIcon = new QLabel(this);
	m_titleIcon->setPixmap(QPixmap(":/icons/lxc_plus"));

	m_alertLabel = new QLabel(this);
	m_alertLabel->setStyleSheet(m_css["transparent"]);
	m_alertLabel->setFixedHeight(40);
	m_alertLabel->setAlignment(Qt::AlignCenter);

	m_nameLabel = new QLabel(tr("Container name:"), this);
	m_distribLabel = new QLabel(tr("Distribution:"), this);
	m_releaseLabel = new QLabel(tr("Release:"), this);
	m_archLabel = new QLabel(tr("Architecture:"), this);
	m_variantLabel = new QLabel(tr("Variant:"), this);

	m_distribCombo = new QComboBox(this);
	QMapIterator<QString, QByteArray>it(m_controller->distributions());

	m_distribCombo->addItem(tr("Select distribution ..."));
	while(it.hasNext())
	{
		it.next();

		QPixmap pxmap;
		pxmap.loadFromData(QByteArray::fromBase64(it.value()));

		m_distribCombo->addItem(QIcon(pxmap), it.key());
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

void CreatorWidget::initDisposal()
{
	m_grid->addWidget(m_titleIcon, 0, 0, Qt::AlignCenter);
	m_grid->addWidget(m_titleLabel, 0, 1, Qt::AlignLeft);

	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 0, 1, 3);
	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 2, 1, 3);

	m_grid->addWidget(m_alertLabel, 2, 0, 1, 5);

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

	setFixedSize(450, 395);
	setStyleSheet(m_css["card"]);
	setAutoFillBackground(true);
}

void CreatorWidget::initConnections()
{
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(m_distribCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::clear);
	connect(m_distribCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateRelease);

	connect(m_create, &QPushButton::clicked, this, &CreatorWidget::create);
	connect(m_cancel, &QPushButton::clicked, this, &CreatorWidget::clearAll);
}

void CreatorWidget::paintEvent(QPaintEvent *pevent)
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);

	//	background
	painter->save();
	painter->fillRect(pevent->rect(), QBrush(Qt::white, Qt::SolidPattern));
	painter->restore();

	// spinner
	if(m_spinner)
	{
		painter->save();

		painter->setPen(QPen(QBrush(QColor(95, 158, 160)), 5));


		// get button geometry to place spinner at center button position.
		painter->translate(m_create->geometry().center().rx(), m_create->geometry().center().ry());
		painter->rotate(m_spinnerRotation);

		QRect arcRect(-12, -12, 24, 24);

		painter->drawArc(arcRect, m_spinner, 230  * 16);

		m_spinnerRotation += (360 / 12);	// move 360degree angle by 25

		if(m_spinnerRotation >= 360)
			m_spinnerRotation = 0;

		painter->restore();
	}

	painter->end();

	QWidget::paintEvent(pevent);
}

void CreatorWidget::updateRelease(int)
{
	QStringList releasesList = m_controller->release(m_distribCombo->currentText());;
	releasesList.insert(0, tr("Select release"));

	m_releaseCombo->clear();
	m_releaseCombo->addItems(releasesList);

	connect(m_releaseCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateArch);
}

void CreatorWidget::updateArch(int)
{
	QStringList archList = m_controller->architectures(m_releaseCombo->currentText());
	archList.insert(0, tr("Select architecture"));

	m_archCombo->clear();
	m_archCombo->addItems(archList);

	connect(m_archCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateVariant);
}

void CreatorWidget::updateVariant(int)
{
	QStringList variantsList = m_controller->variants(m_archCombo->currentText());
	variantsList.insert(0, tr("Select variant"));

	m_variantCombo->clear();
	m_variantCombo->addItems(variantsList);
}

void CreatorWidget::create()
{
	clearAlert();
	int name = m_nameEdit->text().length();
	int dist = m_distribCombo->currentIndex();
	int rels = m_releaseCombo->currentIndex();
	int arch = m_archCombo->currentIndex();
	int variant = m_variantCombo->currentIndex();

	if(name <= 2 || m_nameEdit->text().contains(' '))
	{
		m_alertLabel->setStyleSheet(m_css["alert-danger"]);
		m_alertLabel->setText(tr("Name is too short or contains white space!"));
		return;
	}
	else if(dist <= 0 || rels <= 0 || arch <= 0 || variant <= 0)
	{
		m_alertLabel->setStyleSheet(m_css["alert-danger"]);
		m_alertLabel->setText(tr("Selection missing!"));
		return;
	}

	startSpinner();

	QMap<QString, QString> container;
	container.insert("name", m_nameEdit->text().remove(' '));
	container.insert("distribution", m_distribCombo->currentText());
	container.insert("release", m_releaseCombo->currentText());
	container.insert("architecture", m_archCombo->currentText());
	container.insert("variant", m_variantCombo->currentText());

	emit createClicked(container);
}

void CreatorWidget::clear()
{
	disconnect(m_releaseCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateArch);
	disconnect(m_archCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateVariant);

	m_releaseCombo->clear();
	m_archCombo->clear();
	m_variantCombo->clear();

	stopSpinner();
}

void CreatorWidget::clearAlert()
{
	m_alertLabel->clear();
	m_alertLabel->setStyleSheet(m_css["transparent"]);
}

void CreatorWidget::clearAll()
{
	m_distribCombo->setCurrentIndex(0);
	m_nameEdit->clear();

	clear();
	clearAlert();
}

void CreatorWidget::startSpinner()
{
	m_spinner = true;
	m_spinnerRotation = 0;
	m_timer.start(1000 * 12 / 360);
	m_create->setVisible(false);
}

void CreatorWidget::stopSpinner()
{
	m_spinner = false;
	m_spinnerRotation = 0;
	m_timer.stop();
	m_create->setVisible(true);
}


