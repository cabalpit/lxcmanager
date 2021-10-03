#include "imagemodel.h"

using namespace model;
using namespace businesslayer;

/**
 * @brief ImageModel::ImageModel							[public]
 *
 * Default constructor, construct object.
 *
 * @param parent waits parent QObject default nullptr.
 * @param connectionName waits a connectionName, default connection name sql_image_connection
 */
ImageModel::ImageModel(QObject *parent, const QString &connectionName) : ModelBase(parent, connectionName)
{
	setTable("images");
	setId("id_image");
}

/**
 * @brief ImageModel::findRelease							[public]
 *
 * This method will find the release corresponding to the selected distribution.
 *
 * @param idDistribution waits id distribution
 * @return QSqlQuery if releases found otherwize nullptr
 */
QSqlQuery *ImageModel::findRelease(const int idDistribution)
{
	QString q = "SELECT id_release, release_name "
				"FROM images IMG "
				"INNER JOIN distributions DBS ON DBS.id_distribution = IMG.distribution_id "
				"INNER JOIN releases RLS ON RLS.id_release = IMG.release_id "
				"WHERE id_distribution = ? "
				"GROUP BY distribution_name, id_release, release_name "
				"ORDER BY id_release";

	QMap<int, QString>search;
	search.insert(0, QString::number(idDistribution));

	return searcher(q, search);
}

/**
 * @brief ImageModel::findArch							[public]
 *
 * This method will find the architectures corresponding to the selected distribution and release.
 *
 * @param search waits the key idDistribution and idRelease and the value associated to these keys
 * @return QSqlQuery if releases found otherwize nullptr
 */
QSqlQuery *ImageModel::findArch(const QMap<int, QString> &search)
{
	QString q = "SELECT id_arch, arch_name "
				"FROM images IMG "
				"INNER JOIN distributions DBS ON DBS.id_distribution = IMG.distribution_id "
				"INNER JOIN releases RLS ON RLS.id_release = IMG.release_id "
				"INNER JOIN architectures ARC ON ARC.id_arch = arch_id "
				"WHERE id_distribution = ? AND id_release = ? "
				"GROUP BY id_arch, arch_name";

	return searcher(q, search);
}

/**
 * @brief ImageModel::findVariant							[public]
 *
 * This method will find the variants corresponding to the selected distribution, release and architecture.
 *
 * @param search waits the key idDistribution, idRelease, idArch and the value associated to these keys
 * @return QSqlQuery if releases found otherwize nullptr
 */
QSqlQuery *ImageModel::findVariant(const QMap<int, QString> &search)
{
	QString q = "SELECT id_variant, variant_name "
				"FROM images IMG INNER JOIN distributions DSB ON DSB.id_distribution = IMG.distribution_id "
				"INNER JOIN releases RLS ON RLS.id_release = IMG.release_id "
				"INNER JOIN architectures ARC ON ARC.id_arch = IMG.arch_id "
				"INNER JOIN variants VRT ON VRT.id_variant = IMG.variant_id "
				"WHERE id_distribution = ? AND id_release = ? AND id_arch = ? "
				"GROUP BY id_variant, variant_name";

	return searcher(q, search);
}

/**
 * @brief ImageModel::searcher							[private]
 *
 * Generic method will query database. The method prepare the query and replace with the
 * parameters. The param parameter is optional and can be ignore. The query prepared can
 * be executed without binding value.
 *
 * @param q	waits the query to prepare.
 * @param params (optional) waits the parameters to bind to query.
 * @return QSqlQuery if results found otherwize nullptr
 */
QSqlQuery *ImageModel::searcher(const QString &q, const QMap<int, QString> &params)
{
	QMapIterator<int, QString>it(params);

	if(open())
	{
		QSqlQuery *query = new QSqlQuery(database());
		query->prepare(q);

		while(it.hasNext())
		{
			it.next();
			query->bindValue(it.key(), it.value());
		}

		if(query->exec())
		{
			return query;
		}
		else if(query->lastError().type() != QSqlError::NoError)
		{
			QString error = QString("QSqlError number %1: %2\n%3").arg(QString::number(query->lastError().type()), query->lastError().text(), query->lastQuery());
			Logs::writeLog(LogType::Error, "ImageModel::searcher", error);

#ifdef QT_DEBUG
			qDebug() << "ImageModel::searcher: " << error;
#endif
		}
	}

	return nullptr;
}
