#ifndef ABSTRACTWIDGET_H
#define ABSTRACTWIDGET_H

#include <QPainter>
#include <QPen>

/*!
 * \brief The AbstractWidget class
 *
 * This class implement \c AbstractWidget class, Subclasses of this class handle user actions and
 * drawing spinner loader. It ensures to implement minimun of methods, \a initObjects(), \a initDisposal()
 * and \a initConnections().
 *
 * AbstractWidget provides a support and ensure to create homogenous classes.
 */
class AbstractWidget
{
	public:
		AbstractWidget();

	protected:
		/*!
		 * \brief initObjects
		 *
		 * This pure method must be implements in subclass.
		 * It initializes objects of class.
		 */
		virtual void initObjects() = 0;

		/*!
		 * \brief initDisposal
		 *
		 * This pure method must be implements in subclass.
		 * It initializes the disposition of the elements on ui.
		 */
		virtual void initDisposal() = 0;

		/*!
		 * \brief initConnections
		 *
		 * This pure method must be implements in subclass.
		 * It initializes connections of the objects in the class.
		 */
		virtual void initConnections() = 0;

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
		virtual void spinner(QPainter *painter, QColor color, QPointF position, QRectF spinerRect);

	private:
		/*!
		 * \brief m_rotate hold rotation
		 */
		int m_rotate;
};

#endif // ABSTRACTWIDGET_H
