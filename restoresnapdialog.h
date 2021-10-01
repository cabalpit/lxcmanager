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

#include "businesslayer/lxccontainer.h"
#include "businesslayer/style.h"
#include "lxc/lxccontainer.h"

class RestoreSnapDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit RestoreSnapDialog(QWidget *parent = nullptr);
		~RestoreSnapDialog();

	signals:
		void restored(const int, const int, const QString &);

	public slots:
		void updateContainers();
		void showAlert(bool success, const QString &message);


	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void populateSnapView();
		void clear();
		void clearAlert();
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
		QLabel *m_alertLabel;

		QComboBox *m_containerCombo;
		QListView *m_snapListView;
		QStandardItemModel m_model;

		QLineEdit *m_newNameLienEdit;
		QPushButton *m_cancel;
		QPushButton *m_restore;

		businesslayer::Style m_css;
		lxc_container **m_containers;
		int m_containersCount;

		QTimer m_timer;
		bool m_loading;
		int m_spinnerRotate;
};

#endif // RESTORESNAPDIALOG_H
