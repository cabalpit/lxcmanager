#include "creatorwidget.h"

CreatorWidget::CreatorWidget(QWidget *parent) : QWidget(parent)
{

}

CreatorWidget::~CreatorWidget()
{
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
	m_grid = new QGridLayout(this);

	m_titleLabel = new QLabel(tr("Create Container"), this);

	m_titleIcon = new QLabel(this);
	m_titleIcon->setPixmap(QPixmap(":/icons/lxc_plus"));

	m_distribLabel = new QLabel(tr("Distribution:"), this);
	m_releaseLabel = new QLabel(tr("Release:"), this);
	m_archLabel = new QLabel(tr("Architecture:"), this);
	m_variantLabel = new QLabel(tr("Variant (optional):"), this);

	m_distribCombo = new QComboBox(this);
	m_releaseCombo = new QComboBox(this);
	m_archCombo = new QComboBox(this);
	m_variantCombo = new QComboBox(this);

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);

	m_create = new QPushButton(tr("Create"), this);
	m_create->setStyleSheet(m_css["primary-button"]);

	m_grid->addWidget(m_titleLabel, 0, 0, Qt::AlignCenter);
	m_grid->addWidget(m_titleLabel, 0, 1, Qt::AlignLeft);

	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 0, 1, 2);
	m_grid->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 2, 1, 2);

	m_grid->addWidget(m_distribLabel, 2, 2, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_distribCombo, 2, 3, 1, 2);

	m_grid->addWidget(m_releaseLabel, 3, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_releaseCombo, 3, 3, 1, 2);

	m_grid->addWidget(m_archLabel, 4, 2, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_archCombo, 4, 3, 1, 2);

	m_grid->addWidget(m_variantLabel, 5, 0, 1, 2, Qt::AlignRight);
	m_grid->addWidget(m_variantCombo, 5, 3, 1, 2);

	m_grid->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed), 6, 0, 1, 2);
	m_grid->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed), 6, 2, 1, 2);

	m_grid->addWidget(m_cancel, 7, 3);
	m_grid->addWidget(m_create, 7, 4);

	setFixedWidth(450);
	setStyleSheet(m_css["card"]);

	setLayout(m_grid);
}

void CreatorWidget::initConnections()
{
	connect(m_distribCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateRelease);
	connect(m_releaseCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateArch);
	connect(m_archCombo, &QComboBox::currentIndexChanged, this, &CreatorWidget::updateVariant);
}

void CreatorWidget::updateRelease(int idx)
{

}

void CreatorWidget::updateArch(int idx)
{

}

void CreatorWidget::updateVariant(int idx)
{

}

void CreatorWidget::cancel()
{
	m_distribCombo->setCurrentIndex(0);
	m_releaseCombo->clear();
	m_archCombo->clear();
	m_variantCombo->clear();
}

void CreatorWidget::create()
{

}
