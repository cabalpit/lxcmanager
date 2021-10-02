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
			void containerStarted(bool);
			void containerStopped(bool);
			void containerCloned(bool);
			void containerDestroyed(bool);
			void containerSnapshoted(bool);


		public slots:
			void setLxcPath(const char *path = NULL);
			void createContainer(const businesslayer::Container &container);
			void start(lxc_container *c);
			void stop(lxc_container *c);
			void clone(lxc_container *c, const char *name, const int cloneType);
			void destroy(lxc_container *c);
			void snapshot(lxc_container *c, const char *snapCommentFolder, const char *comment);

		protected:
			void initThread();

		signals:
			void operateCreation(const businesslayer::Container &container);
			void operateStart(lxc_container *);
			void operateStop(lxc_container *);
			void operateClone(lxc_container *c, const char *name, const int cloneType);
			void operateDestroy(lxc_container *);
			void operateSnapshot(lxc_container *, const char *comment);

		private:
			char *m_path;
			QThread m_thread;
			LxcWorker *m_lxcWorker;
	};
}
#endif // LXCCONTAINER_H
