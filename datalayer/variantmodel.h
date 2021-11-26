#ifndef VARIANTMODEL_H
#define VARIANTMODEL_H

#include <QObject>
#include "modelbase.h"

namespace model {

	/**
	 * @brief The VariantModel class
	 *
	 * This class represent variants table
	 *
	 * @version 1.0
	 * @since 2021-0919
	 * @author Peter Cata
	 */
	class VariantModel : public model::ModelBase
	{
			Q_OBJECT
		public:
			explicit VariantModel(QObject *parent = nullptr, const QString &connectionName = "sql_variant_connection");
	};
}
#endif // VARIANTMODEL_H
