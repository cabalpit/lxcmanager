#ifndef LXCVIEW_H
#define LXCVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QInputDialog>

#include "businesslayer/lxccontainer.h"
#include "businesslayer/style.h"
#include "businesslayer/configfile.h"

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
		void lxcCreated(bool, const QString &message = QString());
		void lxcCloned(bool, const QString &message = QString());
		void lxcSnapRestored(bool, const QString &message = QString());
		void lxcDestroyed(bool, const QString &message = QString());
		void populateChanged(const QStandardItemModel &);
		void lxcSnapDetroyed(bool, const QString &message = QString());

	public slots:
		void populateModel(bool populate = true);
		void createContainer(const QMap<QString, QString> &container);
		void cloneContainer(const int idx, const QString &name, const int cloneType);
		void restoreSnapshot(const int containerIdx, const int snapshotIdx, const QString &newName);
		void destroyContainer(int idx);
		void destroySnap(const int containerIdx, const int snapshotIdx);

	protected:
		void initObjects();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;

	protected slots:
		void messageStart(bool success);
		void messageStop(bool success);
		void messageCreate(bool success, const QString &message);
		void messageClone(bool success);
		void messageRestored(bool success, const QString &message);
		void messageDestroy(bool success);
		void messageSnapshot(bool success);
		void messageSnapDestroy(bool success, const QString &message);

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
