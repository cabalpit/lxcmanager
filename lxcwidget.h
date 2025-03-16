#ifndef LXCWIDGET_H
#define LXCWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include "lxcview.h"

/*!
 * \class LxcWidget
 * \brief The LxcWidget class convenient class for render.
 * \version 1.0
 * \since 2021-10-11
 * \author Peter Cata
 *
 * This class is convenince class for render background equal as the other background
 * to the project.
 *
 * The class do nothing else that painter.
 */
class LxcWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit LxcWidget(QWidget *parent = nullptr);
		~LxcWidget();

		LxcView *view() const;

	signals:

	protected:
		void initObjects();
		void initDisposal();

		void paintEvent(QPaintEvent *event) override;

	private:
		QHBoxLayout *m_layout;
		LxcView *m_view;

};

#endif // LXCWIDGET_H
