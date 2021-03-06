#include "chart.h"


using namespace businesslayer;

/*!
 * \brief Chart::Chart
 *
 * Construct a \c RemoveSnapDialog object with the given \a parent.
 *
 * \param parent waits parent widget, default \a nullptr
 * \param flags waits \c QWindowFlags
 */
Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags flags): QChart(QChart::ChartTypeCartesian, parent, flags), m_pid(0),
	m_cpuSeries(nullptr), m_memSeries(nullptr), m_xAxis(nullptr), m_yAxis(nullptr), m_second(-1), m_step(0), m_maxSecond(60)
{
	QPen cpuPen(QBrush(QColor()), 2);
	QPen memPen(QBrush(QColor()), 2);

	m_xAxis = new QValueAxis(this);
	m_xAxis->setRange(0, 60);
	m_xAxis->setTickCount(7);

	m_yAxis = new QValueAxis(this);
	m_yAxis->setRange(0, 100);
	m_yAxis->setTickCount(6);

	m_cpuSeries = new QSplineSeries(this);
	m_cpuSeries->setPen(cpuPen);

	m_cpuSeries->setName(tr("CPU%"));

	m_memSeries = new QSplineSeries(this);
	m_memSeries->setPen(memPen);

	m_memSeries->setName(tr("MEM%"));

	addSeries(m_cpuSeries);
	addSeries(m_memSeries);
	addAxis(m_xAxis, Qt::AlignBottom);
	addAxis(m_yAxis, Qt::AlignLeft);

	m_cpuSeries->attachAxis(m_xAxis);
	m_cpuSeries->attachAxis(m_yAxis);
	m_memSeries->attachAxis(m_xAxis);
	m_memSeries->attachAxis(m_yAxis);
}

/*!
 * \brief Chart::~Chart destructor
 */
Chart::~Chart()
{

}

/*!
 * \fn Chart::pid
 * \brief Chart::pid getter
 *
 * This method retrieves the pid on monitoring.
 * \return
 */
pid_t Chart::pid() const
{
	return m_pid;
}

/*!
 * \fn Chart::setPid
 * \brief Chart::setPid setter
 *
 * This method sets the pid of container to graph.
 * \param pid waits the container pid to chart.
 */
void Chart::setPid(pid_t pid)
{
	m_pid = pid;
}

/*!
 * \fn Chart::getStep
 * \brief Chart::getStep getter
 *
 * The method retrives the drawing step
 * \return step
 */
int Chart::getStep() const
{
	return m_step;
}

/*!
 * \fn Chart::setStep
 * \brief Chart::setStep
 *
 * This method sets the step to draw the chart the step, ususaly linked to refersh time.
 * \param step waits gap between two point to draw an xaxis.
 */
void Chart::setStep(int step)
{
	m_step = step;
}

/*!
 * \fn Chart::setMaxSecond
 * \brief Chart::setMaxSecond define the max of xaxis
 *
 * This method sets the maximum in second of the xaxis.
 * \param second waits int max in second
 */
void Chart::setMaxSeconde(int second)
{
	m_maxSecond = second;
}

/*!
 * \fn Chart::updateChart
 * \brief Chart::updateChart update chart series.
 *
 * The \c Chart::updateChart add to series the values, and animate the graph.
 *
 * \param containerStat waits the list of \c Businesslayer::Stats of containers.
 */
void Chart::updateChart(const QVector<Stats> &containerStat)
{
	// find the container
	const Stats *it = std::find_if(containerStat.begin(), containerStat.end(), [&](Stats stat) { return (stat.pid == m_pid); });

	if(it)
	{
		if(m_second <= m_maxSecond)
		{
			m_second += m_step;
		}
		else
		{
			QList<QPointF> cpuPoints = m_cpuSeries->points();
			QList<QPointF> memPoints = m_memSeries->points();

			for(int i = 0; i < cpuPoints.length(); i++)
			{
				QPointF cpuNewPt(cpuPoints.at(i).x() - 1, cpuPoints.at(i).y());
				QPointF memNewPt(memPoints.at(i).x() - 1, memPoints.at(i).y());

				m_cpuSeries->replace(cpuPoints.at(i), cpuNewPt);
				m_cpuSeries->replace(memPoints.at(i), memNewPt);
			}

			// remove first point each time to keep low the number of point in series
			m_cpuSeries->remove(cpuPoints.first().rx() - 1, cpuPoints.first().ry());
			m_memSeries->remove(memPoints.first().rx() - 1, memPoints.first().ry());
		}

		m_cpuSeries->append(m_second, it->cpu);
		m_memSeries->append(m_second, it->mem);
	}
}
