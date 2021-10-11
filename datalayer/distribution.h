#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QObject>
#include <QString>
#include <QByteArray>

namespace model
{

	/*!
	 * \brief The Distribution hold distribution information
	 *
	 * This structure represent the Table model structure of distribution.
	 * It hold distribution id, name and icon.
	 *
	 * The \c Distribution structur is usefull for load a distribution list for example.
	 */
	struct Distribution
	{
			int id;					/*! \brief id store the id of distribution */
			QString name;			/*! \brief name store the of distribution */
			QByteArray icon;		/*! \brief icon store the icon of distribution */
	};
}

Q_DECLARE_METATYPE(model::Distribution);

#endif // DISTRIBUTION_H
