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
 * \author Peter Cata
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

		pid_t pid() const;
		void setPid(pid_t pid);

		int getStep() const;
		void setStep(int step);

		void setMaxSeconde(int second = 60);

	public slots:
		void updateChart(const QVector<businesslayer::Stats> &containerStat);

	private:
		pid_t m_pid;
		QtCharts::QSplineSeries *m_cpuSeries;
		QtCharts::QSplineSeries *m_memSeries;
		QtCharts::QValueAxis *m_xAxis;
		QtCharts::QValueAxis *m_yAxis;
		int m_second;
		int m_step;
		int m_maxSecond;
};

#endif // CHART_H
