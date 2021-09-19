#include "imagemodel.h"

using namespace model;

/**
 * @brief ImageModel::ImageModel
 *
 * Default constructor, construct object.
 *
 * @param parent waits parent QObject default nullptr.
 */
ImageModel::ImageModel(QObject *parent) : ModelBase(parent)
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
QSqlQuery *ImageModel::findRelease(const QString &idDistribution)
{
	QString q = "SELECT id_release, release_name "
				"FROM images IMG "
				"INNER JOIN distributions DBS ON DBS.id_distribution = IMG.distribution_id "
				"INNER JOIN releases RLS ON RLS.id_release = IMG.release_id "
				"WHERE id_distribution = ? "
				"GROUP BY distribution_name, id_release, release_name";

	QMap<QString, QString>search;
	search.insert("id_distrib", idDistribution);

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
QSqlQuery *ImageModel::findArch(const QMap<QString, QString> &search)
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
QSqlQuery *ImageModel::findVariant(const QMap<QString, QString> &search)
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
QSqlQuery *ImageModel::searcher(const QString &q, const QMap<QString, QString> &params)
{
	QMapIterator<QString, QString>it(params);

	if(open())
	{
		QSqlQuery *query = new QSqlQuery(q);

		int idx = -1;
		while(it.hasNext())
		{
			it.next();
			idx++;
			query->bindValue(0, it.value());
		}

		if(query->exec())
		{
			return query;
		}
		else if(query->lastError().type() != QSqlError::NoError)
		{
			qDebug() << query->lastQuery();
			qDebug() << query->lastError();
		}
	}

	return nullptr;
}
