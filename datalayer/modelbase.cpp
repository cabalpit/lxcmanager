#include "modelbase.h"
using namespace model;

ModelBase::ModelBase(QObject *parent) : QObject(parent)
{
	if(!m_db.isDriverAvailable("QSQLITE"))
		return;

	QString dbPath = QDir::homePath() + "/.local/share/lxcmanager/lxcimages";

	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(dbPath);
}

ModelBase::~ModelBase()
{

}

void ModelBase::setTable(const QString &table)
{
	m_table = table;
	emit tableChanged();
}

QString ModelBase::table() const
{
	return m_table;
}

void ModelBase::setId(const QString &name)
{
	m_id = name;
	emit idChanged();
}

QString ModelBase::id() const
{
	return m_id;
}

QSqlQuery *ModelBase::find(const QString &search)
{
	QString q = QString("SELECT * FROM @ WHERE % = ? ;").replace('@', m_table).replace('%', m_id);

	if(m_db.open())
	{
		QSqlQuery *query = new QSqlQuery(q);
		query->bindValue(0, QVariant(search));

		if(query->exec())
		{
			qDebug() << query->lastQuery();
			return query;
		}
		else
			qDebug() << query->lastError();
	}

	close();
	return nullptr;
}

QSqlQuery *ModelBase::find(const int &search)
{
	return find(QString::number(search));
}

QSqlQuery *ModelBase::findAll(int limit, int offset)
{
	QString q = QString("SELECT * FROM @").replace('@', m_table).replace('%', m_id);

	if(limit > 0)
		q += " LIMIT " + QString::number(limit);

	if(limit > 0 && offset > 0)
		q += " OFFSET " + QString::number(offset);

	q += ";";

	if(open())
	{
		QSqlQuery *query = new QSqlQuery(q);

		if(query->exec())
		{
			qDebug() << query->lastQuery();
			return query;
		}
		else
			qDebug() << query->lastError().text();
	}

	close();

	return nullptr;
}

QSqlQuery *ModelBase::del(const QPair<QString, QString> &keyValue)
{
	QString q = QString("DELETE FROM @ WHERE % = ?;").replace('@', m_table).replace('%', keyValue.first);

	QSqlQuery *query = new QSqlQuery(q);
	query->bindValue("?", keyValue.second);

	query->exec();

	return query;
}

bool ModelBase::insert(const QMap<QString, QString> &keysValues)
{
	QString q = QString("INSERT INTO @ (%) VALUE (#);").replace('@', m_table);

	// build string for attributes.
	QMapIterator<QString, QString>it(keysValues);
	QString attribs, placeholder;

	while (it.hasNext())
	{
		it.next();
		attribs = attribs.append(it.key()).append(", ");
		placeholder = placeholder.append("?, ");
	}

	it.toFront();

	if(!attribs.isEmpty())
	{
		attribs.chop(2);
		placeholder.chop(2);

		q.replace('%', attribs);
	}

	QSqlQuery *query = new QSqlQuery(q);

	while (it.hasNext())
	{
		it.next();
		query->bindValue("?", it.value());
	}

	query->exec();

	return query;
}

bool ModelBase::update(const QMap<QString, QString> &keysValues, const QPair<QString, QString> &where)
{
	QString q = QString("UPDATE @ SET # WHERE ! = :where;").replace('@', m_table).replace('!', where.first);

	QMap<QString,QString>::const_iterator it;

	QString attribs;

	for(it = keysValues.cbegin(); it != keysValues.cend(); it++)
	{
		attribs = attribs.append(it.key()).append(" = ?, ");
	}

	attribs.chop(2);
	q = q.replace('#', attribs);

	QSqlQuery *query = new QSqlQuery(q);
	query->bindValue(":where", where.second);

	for(it = keysValues.cbegin(); it != keysValues.end(); it++)
	{
		query->bindValue("?", it.value());
	}

	query->exec();

	return query;
}

bool ModelBase::open()
{
	bool isOpen = m_db.open();

	if(!isOpen)
		qWarning() << "Warning: " << m_db.lastError().text();

	return isOpen;
}

void ModelBase::close()
{
	m_db.close();
}
