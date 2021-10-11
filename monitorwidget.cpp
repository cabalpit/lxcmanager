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
	m_lxc = new LxcContainer(this);
	m_layout = nullptr;
	m_monitor = nullptr;

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidget(this);
}

/*!
 * \brief MonitorWidget::~MonitorWidget destructor
 */
MonitorWidget::~MonitorWidget()
{
	delete m_lxc;

	for(int i = 0; i < m_charts.length(); i++)
	{
		delete m_charts.at(i);
		delete m_views.at(i);
	}

	m_charts.clear();
	m_views.clear();

	if(m_layout)
		delete m_layout;

	if(m_monitor)
	{
		m_monitor->interrupt();
		QThreadPool::globalInstance()->waitForDone();
	}
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
		stopMonitor();

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

			delete m_layout;
			m_layout = nullptr;
		}
	}

	lxc_container **actives = m_lxc->activeContainersList();
	int count = m_lxc->lxcCountActives();
	QMap<pid_t, QString> pids;

	if(count)
	{
		if(!m_layout)
		{
			m_layout = new QGridLayout(this);
			setLayout(m_layout);
		}

		int row = 0, col = 0;

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
			view->setStyleSheet(m_css["transparent"]);

			m_charts << chart;
			m_views << view;

			row = (i % 3 == 0 && i ? row + 1 : row);

			m_layout->addWidget(view, row, col);

			col = (i % 3 == 0 && i ? 0: col + 1);
		}

		monitorSize(count);
		initMonitor(pids);
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
	int rows = floor(m_layout->count() / 3) + 1;
	int cols = itemsCount >= 3 ? 3 : itemsCount;
	int horizontalMargins = m_layout->contentsMargins().left() + m_layout->contentsMargins().right();
	int verticalMargins = m_layout->contentsMargins().top() + m_layout->contentsMargins().bottom();

	float w = (geometry().width() - horizontalMargins - m_layout->horizontalSpacing() * (cols - 1)) / cols;
	float h = (geometry().height() - verticalMargins - m_layout->verticalSpacing() * (rows - 1)) / rows;


qDebug() << m_layout->rowCount() << m_layout->columnCount() ;

	if(rows >= 3)
		h = 400;

	for(int i = 0; i < cols; i++)
		m_layout->setColumnMinimumWidth(i, w);

	for(int i = 0; i < rows; i++)
		m_layout->setRowMinimumHeight(i, h);


	return QSize(w, h);
}

/*!
 * \fn MonitorWidget::initMonitor
 * \brief MonitorWidget::initMonitor initialize monitor object.
 *
 * The \c MonitorWidget::initMonitor initialize the monitor object by contructing it,
 * initializing \a interval, \a pids, connecting monitor to chart, and strat global thread pool.
 *
 * \param pids waits the \a pids list to stat, key must be the pid, value the name of the pid in other word the name of the container.
 */
void MonitorWidget::initMonitor(QMap<pid_t, QString> pids)
{
	if(m_monitor)
		m_monitor = nullptr;

	m_monitor = new Monitor(this);
	m_monitor->setInterval(1);
	m_monitor->setPids(pids);

	for (int i = 0; i < m_charts.count(); i++)
		connect(m_monitor, &Monitor::statsResultReady, m_charts.at(i), &Chart::updateChart);

	QThreadPool::globalInstance()->start(m_monitor);
}

/*!
 * \fn MonitorWidget::stopMonitor
 * \brief MonitorWidget::stopMonitor interrupt thread
 *
 * The \c MonitorWidget::stopMonitor method interrupt thread, and stop the global thread,
 * and free the monitor object.
 *
 */
void MonitorWidget::stopMonitor()
{
	m_monitor->interrupt();

	disconnect(m_monitor, nullptr, nullptr, nullptr);
	QThreadPool::globalInstance()->waitForDone();

	m_monitor = nullptr;
}

/*!
 * \fn MonitorWidget::paintEvent
 * \brief MonitorWidget::paintEvent draw background
 *
 * Override method. The \c MonitorWidget::paintEvent draw background of widget.
 * \param event waits event \c QPaintEvent provided by Qt
 */
void MonitorWidget::paintEvent(QPaintEvent *event)
{
	QRect backgroundRect(0, 0, geometry().width(), geometry().height());

	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing);

	QPainterPath path;
	path.addRoundedRect(backgroundRect, 10, 10);
	path.setFillRule(Qt::OddEvenFill);

	painter->save();
	painter->setPen(QPen(QBrush(QColor(255, 255, 255)), 1));
	painter->fillPath(path, QBrush(QColor(255, 255, 255)));
	painter->restore();

	if(!m_layout)
	{
		// draw text
		QFont font("Lato");
		font.setBold(true);
		font.setPixelSize(24);

		QFontMetrics metrics(font);

		QString text = tr("No container running for monitoring");

		painter->save();

		float mm = 25.4 / metrics.fontDpi();

		float textX = (geometry().width() - text.length() * font.pixelSize() * mm) / 2;
		float textY = (geometry().height() + metrics.height() * mm) / 2;

		painter->setPen(QColor(220, 220, 220));
		painter->setFont(font);
		painter->drawText(textX, textY, text);

		painter->restore();

		//draw donot_disturb picture
		painter->save();

		float pmX = textX - 64;
		float pmY = (geometry().height() - 48) / 2;

		QPixmap pm (":/icons/donot_disturb_green");
		painter->drawPixmap(pmX, pmY, pm.scaled(48, 48));

		painter->restore();
	}

	painter->end();

	delete painter;

	QWidget::paintEvent(event);
}

