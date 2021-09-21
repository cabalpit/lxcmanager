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
}

void MainWindow::initObjects()
{
	m_toolbar = new ToolBar(this);
	m_configDialog = new ConfigDialog(this);
	m_configDialog->setModal(true);
}

void MainWindow::initDisposal()
{
	addToolBar(Qt::LeftToolBarArea, m_toolbar);

	setGeometry(100, 100, 1170, 950);
}

void MainWindow::initConnections()
{
	connect(m_toolbar, &ToolBar::settingClicked, m_configDialog, &ConfigDialog::show);
}
