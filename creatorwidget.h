#ifndef CREATORWIDGET_H
#define CREATORWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>

#include "businesslayer/style.h"

class CreatorWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit CreatorWidget(QWidget *parent = nullptr);
		~CreatorWidget();

	signals:
		void createClicked(const QMap<QString, QString> &);

	public slots:
		void containerCreated(bool create);

	protected:
		void initObjects();
		void initConnections();

	private:
		businesslayer::Style m_css;
};

#endif // CREATORWIDGET_H
