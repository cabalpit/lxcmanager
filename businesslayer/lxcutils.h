#ifndef LXCUTILS_H
#define LXCUTILS_H

#include <QObject>
#include <QString>

#define DEFAULT_FOLDER "/.local/share/lxc"

namespace businesslayer
{
	/*!
	 * \struct
	 * \brief The Container struct
	 * \version 1.0
	 * \since 2021-09-20
	 * \author Peter Cata
	 *
	 * This struct hold the definition for a new container to create.
	 * To know how to fill this structure report to Lxc server images \see https://us.images.linuxcontainers.org/
	 * each needed column correspond to an attribute of this structure are reported to the table.
	 *
	 * For the hkp attribute by default we use the keyserver ubuntu to sign GPG because the users not installed GPG or not defined on is own machine.
	 * To avoid this matter we provid this attrib that can be filled the url
	 */
	struct Container
	{
			QString name;			/*! \param name waits the name of the new container */
			QString distribution;	/*! \param distribution waits the distribution name for the new container */
			QString release;		/*! \param release waits the release name for the new container */
			QString arch;			/*! \param arch waits the architecture name for the new container */
			QString variant;		/*! \param variant waits the variant name for the new container */
			QString hkp;			/*! \param hkp waits the keyserver url to create a new container \see hkp://ubuntu.container.com */
			bool autostart;			/*! \param autostart waits autostart for containers */
	};
}

Q_DECLARE_METATYPE(businesslayer::Container);

#endif // LXCUTILS_H
