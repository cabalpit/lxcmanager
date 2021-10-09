#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QRunnable>
#include <QMutex>
#include <QMutexLocker>
#include <QProcess>
#include <QThread>
#include "QDebug"

#include "businesslayer/monitorutils.h"

namespace businesslayer
{
	/*!
	 * \class Monitor
	 * \brief The Monitor class get memory and cpu containers usage.
	 * \version 1.0
	 * \since 2021-10-08
	 * \author Peter Cata
	 *
	 * Runnable class retrieves the informations for each activate containers.
	 * The class reads process and computes cpu usage and memory usage.
	 * This class is thread-safe.
	 */
	class Monitor : public QObject, public QRunnable
	{
			Q_OBJECT
		public:
			explicit Monitor(QObject *parent = nullptr);
			~Monitor();
			void run() override;

		signals:
			void statsResultReady(const QVector<Stats> &);

		public slots:
			void setPids(const QHash<QString, pid_t> &pids);
			void setInterval(uint seconds);
			void interrupt();
			uint interval();

		protected:
			QString program() const;
			QStringList arguments() const;
			QVector<Stats> statisticsReader(const QByteArray &text);

		private:
			QMutex m_mutex;
			QHash<QString, pid_t> m_pids;
			uint m_seconds;
			bool m_interrupt;
			bool m_done;

	};
}
#endif // MONITOR_H
