#include "monitorwidget.h"

using namespace businesslayer;
using namespace QtCharts;

/*!
 * \fn MonitorWidget::MonitorWidget
 * \brief MonitorWidget::MonitorWidget	Constructor
 *
 * Construct a \c RemoveSnapDialog object with the given parent.
 *
 * \param parent waits parent widget, default \a nullptr
 */
MonitorWidget::MonitorWidget(QWidget *parent) : QWidget(parent)
{
	m_layout = new QGridLayout(this);
	m_lxc = new LxcContainer(this);
	m_monitor = new Monitor(this);
	m_monitor->setInterval(1);

	setStyleSheet(m_css["main"]);
	setLayout(m_layout);

	updateMonitors(true);
}

/*!
 * \brief MonitorWidget::~MonitorWidget destructor
 */
MonitorWidget::~MonitorWidget()
{
	delete m_lxc;
	delete m_layout;

	m_monitor->interrupt();
	QThreadPool::globalInstance()->waitForDone();
}

/*!
 * \fn MonitorWidget::updateMonitors
 * \brief MonitorWidget::updateMonitors update monitor list.
 *
 * This method construct all objects and connect chart to monitor.
 * \param update waits true to update otherwize false.
 */
void MonitorWidget::updateMonitors(bool update)
{
	if(!update)
		return;

	// removes all widget from grid
	if(m_views.size())
	{
		m_monitor->interrupt();

		disconnect(m_monitor, nullptr, nullptr, nullptr);
		QThreadPool::globalInstance()->waitForDone();

		if(m_views.length())
		{
			for(int i = 0; i < m_views.length(); i++)
			{
				m_layout->removeWidget(m_views.at(i));

				delete m_charts.at(i);
				delete m_views.at(i);
			}

			m_charts.clear();
			m_views.clear();
		}
	}

	lxc_container **actives = m_lxc->activeContainersList();
	int count = m_lxc->lxcCountActives();
	QMap<pid_t, QString> pids;

	if(count)
	{
		int row = 0, col = 0;
		QSize viewSize = monitorSize(count);

		for (int i = 0; i < count; i++)
		{
			QString name = actives[i]->name;
			pid_t pid = actives[i]->init_pid(actives[i]);

			pids.insert(pid, name);

			Chart *chart = new Chart;
			chart->setTheme(QChart::ChartThemeBlueCerulean);
			chart->setAnimationOptions(QChart::SeriesAnimations);
			chart->setPid(pid);
			chart->setTitle(name);
			chart->setStep(1);

			QChartView *view = new QChartView(chart, this);
			view->setRenderHint(QPainter::Antialiasing);
			view->setObjectName(name);
			view->resize(viewSize);

			m_charts << chart;
			m_views << view;

			row = (i % 3 == 0 && i ? row + 1 : row);

			m_layout->addWidget(view, row, col);

			col = (i % 3 == 0 && i ? 0: col + 1);

			connect(m_monitor, &Monitor::statsResultReady, chart, &Chart::updateChart);
		}

		m_monitor->setPids(pids);
		QThreadPool::globalInstance()->start(m_monitor);
	}
}

/*!
 * \fn MonitorWidget::monitorSize
 * \brief MonitorWidget::monitorSize compute size for each monitor
 *
 * This \c MonitorWidget::monitorSize method define the size for each monitor depending of the numbers of monitors to display.
 *
 * \param itemsCount waits the number of monitor to display
 * \return size for a monitor.
 */
QSize MonitorWidget::monitorSize(int itemsCount)
{
	float w = (itemsCount == 1) ? geometry().width() : (geometry().width()  - m_layout->spacing()) / itemsCount;
	float h = 0.0;

	if(!floor(itemsCount / 3))
		h = geometry().height();

	else if(floor(itemsCount / 3) == 1)
		h = (geometry().height() - m_layout->spacing()) / 2;

	else
		h = 400;

	return QSize(w, h);
}
