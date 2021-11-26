#include "loader.h"

/*!
 * \brief Loader::Loader
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
Loader::Loader(QObject *parent): QObject(parent)
{
	m_rotate = 0;
	m_isStart = false;
	m_timer.setInterval(1000 * 12 / 360);
	connect(&m_timer, &QTimer::timeout, this, [=] { emit timerChanged(); });
}

/*!
 * \brief Loader::~Loader
 *
 * Default destructor
 */
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

	painter->setPen(QPen(QBrush(m_color), 3));
	painter->translate(position);
	painter->rotate(m_rotate);

	painter->drawArc(m_arcRect, 0, 180 * 16);

	m_rotate += (360 / 12);

	if(m_rotate >= 360)
		m_rotate = 0;

	painter->restore();
}

/*!
 * \brief Loader::rotate
 *
 * Get rotation value
 * \return rotation value is in degree.
 */
int Loader::rotate() const
{
	return m_rotate;
}

/*!
 * \brief Loader::color
 *
 * Get the color of loader.
 *
 * \return \c QColor
 */
QColor Loader::color() const
{
	return m_color;
}

/*!
 * \brief Loader::arcRect
 *
 * Get the arc rect of loader.
 * \return \c QRectF
 */
QRectF Loader::arcRect() const
{
	return m_arcRect;
}

/*!
 * \brief Loader::setColor
 *
 * Set loader color.
 *
 * \param color waits loader \a color.
 */
void Loader::setColor(const QColor &color)
{
	if(m_color == color)
		return;

	m_color = color;
	emit colorChanged(m_color);
}

/*!
 * \brief Loader::setColor
 *
 * Set color of loader.
 *
 * \param r waits red color 0 -> 255
 * \param g waits green color 0 -> 255
 * \param b waits blue color 0 -> 255
 * \param a waits alpha 0 -> 255
 */
void Loader::setColor(int r, int g, int b, int a)
{
	QColor color(r, g, b, a);

	if(m_color == color)
		return;

	m_color.setRgb(r, g, b, a);
	emit colorChanged(m_color);
}

/*!
 * \brief Loader::setArcRect
 *
 * Set arc size and position.
 *
 * \param arcRect waits \c QRectF
 */
void Loader::setArcRect(const QRectF &arcRect)
{
	if(m_arcRect == arcRect)
		return;

	m_arcRect = arcRect;
	emit arcRectChanged(m_arcRect);
}

/*!
 * \brief Loader::setArcRect
 *
 * Set arc size and position.
 *
 * \param x waits position on x from top.
 * \param y waits position on y from top.
 * \param w waits width.
 * \param h waits height.
 */
void Loader::setArcRect(float x, float y, float w, float h)
{
	QRectF rect(x, y, w, h);

	if(m_arcRect == rect)
		return;

	m_arcRect = rect;
	emit arcRectChanged(m_arcRect);
}

/*!
 * \brief Loader::stop
 *
 * Stop loader
 */
void Loader::stop()
{
	m_rotate = 0;
	m_isStart = false;
	m_timer.stop();
}

/*!
 * \brief Loader::start
 *
 * Start loader.
 */
void Loader::start()
{
	m_rotate = 0;
	m_isStart = true;
	m_timer.start();
}

/*!
 * \fn Loader::isStart
 * \brief Loader::isStart check loader state.
 *
 * The \c isStart method check the loader state.
 *
 * \return true if is running otherwize false.
 */
bool Loader::isLoading()
{
	return m_isStart;
}






