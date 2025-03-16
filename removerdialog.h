#ifndef REMOVERDIALOG_H
#define REMOVERDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPainter>
#include <QCloseEvent>

#include "loader.h"
#include "alert.h"
#include "businesslayer/lxccontainer.h"
#include "businesslayer/configfile.h"
#include "businesslayer/style.h"

/*!
 * \class RemoverDialog
 * \brief The RemoverDialog class destroy containers.
 * \version 1.0
 * \since 2021-09-25
 * \author Peter Cata
 *
 * The Remover class destroy a selected container. This action cannot be
 * undo after deletation.
 *
 * \note The class will check if the containers contains snapshot and not delete
 * containers until the snapshot are removed.
 */
class RemoverDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit RemoverDialog(QWidget *parent = nullptr);
		~RemoverDialog();

	signals:
		void containerDestroyed(bool);

	public slots:
		void updateContainers(bool populate);
		void showAlert(bool status);

	protected:
		void initObjects();
		void initDisposal();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void closeEvent(QCloseEvent *event) override;

	protected slots:
		void remove();
		void cancelClick();
		void clear();

	private:
		businesslayer::LxcContainer *m_lxc;
		lxc_container **m_containers;
		int m_containersCount;

		QGridLayout *m_layout;
		QLabel *m_infoLabel;
		Alert *m_alert;
		QComboBox *m_containerCombobox;
		QPushButton *m_cancel;
		QPushButton *m_destroy;
		businesslayer::Style m_css;

		Loader *m_loader;
};

#endif // REMOVERDIALOG_H
