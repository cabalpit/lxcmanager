#include "loader.h"

Loader::Loader(QObject *parent): QObject(parent)
{
	m_rotate = 0;
	m_timer.setInterval(1000 * 12 / 360);
	connect(&m_timer, &QTimer::timeout, this, [=] { emit timerChanged(); });
}

Loader::~Loader()
{

}

/*!
 * \brief spinner
 *
 * Spinner is virtual method, it draw an arc using the painter of subclass.
 * The method save the current state, draw arc and restore the state using \c QPainter::save() and QPainter::restrore()
 *
 * \param painter waits the painter to use for drawing arc.
 * \param color waits the color to use for drawing arc.
 * \param position waits the position where to draw.
 * \param spinerRect waist the rect for spinner.
 */
void Loader::spinner(QPainter *painter, QPointF position)
{
	painter->save();

	painter->setPen(QPen(QBrush(m_color), 5));
	painter->translate(position);
	painter->rotate(m_rotate);

	painter->drawArc(m_arcRect, 0, 270 * 16);

	m_rotate += (360 / 12);

	if(m_rotate >= 360)
		m_rotate = 0;

	painter->restore();
}

int Loader::rotate()
{
	return m_rotate;
}

QColor Loader::color()
{
	return m_color;
}

QRectF Loader::arcRect()
{
	return m_arcRect;
}

void Loader::setColor(const QColor &color)
{
	if(m_color == color)
		return;

	m_color = color;
	emit colorChanged(m_color);
}

void Loader::setColor(int r, int g, int b, int a)
{
	QColor color(r, g, b, a);

	if(m_color == color)
		return;

	m_color.setRgb(r, g, b, a);
	emit colorChanged(m_color);
}

void Loader::setArcRect(const QRectF &arcRect)
{
	if(m_arcRect == arcRect)
		return;

	m_arcRect = arcRect;
	emit arcRectChanged(m_arcRect);
}

void Loader::setArcRect(float x, float y, float w, float h)
{
	QRectF rect(x, y, w, h);

	if(m_arcRect == rect)
		return;

	m_arcRect = rect;
	emit arcRectChanged(m_arcRect);
}

void Loader::stop()
{
	m_rotate = 0;
	m_timer.stop();
}

void Loader::start()
{
	m_timer.start();
}




