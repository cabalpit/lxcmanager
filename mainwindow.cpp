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
	delete m_lxcview;
	delete m_creator;
	delete m_cloneDialog;
	delete m_snapDialog;
	delete m_removerDialog;
	delete m_snapRemoverDialog;

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

	m_lxcview = new LxcView(this);

	m_creator = new CreatorWidget(this);

	m_configDialog = new ConfigDialog(this);
	m_configDialog->setModal(true);

	m_cloneDialog = new CloneDialog(this);
	m_cloneDialog->setModal(true);

	m_snapDialog = new RestoreSnapDialog(this);
	m_snapDialog->setModal(true);

	m_snapRemoverDialog = new RemoveSnapDialog(this);
	m_snapRemoverDialog->setModal(true);

	m_removerDialog = new RemoverDialog(this);
	m_removerDialog->setModal(true);
}

void MainWindow::initDisposal()
{
	addToolBar(Qt::LeftToolBarArea, m_toolbar);

	setGeometry(100, 100, 1170, 950);

	m_layout->addWidget(m_creator, 0, 0);
	m_layout->addWidget(m_lxcview, 0, 1);

	m_centralWidget->setLayout(m_layout);
	setCentralWidget(m_centralWidget);
}

void MainWindow::initConnections()
{
	// toolbar action connections
	connect(m_toolbar, &ToolBar::refreshClicked, m_lxcview, &LxcView::populateModel);
	connect(m_toolbar, &ToolBar::refreshClicked, m_cloneDialog, &CloneDialog::updateContainers);

	// TODO: uncomment when done.
//	connect(m_toolbar, &ToolBar::refreshClicked, m_snapDialog, &RestoreSnapDialog::updateContainers);
//	connect(m_toolbar, &ToolBar::refreshClicked, m_removerDialog, &RemoverDialog::updateContainers);

	connect(m_toolbar, &ToolBar::duplicateClicked, m_cloneDialog, &CloneDialog::show);
	connect(m_toolbar, &ToolBar::restoreSnapClicked, m_snapDialog, &RestoreSnapDialog::show);
	connect(m_toolbar, &ToolBar::deleteCTClicked, m_removerDialog, &RemoverDialog::show);
	connect(m_toolbar, &ToolBar::deleteSnapsClicked, m_snapRemoverDialog, &RemoveSnapDialog::show);
	connect(m_toolbar, &ToolBar::settingClicked, m_configDialog, &ConfigDialog::show);


	// creator object connections
	// TODO: uncomment after created on specific class.
	connect(m_creator, &CreatorWidget::containerCreated, m_lxcview, &LxcView::populateModel);
	connect(m_creator, &CreatorWidget::containerCreated, m_cloneDialog, &CloneDialog::updateContainers);
//	connect(m_creator, &CreatorWidget::containerCreated, m_snapDialog, &RestoreSnapDialog::updateContainers);
//	connect(m_creator, &CreatorWidget::containerCreated, m_removerDialog, &RemoverDialog::updateContainers);
//	connect(m_creator, &CreatorWidget::containerCreated, m_snapRemoverDialog, &RemoveSnapDialog::updateContainers);


	// cloneDialog object connections.
	// TODO: uncomment after created on specific class.
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_lxcview, &LxcView::populateModel);
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_snapDialog, &LxcView::populateModel);
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_removerDialog, &LxcView::populateModel);
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_snapRemoverDialog, &LxcView::populateModel);

	// TODO: revaluate connections
	connect(m_snapDialog, &RestoreSnapDialog::restored, m_lxcview, &LxcView::restoreSnapshot);
	connect(m_removerDialog, &RemoverDialog::distroyClicked, m_lxcview, &LxcView::destroyContainer);
	connect(m_snapRemoverDialog, &RemoveSnapDialog::snapRemoved, m_lxcview, &LxcView::destroySnap);

	connect(m_lxcview, &LxcView::lxcSnapRestored, m_snapDialog, &RestoreSnapDialog::showAlert);
	connect(m_lxcview, &LxcView::lxcDestroyed, m_removerDialog, &RemoverDialog::showAlert);
	// end revaluation connections.
}
