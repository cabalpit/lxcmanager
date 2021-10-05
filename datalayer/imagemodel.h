#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "modelbase.h"
#include <QObject>

namespace model {

	/*!
	 * \brief The ImageModel class
	 * \version 1.0
	 * \since 2021-09-19
	 * \author Peter Cata
	 *
	 * This class represent images table.
	 */
	class ImageModel : public ModelBase
	{
			Q_OBJECT
		public:
			explicit ImageModel(QObject *parent = nullptr, const QString &connectionName = "sql_image_connection");

			QSqlQuery *findRelease(const int idDistribution);
			QSqlQuery *findArch(const QMap<int, QString> &search);
			QSqlQuery *findVariant(const QMap<int, QString> &search);


		private:
			QSqlQuery *searcher(const QString &q, const QMap<int, QString> &params = QMap<int, QString>());
	};
}

#endif // IMAGEMODEL_H
