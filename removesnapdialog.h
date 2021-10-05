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
#include <QCloseEvent>
#include <QPainter>

#include "loader.h"
#include "alert.h"
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

	public slots:
		void updateContainers(bool populate);
		void showAlert(bool success, const QString &message);
		void removeSnap();

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void populateSnapsView();
		void cancelClick();
		void clear();
		void stopLoader();
		void startLoader();

	private:
		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		Alert *m_alert;
		QLabel *m_containerLabel;
		QLabel *m_snapshotLabel;

		QComboBox *m_containerCombo;
		QListView *m_snapshotView;
		QStandardItemModel m_model;

		QPushButton *m_cancel;
		QPushButton *m_remove;

		bool m_loading;
		Loader *m_loader;

		businesslayer::LxcContainer *m_lxc;
		lxc_container **m_containers;
		int m_containersCount;

		businesslayer::ConfigFile m_config;
		businesslayer::Style m_css;
};

#endif // REMOVESNAPDIALOG_H
