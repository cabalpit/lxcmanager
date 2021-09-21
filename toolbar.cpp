#include "toolbar.h"

using namespace businesslayer;

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent)
{
	initDisposal();
}

void ToolBar::initDisposal()
{
	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	setFixedWidth(90);
	setStyleSheet(m_css["toolbar"]);
	setAutoFillBackground(true);
	layout()->setContentsMargins(0, 10, 0, 0);
	layout()->setSizeConstraint(QLayout::SetNoConstraint);

	QFont toolFont("lato-light");
	toolFont.setPointSize(8);

	QAction *deleteCT = addAction(QIcon(":/icons/lxc_minus"), tr("Remove CT"));
	deleteCT->setFont(toolFont);
	deleteCT->setObjectName("deleteCT");

	QAction *settings = addAction(QIcon(":/icons/settings_white"), tr("Settings"));
	settings->setFont(toolFont);
	settings->setObjectName("settings");

	connect(settings, &QAction::triggered, this, &ToolBar::actionsClick);
	connect(deleteCT, &QAction::triggered, this, &ToolBar::actionsClick);
}

void ToolBar::actionsClick()
{
	QAction *action = qobject_cast<QAction *>(QObject::sender());

	if(action->objectName() == "settings")
		emit settingClicked();

	if(action->objectName() == "deleteCT")
		emit deleteCTClicked();
}
