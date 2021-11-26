#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QToolBar>
#include <QActionEvent>
#include <QLayout>
#include <QToolButton>
#include <QTimer>

#include "businesslayer/style.h"

/*!
 * \class ToolBar
 * \brief The ToolBar class
 * \since 2021-09-23
 * \version 1.2
 * \author Peter Cata
 *
 * The \c ToolBar class has the action menu buttons. It is the subclass of \c QToolBar.
 * It opens the differents widget window dialog or emit signals to other widget.
 *
 * The actions are :
 * \list
 *		\li Refresh containers list,
 *		\li Duplicate containers,
 *		\li Restore containers,
 *		\li Delete containers,
 *		\li Delete Snaphot
 *		\li Settings
 * \endlist
 *
 * The \ToolBar class use \c QAction to add button.
 *
 */
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
		void about(bool);

	protected:

	private:
		businesslayer::Style m_css;
};

#endif // TOOLBAR_H
