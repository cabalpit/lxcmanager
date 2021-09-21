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
		void settingClicked();
		void deleteCTClicked();

	protected:
		void actionsClick();

	private:
		businesslayer::Style m_css;
};

#endif // TOOLBAR_H
