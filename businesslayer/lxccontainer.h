#ifndef LXCCONTAINER_H
#define LXCCONTAINER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "lxc/lxccontainer.h"
#include "lxc/version.h"
#include "logs.h"

#define DEFAULT_FOLDER "/.local/share/lxc"

namespace businesslayer {

	/**
	 * @brief The Container struct
	 *
	 * This struct hold the definition for a new container to create.
	 * To know how to fill this structure report to Lxc server images @see https://us.images.linuxcontainers.org/
	 * each needed column correspond to an attribute of this structure are reported to the table.
	 *
	 * For the hkp attribute by default we use the keyserver ubuntu to sign GPG because the users not installed GPG or not defined on is own machine.
	 * To avoid this matter we provid this attrib that can be filled the url
	 */
	struct Container
	{
		QString name;			/** waits the name of the new container */
		QString distribution;	/** waits the distribution name for the new container */
		QString release;		/** waits the release name for the new container */
		QString arch;			/** waits the architecture name for the new container */
		QString variant;		/** waits the variant name for the new container */
		QString hkp;			/** waits the keyserver url to create a new container hkp://ubuntu.container.com */
	};

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
			void containerStarted(bool);
			void containerStopped(bool);
			void containerDestroyed(bool);
			void containerCreated(bool);

		public slots:
			void setLxcPath(const char *path = NULL);
			bool createContainer(const businesslayer::Container &container);

			bool start(lxc_container *c);
			bool stop(lxc_container *c);
			bool destroy(lxc_container *c);

		protected:

		private:
			char *m_path;
	};
}
#endif // LXCCONTAINER_H
