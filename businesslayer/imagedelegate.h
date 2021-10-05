#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QStyledItemDelegate>

namespace businesslayer
{
	/*!
	 * \brief The ImageDelegate class
	 * \version 1.0
	 * \since 2021-10-04
	 * \author Peter Cata
	 */
	class ImageDelegate : public QStyledItemDelegate
	{
		public:
			explicit ImageDelegate(QObject *parent = nullptr);
			void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	};
}

#endif // IMAGEDELEGATE_H
