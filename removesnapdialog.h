#ifndef REMOVESNAPDIALOG_H
#define REMOVESNAPDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTimer>
#include <QCloseEvent>
#include <QPainter>

#include "businesslayer/lxccontainer.h"
#include "businesslayer/configfile.h"
#include "businesslayer/style.h"

class RemoveSnapDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit RemoveSnapDialog(QWidget *parent = nullptr);
		~RemoveSnapDialog();

	signals:
		void snapRemoved(const int containerIdx, const int snapshotIdx);

	public slots:
		void populateContainer(bool populate);
		void showAlert(bool success, const QString &message);
		void removeSnap();

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void cancelClick();
		void clear();
		void clearAlert();
		void stopLoader();
		void startLoader();

	private:
		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		QLabel *m_alertLabel;
		QLabel *m_containerLabel;
		QLabel *m_snapshotLabel;

		QComboBox *m_containerCombo;
		QListView *m_snapshotView;
		QStandardItemModel m_model;

		QPushButton *m_cancel;
		QPushButton *m_remove;

		QTimer m_timer;
		int m_spinnerRotate;
		bool m_loading;

		lxc_container **m_containers;
		int m_containersCount;

		businesslayer::ConfigFile m_config;
		businesslayer::Style m_css;
};

#endif // REMOVESNAPDIALOG_H
