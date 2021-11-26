#ifndef MONITORUTILS_H
#define MONITORUTILS_H

#include <QObject>

namespace businesslayer
{
	/*!
	 * \struct Stats
	 * \brief The Stats struct holds container for statistics usage.
	 *
	 * This structure hold statistics usage for container.
	 * The structure contains the name, pid, cpu, and mem.
	 */
	struct Stats
	{
		QString name;			/*! \brief name waits container name. */
		pid_t pid;				/*! \brief pid waits container pid */
		double cpu;				/*! \brief cpu holds cpu usage */
		double mem;				/*! \brief mem holds memory usage */
	};
}

Q_DECLARE_METATYPE(businesslayer::Stats);

#endif // MONITORUTILS_H
