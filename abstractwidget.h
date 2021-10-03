#ifndef ABSTRACTWIDGET_H
#define ABSTRACTWIDGET_H

#include <QPainter>
#include <QPen>

class AbstractWidget
{
	public:
		AbstractWidget();

	protected:
		virtual void initObjects() = 0;
		virtual void initDisposal() = 0;
		virtual void initConnection() = 0;

		virtual void spiner(QPainter *painter, QColor color, QPointF position, QRectF spinerRect);

	private:
		int m_rotate;
};

#endif // ABSTRACTWIDGET_H
