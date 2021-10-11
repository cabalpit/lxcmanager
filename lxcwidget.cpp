#include "lxcwidget.h"

LxcWidget::LxcWidget(QWidget *parent) : QWidget(parent)
{
	initObjects();
	initDisposal();
}

LxcWidget::~LxcWidget()
{
	delete m_view;
}

LxcView *LxcWidget::view() const
{
	return m_view;
}

void LxcWidget::initObjects()
{
	m_layout = new QHBoxLayout(this);
	m_view = new LxcView(this);
}

void LxcWidget::initDisposal()
{
	m_layout->addWidget(m_view);
	setLayout(m_layout);
	setFixedHeight(395);
}

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
