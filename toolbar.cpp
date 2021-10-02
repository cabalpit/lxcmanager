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

	QAction *refresh = addAction(QIcon(":/icons/refresh_white"), tr("Refresh"));
	refresh->setFont(toolFont);

	QAction *duplicate = addAction(QIcon(":/icons/copy_white"), tr("Duplicate"));
	duplicate->setFont(toolFont);

	QAction *restorSnap = addAction(QIcon(":/icons/restor_white"), tr("Restor Snapshot"));
	restorSnap->setFont(toolFont);

	QAction *deleteCT = addAction(QIcon(":/icons/lxc_minus_white"), tr("Remove CT"));
	deleteCT->setFont(toolFont);

	QAction *deleteSnap = addAction(QIcon(":/icons/remove_white"), tr("Remove Snaps"));
	deleteSnap->setFont(toolFont);

	QAction *settings = addAction(QIcon(":/icons/settings_white"), tr("Settings"));
	settings->setFont(toolFont);


	connect(refresh, &QAction::triggered, this, [=] { emit refreshClicked(true); });
	connect(duplicate, &QAction::triggered, this, [=] { emit duplicateClicked(true); });
	connect(restorSnap, &QAction::triggered, this, [=] { emit restoreSnapClicked(true); });
	connect(deleteCT, &QAction::triggered, this, [=] { emit deleteCTClicked(true); });
	connect(deleteSnap, &QAction::triggered, this, [=] { emit deleteSnapsClicked(true); });
	connect(settings, &QAction::triggered, this, [=] { emit settingClicked(true); });
}
