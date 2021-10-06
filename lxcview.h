#ifndef LXCVIEW_H
#define LXCVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>
#include <QInputDialog>

#include "businesslayer/lxccontainer.h"
#include "businesslayer/configfile.h"
#include "businesslayer/imagedelegate.h"
#include "businesslayer/style.h"

/*!
 * \brief The LxcView class
 * \version 1.0
 * \since 2021-09-27
 * \author Peter Cata
 *
 * This class display all containers list. It provides some action on containers.
 * Start, stop, snapshot autorestart and freeze unfreeze container.
 *
 * LxcView when is update it emit a signal to alert all connect class that the LxcView class
 * has been updated.
 */
class LxcView : public QTableView
{
		Q_OBJECT
	public:
		explicit LxcView(QWidget *parent = nullptr);
		~LxcView();

	signals:
		void snapshotCreated(bool);

	public slots:
		void populateModel(bool populate = true);

	protected:
		void initObjects();
		void initConnections();

		void resizeEvent(QResizeEvent *event) override;

	protected slots:
		void messageStart(bool status);
		void messageStop(bool status);
		void messageSnapshot(bool status);
		void messageFreeze(bool status);
		void messageUnFreeze(bool status);
		void changes(const QModelIndex &index);

	private:
		QStandardItemModel m_model;
		businesslayer::LxcContainer *m_lxc;
		lxc_container **m_containers;
		int m_allCount;
		businesslayer::Style m_css;
		businesslayer::ConfigFile *m_config;

};

#endif // LXCVIEW_H
