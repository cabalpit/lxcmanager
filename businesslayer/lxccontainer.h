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

	class LxcContainer : public QObject
	{
			Q_OBJECT
		public:
			explicit LxcContainer(QObject *parent = nullptr);
			~LxcContainer();

			void init();
			char *lxcPath() const;

			QString lxcVersion() const;
			int lxcCountActive() const;
			int lxcCountAll() const;

		signals:

		public slots:
			void setLxcPath(const char *path = NULL);

		protected:
			int m_countAll;
			int m_countActive;

			char *m_path;
			lxc_container **m_allContainerCrets;
			char **m_allContainerNames;
			lxc_container **m_activeContainerCrets;
			char **m_activeContainerNames;

		private:
			void errors(const QString &methodName, const QString &error);

	};
}
#endif // LXCCONTAINER_H
