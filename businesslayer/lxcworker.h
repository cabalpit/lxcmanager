#ifndef LXCWORKER_H
#define LXCWORKER_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

#include "lxc/lxccontainer.h"
#include "lxcutils.h"
#include "logs.h"

namespace businesslayer
{
	/*!
	 * \brief The LxcWorker class
	 * \version 1.0
	 * \since 2021-09-28
	 * \author Peter Cata
	 *
	 * This Worker class start thread which operate consuming operations.
	 * The operations threads are create, start, stop, destroy.
	 *
	 * That methods cosume times and resources that slowed the main gui program.
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
			void doWorkFreeze(lxc_container *c);
			void doWorkUnfreeze(lxc_container *c);
			void doWorkClone(lxc_container *c, const char *name, const int cloneType);
			void doWorkRestore(lxc_container *c, const int snapshotIndex, const char *newName);
			void doWorkDestroy(lxc_container *c);
			void doWorkSnapshot(lxc_container *c, const char *commentPath);
			void doWorkSnapshotDestroy(lxc_container *c, const int snapshotIdx);

		signals:
			void resultCreateReady(bool, const QString &);
			void resultStartReady(bool, const QString &);
			void resultStopReady(bool, const QString &);
			void resultFreezeReady(bool, const QString &);
			void resultUnFreezeReady(bool, const QString &);
			void resultCloneReady(bool);
			void resultRestoreReady(bool, const QString &);
			void resultDestroyReady(bool);
			void resultSnapshotReady(bool);
			void resultSnapshotDestroyReady(bool, const QString &);

		private:
			QMutex m_startMutex;				/*! \brief m_startMutex exlusion avoid concurency */
			QMutex m_stopMutex;					/*! \brief m_stopMutex exlusion avoid concurency */
			QMutex m_freezeMutex;				/*! \brief m_freezeMutex exlusion avoid concurency */
			QMutex m_unfreezeMutex;				/*! \brief m_unfreezeMutex exlusion avoid concurency */
			QMutex m_cloneMutex;				/*! \brief m_cloneMutex exlusion avoid concurency */
			QMutex m_restoreMutex;				/*! \brief m_restoreMutex exlusion avoid concurency */
			QMutex m_destroyMutex;				/*! \brief m_restoreMutex exlusion avoid concurency */
			QMutex m_snapshotMutex;				/*! \brief m_snapshotMutex exlusion avoid concurency */
			QMutex m_destroySnapMutex;			/*! \brief m_restoreMutex exlusion avoid concurency */

	};
}

#endif // LXCWORKER_H
