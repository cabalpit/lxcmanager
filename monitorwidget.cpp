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
	if(m_layout->count())
	{
		for (int i = m_layout->count() - 1; i >= 0; i--)
		{
			QWidget *view = m_layout->findChild<QChartView *>(QString("view%1").arg(i));
			m_layout->removeWidget(view);

			delete view;
			view = nullptr;
		}

		disconnect(m_monitor, &Monitor::statsResultReady, nullptr, nullptr);

		m_monitor->interrupt();
		QThreadPool::globalInstance()->waitForDone();
	}

	lxc_container **actives = m_lxc->activeContainersList();
	int count = m_lxc->lxcCountActives();
	QHash<QString, pid_t> pids;

	if(count)
	{
		int row = 0, col = 0;

		for (int i = 0; i < count; i++)
		{
			QString name = actives[i]->name;
			pid_t pid = actives[i]->init_pid(actives[i]);

			pids.insert(name, pid);

			Chart *chart = new Chart;
			chart->setTheme(QChart::ChartThemeBlueCerulean);
			chart->setAnimationOptions(QChart::SeriesAnimations);
			chart->setPid(pid);
			chart->setTitle(name);
			chart->setStep(1);

			QChartView *view = new QChartView(chart, this);
			view->setObjectName("view" + QString::number(i));

			row = (i % 3 == 0 ? row + 1 : row);
			col = (i % 3 == 0 ? 0 : col + 1);

			m_layout->addWidget(view, row, col);

			connect(m_monitor, &Monitor::statsResultReady, chart, &Chart::updateChart);
		}

		m_monitor->setPids(pids);
		QThreadPool::globalInstance()->start(m_monitor);
	}
}
