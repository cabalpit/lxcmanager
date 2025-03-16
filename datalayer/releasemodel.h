#ifndef RELEASEMODEL_H
#define RELEASEMODEL_H

#include <QObject>
#include "modelbase.h"

namespace  model {

	/**
	 * @brief The ReleaseModel class
	 *
	 * This class represent release table.
	 *
	 * @version 1.0
	 * @since 2021-09-19
	 */
	class ReleaseModel : public ModelBase
	{
			Q_OBJECT
		public:
			explicit ReleaseModel(QObject *parent = nullptr, const QString &connectionName = "sql_release_connection");
	};
}
#endif // RELEASEMODEL_H
