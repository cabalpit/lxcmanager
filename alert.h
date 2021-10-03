#ifndef ALERT_H
#define ALERT_H

#include <QLabel>
#include "businesslayer/style.h"

/*!
 * class Alert
 * \brief The Alert class represent a label
 *
 * This class is used fo displaying a message. The Alert class provides defined design.
 * You can selecting various design for example primary, danger, info, success, ...
 *
 * \since 2021-10-03
 * \version 1.0
 * \author Peter Cata
 */
class Alert : public QLabel
{
		Q_OBJECT

	public:
		explicit Alert(QWidget *parent = nullptr);
		~Alert();

	public slots:
		void primary(const QString &text = QString());
		void secondary(const QString &text = QString());
		void success(const QString &text = QString());
		void danger(const QString &text = QString());
		void warning(const QString &text = QString());
		void information(const QString &text = QString());
		void light(const QString &text = QString());
		void dark(const QString &text = QString());

		void clean();

	private:
		businesslayer::Style m_css;
};

#endif // ALERT_H
