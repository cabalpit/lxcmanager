#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QSvgRenderer>
#include <QPixmap>
#include <QTableView>

namespace businesslayer
{
	/*!
	 * \brief The ImageDelegate class
	 * \version 1.0
	 * \since 2021-10-04
	 * \author Peter Cata
	 *
	 * The \c ImageDelegate class will replace the default delegate to custom style delegate.
	 * This class is a subclass of \c QStyleItemDelegate.
	 *
	 * The \c ImageDelegate will replace the value provided in to cell to image picture.
	 * The value must be 0 for stop, 1 for active, 2 for loading.
	 *
	 * The other value will be not considered and \c ImageDelegate will return to \c QStyleItemDelegate default painting.
	 */
	class ImageDelegate : public QStyledItemDelegate
	{
		public:
			explicit ImageDelegate(QObject *parent = nullptr);
			void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

			void setIconSize(int w, int h);
			void setIconSize(const QSize &size);
			QSize iconSize() const;

		private:
			QSize m_size;
			QSvgRenderer *m_svg;
			QPixmap m_play;
			QPixmap m_pause;
			QPixmap m_stop;
			QPixmap m_snapshot;
	};
}

#endif // IMAGEDELEGATE_H
