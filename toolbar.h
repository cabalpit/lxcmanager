#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QToolBar>
#include <QActionEvent>
#include <QLayout>
#include <QToolButton>
#include <QTimer>

#include "businesslayer/style.h"

class ToolBar : public QToolBar
{
		Q_OBJECT
	public:
		explicit ToolBar(QWidget *parent = nullptr);

		void initDisposal();

	signals:
		void refreshClicked(bool);
		void duplicateClicked(bool);
		void restoreSnapClicked(bool);
		void deleteCTClicked(bool);
		void deleteSnapsClicked(bool);
		void settingClicked(bool);

	protected:

	private:
		businesslayer::Style m_css;
};

#endif // TOOLBAR_H
