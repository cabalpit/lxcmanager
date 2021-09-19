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
	 * @author pcata
	 */
	class VariantModel : public model::ModelBase
	{
			Q_OBJECT
		public:
			explicit VariantModel(QObject *parent = nullptr);
	};
}
#endif // VARIANTMODEL_H
