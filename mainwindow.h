#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>

#include "businesslayer/style.h"
#include "toolbar.h"
#include "settingsdialog.h"
#include "removerdialog.h"
#include "clonedialog.h"
#include "creatorwidget.h"
#include "lxcview.h"
#include "snapshotdialog.h"
#include "monitorwidget.h"

/*!
 * \brief The MainWindow class
 * \version 1.4
 * \since 2021-09-23
 *
 * This class create the main window application. The class hold all widgets, dialogs, ... objects.
 */
class MainWindow : public QMainWindow
{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	signals:

	public slots:

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

	private:
		QGridLayout *m_layout;
		QWidget *m_centralWidget;
		ToolBar *m_toolbar;
		SettingsDialog *m_configDialog;
		RemoverDialog *m_removerDialog;
		CloneDialog *m_cloneDialog;
		CreatorWidget *m_creator;
		LxcView *m_lxcview;
		SnapshotDialog *m_restoreSnapDialog;
		SnapshotDialog *m_removeSnapDialog;
		MonitorWidget *m_monitorWidget;

		businesslayer::Style m_css;
};

#endif // MAINWINDOW_H
