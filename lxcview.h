#ifndef LXCVIEW_H
#define LXCVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>

#include "businesslayer/lxccontainer.h"
#include "businesslayer/style.h"

class LxcView : public QTableView
{
		Q_OBJECT
	public:
		explicit LxcView(QWidget *parent = nullptr);
		~LxcView();

	signals:
		void lxcCreated(bool);


	public slots:
		void createContainer(const QStringList &container);
		void destroyContainer();


	protected:
		void initModel();
		void startContainer();
		void stopContainer();
		void configContainer();

	private:
		QStandardItemModel m_model;
		businesslayer::LxcContainer *m_lxc;
		businesslayer::Style m_css;

};

#endif // LXCVIEW_H
