#include "monitor.h"

using namespace businesslayer;

/*!
 * \fn Monitor::Monitor
 * \brief Monitor::Monitor Constructor
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
Monitor::Monitor(QObject *parent): QObject(parent)
{
	m_pids.clear();
	m_seconds = 3;
	m_interrupt = false;
	m_done = false;
}

/*!
 * \brief Monitor::~Monitor destructor
 */
Monitor::~Monitor()
{

}

/*!
 * \fn Monitor::run
 * \brief Monitor::run
 *
 * Override method retrieves the cpu and memory usage for containers
 * over process command. This method is thread-safe.
 */
void Monitor::run()
{
	m_done = false;
	m_interrupt = false;

	forever
	{
		QMutexLocker locker(&m_mutex);

		if(m_interrupt)
			return;

		QProcess process;
		process.start(program(), arguments(), QIODevice::ReadOnly);

		if(!process.waitForFinished())
		{
			QThread::sleep(1);
			continue;
		}

		QByteArray result = process.readAll();
		QVector<Stats> stats = statisticsReader(result);

		if(!stats.isEmpty())
			emit statsResultReady(stats);

		QThread::sleep(m_seconds);
	}

	m_done = true;
}

/*!
 * \fn Monitor::setPids
 * \brief Monitor::setPids containers process id.
 *
 * This method sets the container name and process id.
 *
 * \param pids waits key container name, value containers pid
 */
void Monitor::setPids(const QHash<QString, pid_t> &pids)
{
	if(m_pids != pids)
		m_pids = pids;
}

/*!
 * \fn Monitor::setInterval
 * \brief Monitor::setInterval refresh interval.
 *
 * This method sets the refresh interval before to retreviews values.
 * The best value is 1 second. By default the class use 3 second.
 *
 * \param seconds time in seconds.
 */
void Monitor::setInterval(uint seconds)
{
	if(seconds != 0)
		m_seconds = seconds;
}

/*!
 * \fn Monitor::interrupt
 * \brief Monitor::interrupt stop run method.
 *
 * This method must be called before to destroy the class, it quite
 * the forever loopin.
 */
void Monitor::interrupt()
{
	m_interrupt = true;
}

/*!
 * \fn Monitor::interval
 * \brief Monitor::interval getter
 *
 * This method gets the interval to refresh.
 *
 * \return interval in second.
 */
uint Monitor::interval()
{
	return m_seconds;
}

/*!
 * \fn Monitor::program
 * \brief Monitor::program default \c SHELL
 *
 * This method find the default \c SHELL program defined by the local machine.
 *
 * \return default \c SHELL path.
 */
QString Monitor::program() const
{
	QString prog = qEnvironmentVariable("SHELL");
	return prog;
}

/*!
 * \fn Monitor::arguments
 * \brief Monitor::arguments command to execute.
 *
 * This method built the command to execute to retrievies the ps container list.
 *
 * \return list of arguments to execute.
 */
QStringList Monitor::arguments() const
{
	QStringList args;
	args << "-c";
	args << "ps fax -o user,pid,%cpu,%mem | egrep ^10[0-9]+ | awk '{ print $1,$2,$3,$4 }'";

	return  args;
}

/*!
 * \Monitor::statisticsReader
 * \brief Monitor::statisticsReader converts and computes cpu and mem usage.
 *
 * This method converts \c QByteArray from process to container usage cpu & memory.
 * the line must be separated by '\n' and each infromation must be separate by space.
 *
 * \example 100033 9930 0.0 0.1\n100033 9931 0.0 0.1\n...
 *
 * \param text waits the text to read.
 * \return the statistics for each active containers.
 */
QVector<Stats> Monitor::statisticsReader(const QByteArray &text)
{
	QByteArrayList lines;
	lines.clear();

	QVector<Stats> statistics;
	statistics.clear();

	QHashIterator<QString, pid_t> pidIt(m_pids);
	pid_t next = 0;

	if (text.isEmpty() || m_pids.isEmpty())
		goto out;


	pidIt.next();
	statistics .push_back(Stats { .name = pidIt.key(), .pid = pidIt.value(), .cpu = 0, .mem = 0 });

	if(pidIt.hasNext())
	{
		pidIt.next();
		next = pidIt.value();
	}

	lines = text.split('\n');

	for(int i = 0; i < lines.count(); i++)
	{
		if(lines.at(i).isEmpty())
			continue;

		QByteArrayList columns = lines.at(i).split(' ');

		if(columns.at(1).toInt() == next)
		{
			statistics.push_back(Stats { .name = pidIt.key(), .pid = next, .cpu = columns.at(2).toDouble(), .mem = columns.at(3).toDouble() });

			if(pidIt.hasNext())
			{
				pidIt.next();
				next = pidIt.value();
			}
		}
		else
		{
			statistics.last().cpu += columns.at(2).toDouble();
			statistics.last().mem += columns.at(3).toDouble();
		}
	}

out:
	return statistics;
}
