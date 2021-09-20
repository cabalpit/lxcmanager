#include "toolbar.h"

using namespace businesslayer;

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent)
{
	initDisposal();
}

void ToolBar::initDisposal()
{
	addAction(QIcon(":/icons/settings_white"), tr("Settings"));


	setFixedWidth(70);
	setStyleSheet(m_css["toolbar"]);
	setAutoFillBackground(true);
}
