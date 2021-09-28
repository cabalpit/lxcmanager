#ifndef LXCWORKER_H
#define LXCWORKER_H

#include <QObject>
#include <QDebug>

#include "lxc/lxccontainer.h"
#include "lxcutils.h"
#include "logs.h"

namespace businesslayer
{
	class LxcWorker : public QObject
	{
			Q_OBJECT
		public:
			explicit LxcWorker(QObject *parent = nullptr);
			~LxcWorker();

		public slots:
			void doWorkStart(lxc_container *c);
			void doWorkStop(lxc_container *c);
			void doWorkCreate(const Container &container);

		signals:
			void resultStartReady(bool);
			void resultStopReady(bool);
			void resultCreateReady(bool, const QString &);

		private:

	};
}

#endif // LXCWORKER_H
