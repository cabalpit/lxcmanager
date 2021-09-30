#ifndef LXCVIEW_H
#define LXCVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QInputDialog>

#include "businesslayer/lxccontainer.h"
#include "businesslayer/style.h"
#include "businesslayer/configfile.h"

class LxcView : public QTableView
{
		Q_OBJECT
	public:
		explicit LxcView(QWidget *parent = nullptr);
		~LxcView();

	signals:
		void lxcCreated(bool, const QString &message = QString());
		void lxcCloned(bool, const QString &message = QString());
		void lxcDestroyed(bool, const QString &message = QString());
		void populateChanged(const QStandardItemModel &);


	public slots:
		void populateModel(bool populate = true);
		void createContainer(const QMap<QString, QString> &container);
		void cloneContainer(const int idx, const QString &name, const int cloneType);
		void destroyContainer(int idx);


	protected:
		void initObjects();
		void initConnections();

		void paintEvent(QPaintEvent *event) override;
		void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

	protected slots:
		void messageStart(bool success);
		void messageStop(bool success);
		void messageCreate(bool success);
		void messageClone(bool success);
		void messageDestroy(bool success);
		void messageSnapshot(bool success);

	private:
		QStandardItemModel m_model;
		businesslayer::LxcContainer *m_lxc;
		lxc_container **m_containers;
		businesslayer::Style m_css;
		businesslayer::ConfigFile *m_config;

};

#endif // LXCVIEW_H
