#include "abstractwidget.h"

AbstractWidget::AbstractWidget()
{
	m_rotate = 0;
}

void AbstractWidget::spinner(QPainter *painter, QColor color, QPointF position, QRectF spinerRect)
{
	painter->save();

	painter->setPen(QPen(QBrush(color), 5));
	painter->translate(position);
	painter->rotate(m_rotate);

	painter->drawArc( spinerRect, 0, 270 * 16);

	m_rotate += (360 / 12);

	if(m_rotate >= 360)
		m_rotate = 0;

	painter->restore();
}
