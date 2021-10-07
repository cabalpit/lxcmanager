#ifndef SNAPSHOTDIALOG_H
#define SNAPSHOTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPainter>
#include <QCloseEvent>

#include "loader.h"
#include "alert.h"
#include "businesslayer/lxccontainer.h"
#include "businesslayer/configfile.h"
#include "businesslayer/style.h"

/*!
 * \class SnapshotDialog
 * \brief The SnapshotDialog class
 * \version 1.0
 * \since 2021-10-05
 * \author Peter Cata
 *
 * The \c SnapshotDialog class shows the containers which contains the snapshot, previously created.
 * This class can be use for restores containers from snapshot or destroy snapshot,
 * by passing the parametre type to constructor.
 *
 * \note  The \c SnapshotDialog class replace \c RestoreSnapDialog and \c RemoveSnapDialog class, these two class
 * become obsolete and have been removed.
 */
class SnapshotDialog : public QDialog
{
		Q_OBJECT
	public:
		/*!
		 * \enum SnapType
		 * \brief The SnapType enum holds type object to create.
		 *
		 * The \c SnapType holds the type object to creates, the object can be crated are
		 * RESTORE for restore snapshot object, and REMOVE for remove snapshot.
		 */
		enum SnapType { RESTORE, REMOVE };
		explicit SnapshotDialog(SnapType type, QWidget *parent = nullptr);

	signals:

	public slots:

	protected:

	protected slots:

	private:
		SnapType m_type;
};

#endif // SNAPSHOTDIALOG_H
