#include "toolbar.h"

using namespace businesslayer;

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent)
{
	initDisposal();
}

void ToolBar::initDisposal()
{
	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	setFixedWidth(110);
	setStyleSheet(m_css["toolbar"]);
	setAutoFillBackground(true);
	layout()->setContentsMargins(0, 10, 0, 0);
	layout()->setSizeConstraint(QLayout::SetNoConstraint);

	QFont toolFont("lato-light");
	toolFont.setPointSize(8);

	//TODO remove all objects name
	QAction *refresh = addAction(QIcon(":/icons/refresh_white"), tr("Refresh"));
	refresh->setFont(toolFont);
	refresh->setObjectName("refresh");

	QAction *duplicate = addAction(QIcon(":/icons/copy_white"), tr("Duplicate"));
	duplicate->setFont(toolFont);
	duplicate->setObjectName("duplicate");

	QAction *restorSnap = addAction(QIcon(":/icons/restor_white"), tr("Restor Snapshot"));
	restorSnap->setFont(toolFont);
	restorSnap->setObjectName("restorSnap");

	QAction *deleteCT = addAction(QIcon(":/icons/lxc_minus"), tr("Remove CT"));
	deleteCT->setFont(toolFont);
	deleteCT->setObjectName("deleteCT");

	QAction *deleteSnap = addAction(QIcon(":/icons/remove_white"), tr("Remove Snaps"));
	deleteSnap->setFont(toolFont);
	deleteSnap->setObjectName("deleteSnaps");

	QAction *settings = addAction(QIcon(":/icons/settings_white"), tr("Settings"));
	settings->setFont(toolFont);
	settings->setObjectName("settings");

	// TODO: replace &Slots with lambda expression.
	connect(refresh, &QAction::triggered, this, &ToolBar::actionsClick);
	connect(duplicate, &QAction::triggered, this, &ToolBar::actionsClick);
	connect(restorSnap, &QAction::triggered, this, &ToolBar::actionsClick);
	connect(deleteCT, &QAction::triggered, this, &ToolBar::actionsClick);
	connect(deleteSnap, &QAction::triggered, this, &ToolBar::actionsClick);
	connect(settings, &QAction::triggered, this, &ToolBar::actionsClick);
}

// TODO: remove this method, move to initdisposal lambda expression
void ToolBar::actionsClick()
{
	QAction *action = qobject_cast<QAction *>(QObject::sender());

	if(action->objectName() == "refresh")
			emit refreshClicked(true);

	else if(action->objectName() == "duplicate")
		emit duplicateClicked();

	else if(action->objectName() == "restorSnap")
		emit restoreSnapClicked();

	else if(action->objectName() == "deleteCT")
		emit deleteCTClicked();

	else if(action->objectName() == "deleteSnaps")
		emit deleteSnapsClicked();

	else if(action->objectName() == "settings")
		emit settingClicked();
}
