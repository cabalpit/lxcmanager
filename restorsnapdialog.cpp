#include "restorsnapdialog.h"

using namespace businesslayer;

RestorSnapDialog::RestorSnapDialog(QWidget *parent) : QDialog(parent)
{
	initObjects();
	initDisposal();
	initConnections();
}

RestorSnapDialog::~RestorSnapDialog()
{
	delete m_infoLabel;
	delete m_containerLabel;
	delete m_snapLabel;
	delete m_alertLabel;

	delete m_containerCombo;
	delete m_snapListView;

	delete m_cancel;
	delete m_restor;

	delete m_layout;
}

void RestorSnapDialog::initObjects()
{
	m_layout = new QGridLayout(this);

	m_infoLabel = new QLabel(tr("Restor a container from a snapshot"), this);
	m_containerLabel = new QLabel(tr("Containers with snapshot"), this);
	m_snapLabel = new QLabel(tr("List of snapshot"), this);

	m_alertLabel = new QLabel(this);
	m_alertLabel->setStyleSheet(m_css["transparent"]);

	m_containerCombo = new QComboBox(this);
	m_snapListView = new QListView(this);
	m_snapListView->setModel(&m_model);
	m_model.clear();

	m_cancel = new QPushButton(tr("Cancel"), this);
	m_cancel->setStyleSheet(m_css["default-button"]);
	m_restor = new QPushButton(tr("Restor"), this) ;
	m_restor->setStyleSheet(m_css["primary-button"]);

	m_timer.setInterval(1000 * 12 / 360);
}

void RestorSnapDialog::initDisposal()
{
	m_layout->addWidget(m_infoLabel, 0, 0, 1, 4);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 1, 0, 1, 4);
	m_layout->addWidget(m_alertLabel, 2, 0, 1, 4);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 3, 0, 1, 4);

	m_layout->addWidget(m_containerLabel, 4, 0, 1, 2);
	m_layout->addWidget(m_snapLabel, 4, 2, 1, 2);
	m_layout->addWidget(m_containerCombo, 5, 0, 1, 2);
	m_layout->addWidget(m_snapListView, 5, 2, 1, 2);

	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 6, 0);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 7, 1);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 8, 2);
	m_layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding), 9, 3);

	m_layout->addWidget(m_cancel, 10, 2);
	m_layout->addWidget(m_restor, 10, 3);

	setStyleSheet(m_css["main"]);
	setFixedSize(515, 445);
	setLayout(m_layout);
}

void RestorSnapDialog::initConnections()
{
	connect(m_cancel, &QPushButton::clicked, this, &RestorSnapDialog::clearAll);
}

void RestorSnapDialog::paintEvent(QPaintEvent *event)
{

}

void RestorSnapDialog::closeEvent(QCloseEvent *event)
{
	clearAll();
	QDialog::closeEvent(event);
}

void RestorSnapDialog::resizeEvent(QResizeEvent *event)
{
	qDebug() << event->size();

	QDialog::resizeEvent(event);
}

void RestorSnapDialog::populateSnapView(int idx)
{

}

void RestorSnapDialog::clear()
{
	m_model.clear();
	m_containerCombo->setCurrentIndex(0);
}

void RestorSnapDialog::clearAlert()
{
	m_alertLabel->clear();
	m_alertLabel->setStyleSheet(m_css["transparent"]);
}

void RestorSnapDialog::clearAll()
{
	clear();
	clearAlert();

	m_timer.stop();
}
