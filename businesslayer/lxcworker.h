#ifndef LXCWORKER_H
#define LXCWORKER_H

#include <QObject>
#include <QDebug>
#include <QMutex>

#include "lxc/lxccontainer.h"
#include "lxcutils.h"
#include "logs.h"

namespace businesslayer
{
	/**
	 * @brief The LxcWorker class
	 *
	 * This Worker class start thread which operate consuming operations.
	 * The operations threads are create, start, stop, destroy.
	 *
	 * That methods cosume times and resources that slowed the main gui program.
	 *
	 * @version 1.0
	 * @since 2021-09-28
	 * @author Pierrec
	 */
	class LxcWorker : public QObject
	{
			Q_OBJECT
		public:
			explicit LxcWorker(QObject *parent = nullptr);
			~LxcWorker();

		public slots:
			void doWorkCreate(const businesslayer::Container &container);
			void doWorkStart(lxc_container *c);
			void doWorkStop(lxc_container *c);
			void doWorkClone(lxc_container *c, const char *name, const int cloneType);
			void doWorkRestore(lxc_container *c, const int snapshotIndex, const char *newName);
			void doWorkDestroy(lxc_container *c);
			void doWorkSnapshot(lxc_container *c, const char *commentPath);
			void doWorkSnapshotDestroy(lxc_container *c, const int snapshotIdx);

		signals:
			void resultCreateReady(bool, const QString &);
			void resultStartReady(bool);
			void resultStopReady(bool);
			void resultCloneReady(bool);
			void resultRestoreReady(bool, const QString &);
			void resultDestroyReady(bool);
			void resultSnapshotReady(bool);
			void resultSnapshotDestroyReady(bool, const QString &);

		private:
			QMutex m_mutex;

	};
}

#endif // LXCWORKER_H
