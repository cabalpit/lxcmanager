#ifndef RESTORESNAPDIALOG_H
#define RESTORESNAPDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include <QPainter>
#include <QCloseEvent>

#include "loader.h"
#include "alert.h"
#include "lxc/lxccontainer.h"
#include "businesslayer/lxccontainer.h"
#include "businesslayer/configfile.h"
#include "businesslayer/style.h"

class RestoreSnapDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit RestoreSnapDialog(QWidget *parent = nullptr);
		~RestoreSnapDialog();

	signals:
		void restored(bool);

	public slots:
		void updateContainers(bool populate);
		void showAlert(bool success, const QString &message);


	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void populateSnapView();
		void cancelClick();
		void clear();
		void clearAll();
		void restore();
		void stopSpinner();
		void startSpinner();

	private:
		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		QLabel *m_containerLabel;
		QLabel *m_snapLabel;
		QLabel *m_newNameLabel;
		Alert *m_alert;

		QComboBox *m_containerCombo;
		QListView *m_snapListView;
		QStandardItemModel m_model;

		QLineEdit *m_newNameLienEdit;
		QPushButton *m_cancel;
		QPushButton *m_restore;

		businesslayer::LxcContainer *m_lxc;
		lxc_container **m_containers;
		int m_containersCount;

		businesslayer::Style m_css;

		bool m_loading;
		Loader *m_loader;
};

#endif // RESTORESNAPDIALOG_H
