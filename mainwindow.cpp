#include "mainwindow.h"

/*!
 * \brief MainWindow::MainWindow
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	initObjects();
	initDisposal();
	initConnections();
}

/*!
 * \brief MainWindow::~MainWindow
 *
 * Default destructor
 */
MainWindow::~MainWindow()
{
	delete m_toolbar;
	delete m_configDialog;
	delete m_lxcWidget;
	delete m_creator;
	delete m_cloneDialog;
	delete m_restoreSnapDialog;
	delete m_removerDialog;
	delete m_removeSnapDialog;

	delete m_layout;
	delete m_centralWidget;
}

/*!
 * \brief MainWindow::initObjects
 *
 * This method creates the objects of the class.
 */
void MainWindow::initObjects()
{
	m_centralWidget = new QWidget(this);
	m_centralWidget->setAutoFillBackground(true);
	m_centralWidget->setStyleSheet(m_css["main"]);

	m_layout = new QGridLayout(m_centralWidget);

	m_toolbar = new ToolBar(this);

	m_lxcWidget = new LxcWidget(this);

	m_creator = new CreatorWidget(this);

	m_configDialog = new SettingsDialog(this);
	m_configDialog->setModal(true);

	m_cloneDialog = new CloneDialog(this);
	m_cloneDialog->setModal(true);

	m_restoreSnapDialog = new SnapshotDialog(SnapshotDialog::RESTORE, this);
	m_restoreSnapDialog->setModal(true);

	m_removeSnapDialog = new SnapshotDialog(SnapshotDialog::REMOVE, this);
	m_removeSnapDialog->setModal(true);

	m_removerDialog = new RemoverDialog(this);
	m_removerDialog->setModal(true);
}

/*!
 * \brief MainWindow::initDisposal
 *
 * This method disposes the objects into layer.
 */
void MainWindow::initDisposal()
{
	addToolBar(Qt::LeftToolBarArea, m_toolbar);

	setGeometry(100, 100, 1370, 950);

	m_layout->addWidget(m_creator, 0, 0);
	m_layout->addWidget(m_lxcWidget, 0, 1);

	m_centralWidget->setLayout(m_layout);
	setCentralWidget(m_centralWidget);
}

/*!
 * \brief MainWindow::initConnections
 *
 * This method connects the objects.
 */
void MainWindow::initConnections()
{
	// toolbar action connections
	connect(m_toolbar, &ToolBar::refreshClicked, m_lxcWidget->view(), &LxcView::populateModel);
	connect(m_toolbar, &ToolBar::refreshClicked, m_cloneDialog, &CloneDialog::updateContainers);
	connect(m_toolbar, &ToolBar::refreshClicked, m_restoreSnapDialog, &SnapshotDialog::updateContainers);
	connect(m_toolbar, &ToolBar::refreshClicked, m_removerDialog, &RemoverDialog::updateContainers);
	connect(m_toolbar, &ToolBar::refreshClicked, m_removeSnapDialog, &SnapshotDialog::updateContainers);

	connect(m_toolbar, &ToolBar::duplicateClicked, m_cloneDialog, &CloneDialog::show);
	connect(m_toolbar, &ToolBar::restoreSnapClicked, m_restoreSnapDialog, &SnapshotDialog::show);
	connect(m_toolbar, &ToolBar::deleteCTClicked, m_removerDialog, &RemoverDialog::show);
	connect(m_toolbar, &ToolBar::deleteSnapsClicked, m_removeSnapDialog, &SnapshotDialog::show);
	connect(m_toolbar, &ToolBar::settingClicked, m_configDialog, &SettingsDialog::show);

	// lxcview object connection
	connect(m_lxcWidget->view(), &LxcView::snapshotCreated, m_restoreSnapDialog, &SnapshotDialog::updateContainers);
	connect(m_lxcWidget->view(), &LxcView::snapshotCreated, m_removeSnapDialog, &SnapshotDialog::updateContainers);

	// creator object connections
	connect(m_creator, &CreatorWidget::containerCreated, m_lxcWidget->view(), &LxcView::populateModel);
	connect(m_creator, &CreatorWidget::containerCreated, m_cloneDialog, &CloneDialog::updateContainers);
	connect(m_creator, &CreatorWidget::containerCreated, m_restoreSnapDialog, &SnapshotDialog::updateContainers);
	connect(m_creator, &CreatorWidget::containerCreated, m_removerDialog, &RemoverDialog::updateContainers);
	connect(m_creator, &CreatorWidget::containerCreated, m_removeSnapDialog, &SnapshotDialog::updateContainers);

	// cloneDialog object connections.
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_lxcWidget->view(), &LxcView::populateModel);
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_restoreSnapDialog, &SnapshotDialog::updateContainers);
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_removerDialog, &RemoverDialog::updateContainers);
	connect(m_cloneDialog, &CloneDialog::containerCloned, m_removeSnapDialog, &SnapshotDialog::updateContainers);

	// snapshot restore
	connect(m_restoreSnapDialog, &SnapshotDialog::snapshotRestored, m_lxcWidget->view(), &LxcView::populateModel);
	connect(m_restoreSnapDialog, &SnapshotDialog::snapshotRestored, m_cloneDialog, &CloneDialog::updateContainers);
	connect(m_restoreSnapDialog, &SnapshotDialog::snapshotRestored, m_removerDialog, &RemoverDialog::updateContainers);
	connect(m_restoreSnapDialog, &SnapshotDialog::snapshotRestored, m_removeSnapDialog, &SnapshotDialog::updateContainers);

	// container remover
	connect(m_removerDialog, &RemoverDialog::containerDestroyed, m_lxcWidget->view(), &LxcView::populateModel);
	connect(m_removerDialog, &RemoverDialog::containerDestroyed, m_cloneDialog, &CloneDialog::updateContainers);
	connect(m_removerDialog, &RemoverDialog::containerDestroyed, m_restoreSnapDialog, &SnapshotDialog::updateContainers);
	connect(m_removerDialog, &RemoverDialog::containerDestroyed, m_removeSnapDialog, &SnapshotDialog::updateContainers);
}
