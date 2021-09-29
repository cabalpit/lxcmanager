#ifndef LXCWORKER_H
#define LXCWORKER_H

#include <QObject>
#include <QDebug>

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
			void doWorkDestroy(lxc_container *c);

		signals:
			void resultCreateReady(bool, const QString &);
			void resultStartReady(bool);
			void resultStopReady(bool);
			void resultCloneReady(bool);
			void resultDestroyReady(bool);

		private:

	};
}

#endif // LXCWORKER_H
