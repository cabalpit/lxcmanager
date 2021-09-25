#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	initObjects();
	initDisposal();
	initConnections();
}

MainWindow::~MainWindow()
{
	delete m_toolbar;
	delete m_configDialog;
	delete m_creator;
	delete m_lxcview;

	delete m_layout;
	delete m_centralWidget;
}

void MainWindow::initObjects()
{
	m_centralWidget = new QWidget(this);
	m_centralWidget->setAutoFillBackground(true);
	m_centralWidget->setStyleSheet(m_css["body"]);

	m_layout = new QGridLayout(m_centralWidget);

	m_toolbar = new ToolBar(this);

	m_configDialog = new ConfigDialog(this);
	m_configDialog->setModal(true);

	m_lxcview = new LxcView(this);

	m_creator = new CreatorWidget(m_centralWidget);
}

void MainWindow::initDisposal()
{
	addToolBar(Qt::LeftToolBarArea, m_toolbar);

	setGeometry(100, 100, 1170, 950);

	m_layout->addWidget(m_creator, 0, 0);
	m_layout->addWidget(m_lxcview, 0, 1, 2, 1);

	m_centralWidget->setLayout(m_layout);
	setCentralWidget(m_centralWidget);
}

void MainWindow::initConnections()
{
	connect(m_toolbar, &ToolBar::settingClicked, m_configDialog, &ConfigDialog::show);
}
