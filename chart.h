#ifndef CHART_H
#define CHART_H

#include <QChart>
#include <QValueAxis>
#include <QSplineSeries>
#include <QVector>
#include <QDebug>

#include "businesslayer/monitorutils.h"

/*!
 * \class Chart
 * \brief The Chart class draw the spline series to chartview monitor.
 * \vesion 1.0
 * \since 2021-10-08
 *
 * The Chart class draw axis and lines to chart view. The lines are cpu and memory usage.
 * The yAxis is bounded from 0 to 100%
 */
class Chart : public QtCharts::QChart
{
		Q_OBJECT
	public:
		explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
		virtual ~Chart();

		const QString &title() const;
		void setTitle(const QString &title);

		pid_t pid() const;
		void setPid(pid_t pid);

		int getStep() const;
		void setStep(int step);

	public slots:
		void updateChart(const QVector<businesslayer::Stats> &containerStat);

	private:
		QString m_title;
		pid_t m_pid;
		QtCharts::QSplineSeries *m_cpuSeries;
		QtCharts::QSplineSeries *m_memSeries;
		QtCharts::QValueAxis *m_xAxis;
		QtCharts::QValueAxis *m_yAxis;
		int m_second;
		int m_step;
};

#endif // CHART_H
