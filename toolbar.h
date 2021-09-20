#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QObject>

#include "businesslayer/style.h"

class ToolBar : public QToolBar
{
		Q_OBJECT
	public:
		explicit ToolBar(QWidget *parent = nullptr);

		void initDisposal();


	private:
		businesslayer::Style m_css;
};

#endif // TOOLBAR_H
