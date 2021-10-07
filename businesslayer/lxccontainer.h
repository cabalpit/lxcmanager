#ifndef LXCCONTAINER_H
#define LXCCONTAINER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QVector>

#include "lxc/lxccontainer.h"
#include "lxc/version.h"
#include "lxcworker.h"
#include "logs.h"
#include "lxcutils.h"

namespace businesslayer
{
	/*!
	 * \brief The LxcContainer class
	 * \version 1.0
	 * \since 2021-09-20
	 * \author Peter Cata
	 *
	 * This class provides a set of lxc container access. The class can list, create, remove, count, start, stop, freeze, unfreeze, snapshot, clone Containers.
	 *
	 * This class work in paralelle mode with worker class. The class call worker class to triggrer lxc action.
	 * Doing this log work by threading task offer a better reliability and stability.
	 */
	class LxcContainer : public QObject
	{
			Q_OBJECT
		public:
			explicit LxcContainer(QObject *parent = nullptr);
			explicit LxcContainer(const char *path, QObject *parent = nullptr);
			~LxcContainer();

			char *lxcPath() const;
			QString lxcVersion() const;
			int lxcCountActives() const;
			int lxcCountAll() const;

			lxc_container **activeContainersList() const;
			lxc_container **allContainersList() const;
			char **activeContainersName() const;
			char **allContainersName() const;

		signals:
			void containerCreated(bool, const QString &);
			void containerStarted(bool, const QString &);
			void containerStopped(bool, const QString &);
			void containerFreezed(bool, const QString &);
			void containerUnfreezed(bool, const QString &);
			void containerCloned(bool);
			void containerSnapshoted(bool);
			void containerRestrored(bool, const QString &);
			void containerDestroyed(bool);
			void containerSnapshotDestroyed(bool, const QString &);


		public slots:
			void setLxcPath(const char *path = NULL);
			void createContainer(const businesslayer::Container &container);
			void start(lxc_container *c);
			void stop(lxc_container *c);
			void freeze(lxc_container *c);
			void unfreeze(lxc_container *c);
			void clone(lxc_container *c, const char *name, const int cloneType);
			void snapshot(lxc_container *c, const char *snapCommentFolder, const char *comment);
			void restoreSnapshot(lxc_container *c, const int snapshotIndex, const char *newName);
			void destroy(lxc_container *c);
			void snapshotDestroy(lxc_container *c, const int snapshotIdx);

			bool isStartauto(lxc_container *c);
			void setStartauto(lxc_container *c, bool state);
			int containerExists(const char *name);

		protected:
			void initThread();

		signals:
			void operateCreation(const businesslayer::Container &container);
			void operateStart(lxc_container *);
			void operateStop(lxc_container *);
			void operateFreeze(lxc_container *c);
			void operateUnfreeze(lxc_container *c);
			void operateClone(lxc_container *c, const char *name, const int cloneType);
			void operateRestore(lxc_container *c, const int snapshotIndex, const char *newName);
			void operateDestroy(lxc_container *);
			void operateSnapshot(lxc_container *, const char *commentPath);
			void operateSnapshotDestroy(lxc_container *, const int);

		private:
			char *m_path;
			QThread m_thread;
			LxcWorker *m_lxcWorker;
	};
}
#endif // LXCCONTAINER_H
