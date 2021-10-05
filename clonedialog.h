#ifndef CLONEDIALOG_H
#define CLONEDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QStandardItemModel>
#include <QPainter>
#include <QCloseEvent>

#include "loader.h"
#include "alert.h"
#include "businesslayer/style.h"
#include "businesslayer/lxccontainer.h"
#include "businesslayer/configfile.h"

/*!
 * \brief The CloneDialog class
 * \version 1.0
 * \since 2021-09-28
 * \author Peter Cata
 *
 * This class provides a set of input to permit to clone a container.
 */
class CloneDialog : public QDialog
{
		Q_OBJECT
	public:
		CloneDialog(QWidget *parent = nullptr);
		~CloneDialog();

	signals:
		void containerCloned(bool);

	public slots:
		void updateContainers(bool populate);
		void showAlert(bool success);

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void clone();
		void cancelClick();
		void clear();
		void startLoader();
		void stopLoader();

	private:
		businesslayer::LxcContainer *m_lxc;
		lxc_container **m_containers;
		int m_containerCount;
		businesslayer::Style m_css;

		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		Alert *m_alert;
		QLabel *m_containerLabel;
		QLabel *m_copyLabel;
		QLabel *m_cloneTypeLabel;
		QComboBox *m_containersCombo;
		QComboBox *m_cloneTypeCombo;
		QLineEdit *m_newContainerNameLine;

		QPushButton *m_cancel;
		QPushButton *m_create;

		bool m_loading;
		Loader *m_loader;
};

#endif // CLONEDIALOG_H
