#include "lxcwidget.h"

LxcWidget::LxcWidget(QWidget *parent) : QWidget(parent)
{

}

LxcWidget::~LxcWidget()
{
	delete m_view;
}

LxcView *LxcWidget::view() const
{
	return m_view;
}

void LxcWidget::paintEvent(QPaintEvent *event)
{

}
