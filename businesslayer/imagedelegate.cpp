#include "imagedelegate.h"

using namespace businesslayer;

/*!
 * \brief ImageDelegate::ImageDelegate
 *
 * Construct a \c ImageStatus object with the given parent.
 * And set default size image to 24x24.
 *
 * \param parent waits parent widget, default \a nullptr
 */
ImageDelegate::ImageDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
	m_size.setWidth(24);
	m_size.setHeight(24);

	m_svg = new QSvgRenderer(QString(":/icons/loader"), parent) ;
	m_play.load(":/icons/play_black");
	m_pause.load(":/icons/pause_black");
	m_stop.load(":/icons/stop_black");
	m_snapshot.load(":/icons/snapshot_black");

	connect(m_svg, &QSvgRenderer::repaintNeeded, this, [=] { qobject_cast<QTableView *>(parent)->viewport()->update(); });
}

/*!
 * \brief ImageDelegate::paint
 *
 * Override method \fn QStyledItemDelegate::paint. This method will draw the correst ponding image to the value
 * provided by the default delegate.
 *
 * if the value is not valid the method will transfere the data to the default \fn QStyledItemDelegate::paint.
 *
 * \param painter
 * \param option
 * \param index
 */
void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if(index.column() > 3 && index.data().toInt() < 3)
	{
		QStyleOptionViewItem opt = option;
		initStyleOption(&opt, index);

		painter->save();

		int value = index.data().toInt();
		QRect bounds(opt.rect.center().x() - m_size.width() / 2, opt.rect.center().y() - m_size.height() / 2, m_size.width(), m_size.height());

		if(value == 2)
		{
			// svg spinner render.
			m_svg->render(painter, bounds);
		}
		else if(index.column() == 4 && value == 0)
		{
			// play render if stop or frozen
			painter->drawPixmap(bounds, m_play);
		}
		else if(index.column() == 4 && value == 1)
		{
			// pause render if container running
			painter->drawPixmap(bounds, m_pause);
		}
		else if(index.column() == 5)
		{
			// stop render icon
			painter->drawPixmap(bounds, m_stop);
		}
		else if(index.column() == 6)
		{
			// snapshot
			painter->drawPixmap(bounds, m_snapshot);
		}

		painter->restore();
	}
	else
		QStyledItemDelegate::paint(painter, option, index);
}

/*!
 * \brief ImageDelegate::setIconSize
 *
 * This method sets default icon size.
 *
 * \param w waits width
 * \param h waist height
 */
void ImageDelegate::setIconSize(int w, int h)
{
	m_size = QSize(w, h);
}

/*!
 * \brief ImageDelegate::setIconSize
 *
 * This method sets default icon size.
 *
 * \param size waits icon size.
 */
void ImageDelegate::setIconSize(const QSize &size)
{
	m_size = size;
}

/*!
 * \brief ImageDelegate::iconSize
 *
 * This method return the icon size.
 * \return \c QSize
 */
QSize ImageDelegate::iconSize() const
{
	return m_size;
}
