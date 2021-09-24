#include "creatorwidget.h"

using namespace businesslayer;

CreatorWidget::CreatorWidget(QWidget *parent) : QWidget(parent)
{
	initObjects();
	initConnections();
}

CreatorWidget::~CreatorWidget()
{
	delete m_controller;

	delete m_titleIcon;
	delete m_titleLabel;
	delete m_distribLabel;
	delete m_releaseLabel;
	delete m_archLabel;
	delete m_variantLabel;

	delete m_distribCombo;
	delete m_releaseCombo;
	delete m_archCombo;
	delete m_variantCombo;

	delete m_cancel;
	delete m_create;
	delete m_grid;
}

void CreatorWidget::containerCreated(bool create)
{

}

void CreatorWidget::initObjects()
{
	m_controller = new Controller();

	m_grid = new QGridLayout(this);

	m_titleLabel = new QLabel(tr("Create Container"), this);

	m_titleIcon = new QLabel(this);
	m_titleIcon->setPixmap(QPixmap(":/icons/lxc_plus"));

	m_distribLabel = new QLabel(tr("Distribution:"), this);
	m_releaseLabel = new QLabel(tr("Release:"), this);
	m_archLabel = new QLabel(tr("Architecture:"), this);
	m_variantLabel = new QLabel(tr("Variant (optional):"), this);

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


	m_releaseCombo = new QComboBox(this);
	m_archCombo = new QComboBox(this);
	m_variantCombo = new QComboBox(this);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_create = new QPushButton(tr("Create"), this);
	m_create->setStyleSheet(m_css["primary-button"]);

	m_grid->addWidget(m_titleIcon, 0, 0, Qt::AlignCenter);
	m_grid->addWidget(m_titleLabel, 0, 1, Qt::AlignLeft);

	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 0, 1, 2);
	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 2, 1, 2);

	m_grid->addWidget(m_distribLabel, 2, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_distribCombo, 2, 2, 1, 2);

	m_grid->addWidget(m_releaseLabel, 3, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_releaseCombo, 3, 2, 1, 2);

	m_grid->addWidget(m_archLabel, 4, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_archCombo, 4, 2, 1, 2);

	m_grid->addWidget(m_variantLabel, 5, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_variantCombo, 5, 2, 1, 2);

	m_grid->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed), 6, 0, 1, 2);
	m_grid->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed), 6, 2, 1, 2);

	m_grid->addWidget(m_cancel, 7, 3);
	m_grid->addWidget(m_create, 7, 4);

	setLayout(m_grid);

	setFixedWidth(450);
	setStyleSheet(m_css["card"]);
	setAutoFillBackground(true);
}

void CreatorWidget::initConnections()
{
	connect(m_distribCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::clear);
	connect(m_distribCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateRelease);

	connect(m_cancel, &QPushButton::clicked, this, &CreatorWidget::cancel);
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

void CreatorWidget::cancel()
{
	m_distribCombo->setCurrentIndex(0);
	clear();
}

void CreatorWidget::clear()
{
	disconnect(m_releaseCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateArch);
	disconnect(m_archCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateVariant);

	m_releaseCombo->clear();
	m_archCombo->clear();
	m_variantCombo->clear();
}

void CreatorWidget::create()
{

}
