#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <QObject>
#include <QString>
#include <QByteArray>

namespace model
{

	/*!
	 * \brief The Distribution struct				[public]
	 *
	 * This structure represent the Table model structure of distribution.
	 */
	struct Distribution
	{
			/*! \brief id store the id of distribution */
			int id;

			/*! \brief name store the of distribution */
			QString name;

			/*! \brief icon store the icon of distribution */
			QByteArray icon;
	};
}

Q_DECLARE_METATYPE(model::Distribution);

#endif // DISTRIBUTION_H
