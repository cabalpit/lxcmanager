#include "lxcwidget.h"

/*!
 * \fn LxcWidget::LxcWidget
 * \brief LxcWidget::LxcWidget constructor
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
LxcWidget::LxcWidget(QWidget *parent) : QWidget(parent)
{
	initObjects();
	initDisposal();
}

/*!
 * \fn LxcWidget::~LxcWidget
 * \brief LxcWidget::~LxcWidget destructor
 */
LxcWidget::~LxcWidget()
{
	delete m_view;
	delete m_layout;
}

/*!
 * \fn LxcWidget::view
 * \brief LxcWidget::view getter
 *
 * The method return the lxcview
 * \return \c LxcView object
 */
LxcView *LxcWidget::view() const
{
	return m_view;
}

/*!
 * \brief LxcWidget::initObjects initialize objects.
 *
 * This method creates all objects of this class.
 */
void LxcWidget::initObjects()
{
	m_layout = new QHBoxLayout(this);
	m_view = new LxcView(this);
}

/*!
 * \brief LxcWidget::initDisposal arrange object into layer
 *
 * This method disposes the object into layer.
 */
void LxcWidget::initDisposal()
{
	m_layout->addWidget(m_view);
	setLayout(m_layout);
	setFixedHeight(395);
}

/*!
 * \fn LxcWidget::paintEvent
 * \brief LxcWidget::paintEvent paint background
 *
 * Override method \c QWidget::paintEvent paint background
 *
 * \param event received from \a event.
 */
void LxcWidget::paintEvent(QPaintEvent *event)
{
	QRect backgroundRect(0, 0, geometry().width(), geometry().height());

		QPainter *painter = new QPainter(this);
		painter->setRenderHint(QPainter::Antialiasing);

		QPainterPath path;
		path.addRoundedRect(backgroundRect, 10, 10);
		path.setFillRule(Qt::OddEvenFill);

		painter->save();
		painter->setPen(QPen(QBrush(QColor(255, 255, 255)), 1));
		painter->fillPath(path, QBrush(QColor(255, 255, 255)));
		painter->restore();
		painter->end();

		delete painter;

		QWidget::paintEvent(event);
}
