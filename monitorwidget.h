#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QChartView>
#include <QThreadPool>
#include <QtMath>

#include "businesslayer/lxccontainer.h"
#include "businesslayer/monitor.h"
#include "businesslayer/style.h"
#include "chart.h"

/*!
 * \class MonitorWidget
 * \brief The MonitorWidget class
 * \version 1.0
 * \since 2021-10-09
 * \author Peter Cata
 *
 * The \c MonitorWidget class display monitors to servey container stat, cpu and memory.
 * The class use \c QThreadPool to retrieves information and to send to chart to draw spline lines.
 * Each containers has is own \a Monitor.
 *
 * This class use thread-safe.
 */
class MonitorWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit MonitorWidget(QWidget *parent = nullptr);
		~MonitorWidget();

	signals:

	public slots:
		void updateMonitors(bool update);

	protected:
		QSize monitorSize(int itemsCount);

	private:
		QGridLayout *m_layout;
		businesslayer::LxcContainer *m_lxc;
		businesslayer::Monitor *m_monitor;
		businesslayer::Style m_css;
		QList<QtCharts::QChartView *> m_views;
		QList<Chart *> m_charts;
};

#endif // MONITORWIDGET_H
