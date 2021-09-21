#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include "toolbar.h"
#include "configdialog.h"

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
		ToolBar *m_toolbar;
		ConfigDialog *m_configDialog;
};

#endif // MAINWINDOW_H
