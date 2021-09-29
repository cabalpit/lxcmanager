#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>

#include "businesslayer/style.h"
#include "toolbar.h"
#include "configdialog.h"
#include "removerdialog.h"
#include "clonedialog.h"
#include "creatorwidget.h"
#include "lxcview.h"

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
		ConfigDialog *m_configDialog;
		RemoverDialog *m_removerDialog;
		CloneDialog *m_cloneDialog;
		CreatorWidget *m_creator;
		LxcView *m_lxcview;
		businesslayer::Style m_css;
};

#endif // MAINWINDOW_H
