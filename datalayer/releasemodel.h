#ifndef RELEASEMODEL_H
#define RELEASEMODEL_H

#include "modelbase.h"

namespace  model {

	/**
	 * @brief The ReleaseModel class
	 *
	 * This class represent release table.
	 */
	class ReleaseModel : public ModelBase
	{
			Q_OBJECT
		public:
			explicit ReleaseModel(QObject *parent = nullptr);
	};
}
#endif // RELEASEMODEL_H
