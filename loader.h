#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <QPainter>
#include <QPen>
#include <QTimer>

/*!
 * \brief The Loader class
 * \version 1.0
 * \since 2021-10-3
 * \author Peter Cata
 *
 * This class implement \c Loader class, Subclasses of this class handle user actions and
 * drawing spinner loader.
 *
 * Loader provides a support and ensure to create homogenous spinner.
 */
class Loader: public QObject
{
		Q_OBJECT
		Q_PROPERTY(int rotate READ rotate NOTIFY rotateChanged)
		Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
		Q_PROPERTY(QRectF arcRect READ arcRect NOTIFY arcRectChanged)

	public:
		explicit Loader(QObject *parent = nullptr);
		~Loader();

		virtual void spinner(QPainter *painter, QPointF position);

		int rotate() const;
		QColor color() const;
		QRectF arcRect() const;

	signals:
		void rotateChanged(int);
		void colorChanged(const QColor &);
		void arcRectChanged(const QRectF &);
		void timerChanged();

	public slots:
		void setColor(const QColor &color);
		void setColor(int r, int g, int b, int a = 255);
		void setArcRect(const QRectF &arcRect);
		void setArcRect(float x, float y, float w, float h);
		void stop();
		void start();
		bool isLoading();

	protected:

	private:
		int m_rotate;			/*! \brief m_rotate hold rotation */
		QColor m_color;			/*! \brief m_color hold spinner color */
		QRectF m_arcRect;		/*! \brief m_arcRect hold spinner rect */
		QTimer m_timer;			/*! \brief m_timer hold timer spinner */
		bool m_isStart;			/*! \brief m_isStart hold if loading */

};

#endif // LOADER_H
