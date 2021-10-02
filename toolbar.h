#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QToolBar>
#include <QActionEvent>
#include <QLayout>
#include <QToolButton>

#include "businesslayer/style.h"

class ToolBar : public QToolBar
{
		Q_OBJECT
	public:
		explicit ToolBar(QWidget *parent = nullptr);

		void initDisposal();

	signals:
		void refreshClicked(bool);
		void settingClicked();
		void duplicateClicked();
		void deleteCTClicked();
		void deleteSnapsClicked();

	protected:
		void actionsClick();

	private:
		businesslayer::Style m_css;
};

#endif // TOOLBAR_H
