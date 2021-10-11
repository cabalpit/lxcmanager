#ifndef LXCWIDGET_H
#define LXCWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include "lxcview.h"

class LxcWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit LxcWidget(QWidget *parent = nullptr);
		~LxcWidget();

		LxcView *view() const;

	signals:

	protected:
		void initObjects();
		void initDisposal();

		void paintEvent(QPaintEvent *event) override;

	private:
		QHBoxLayout *m_layout;
		LxcView *m_view;

};

#endif // LXCWIDGET_H
