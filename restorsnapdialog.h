#ifndef RESTORSNAPDIALOG_H
#define RESTORSNAPDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include <QResizeEvent>

#include "businesslayer/style.h"
#include "lxc/lxccontainer.h"

class RestorSnapDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit RestorSnapDialog(QWidget *parent = nullptr);
		~RestorSnapDialog();

	signals:

	public slots:


	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

		void resizeEvent(QResizeEvent *event) override;

	protected slots:
		void populateSnapView(int idx);
		void clear();
		void clearAlert();
		void clearAll();

	private:
		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		QLabel *m_containerLabel;
		QLabel *m_snapLabel;
		QLabel *m_alertLabel;

		QComboBox *m_containerCombo;
		QListView *m_snapListView;
		QStandardItemModel m_model;

		QPushButton *m_cancel;
		QPushButton *m_restor;

		QTimer m_timer;
		businesslayer::Style m_css;
};

#endif // RESTORSNAPDIALOG_H
