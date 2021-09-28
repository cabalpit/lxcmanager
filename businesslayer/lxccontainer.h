#ifndef LXCCONTAINER_H
#define LXCCONTAINER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "lxc/lxccontainer.h"
#include "lxc/version.h"
#include "lxcworker.h"
#include "logs.h"
#include "lxcutils.h"

namespace businesslayer {

	class LxcContainer : public QObject
	{
			Q_OBJECT
		public:
			explicit LxcContainer(QObject *parent = nullptr);
			explicit LxcContainer(const char *path, QObject *parent);
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
			void containerStarted(bool);
			void containerStopped(bool);
			void containerDestroyed(bool);


		public slots:
			void setLxcPath(const char *path = NULL);
			void createContainer(const Container &container);
			void start(lxc_container *c);
			void stop(lxc_container *c);
			void destroy(lxc_container *c);

		protected:
			void initThread();

		signals:
			void operateCreation(const businesslayer::Container &container);
			void operateStart(lxc_container *);
			void operateStop(lxc_container *);
			void operateDestroy(lxc_container *);

		protected slots:
			void startedContainerDone(bool success);
			void stoppedContainerDone(bool success);
			void createdContainerDone(bool success, const QString &message);
			void destroyedContainerDone(bool success);

		private:
			char *m_path;
			QThread m_thread;
			LxcWorker *m_lxcWorker;
	};
}
#endif // LXCCONTAINER_H
