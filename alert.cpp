#include "alert.h"

using namespace businesslayer;

/*!
 * \brief Alert::Alert						[public]
 *
 * Construct the object with default font.
 * Using default :
 * \list
 *		\li \l {Family Lato if exists otherwize Arial}
 *		\li \l {Bold setted to true}
 *		\li \l {PixelSize 15}
 * \endlist
 *
 * \param parent waits parent \c QObject default value \a nullptr
 */
Alert::Alert(QWidget *parent) : QLabel(parent)
{
	QFont font("Lato");
	font.setBold(true);
	font.setPixelSize(15);

	setFont(font);
}

/*!
 * \brief Alert::primary					[public slot]
 *
 * This method defines primary background and color text of alert label.
 *
 * \span {style="background-color: #CFE2FF; color: #084298; padding: 1rem; border: 1px solid #B6D4FE; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::primary(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-primary"]);
}

/*!
 * \brief Alert::secondary					[public slot]
 *
 * This method defines secondary background and color text of alert label.
 *
 * \span {style="background-color: #E2E3E5; color: #41464B; padding: 1rem; border: 1px solid #D3D6D8; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::secondary(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-secondary"]);
}

/*!
 * \brief Alert::success					[public slot]
 *
 * This method defines success background and color text of alert label.
 *
 * \span {style="background-color: #D1E7DD; color: #0F5132; padding: 1rem; border: 1px solid #BADBCC; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::success(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-success"]);
}

/*!
 * \brief Alert::danger						[public slot]
 *
 * This method defines danger background and color text of alert label.
 *
 * \span {style="background-color: #F8D7DA; color: #842029; padding: 1rem; border: 1px solid #F5C2C7; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::danger(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-danger"]);
}

/*!
 * \brief Alert::warning					[public slot]
 *
 * This method defines warning background and color text of alert label.
 *
 * \span {style="background-color: #FFF3CD; color: #664D03; padding: 1rem; border: 1px solid #FFECB5; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::warning(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-warning"]);
}

/*!
 * \brief Alert::information					[public slot]
 *
 * This method defines information background and color text of alert label.
 *
 * \span {style="background-color: #CFF4FC; color: #055160; padding: 1rem; border: 1px solid #B6EFFB; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::information(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-information"]);
}

/*!
 * \brief Alert::dark							[public slot]
 *
 * This method defines dark background and color text of alert label.
 *
 * \span {style="background-color: #FEFEFE; color: #636464; padding: 1rem; border: 1px solid #FDFDFE; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::light(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-light"]);
}

/*!
 * \brief Alert::dark							[public slot]
 *
 * This method defines dark background and color text of alert label.
 *
 * \span {style="background-color: #D3D3D4; color: #141619; padding: 1rem; border: 1px solid #BCBEBF; border-radius: 0.25rem;"}
 *	This is an example of Alert primary
 * \endspan
 *
 * \param text waits a text to display if empty and \c setText() previously defined the \a text will be display
 */
void Alert::dark(const QString &text)
{
	if(!text.isEmpty())
		setText(text);

	setStyleSheet(m_css["alert-dark"]);
}

/*!
 * \brief Alert::clean
 *
 * This method clear text and style, by falling to transparent background color
 */
void Alert::clean()
{
	clear();
	setStyleSheet(m_css["transparent"]);
}
