#include "model.h"
using namespace model;

Model::Model(QObject *parent) : QObject(parent)
{
	if(!m_db.isDriverAvailable("SQLITE"))
		return;

	m_db = QSqlDatabase::addDatabase("SQLite");
	m_db.setDatabaseName(":/db/lxcimages");

	m_driver = m_db.driver();
}

Model::~Model()
{
	delete m_driver;
}

void Model::setTable(const QString &table)
{
	m_table = table;
	emit tableChanged();
}

void Model::setId(const QString &name)
{
	m_id = name;
	emit idChanged();
}

const QSqlQuery *Model::find(const QString &search)
{
	QString q = QString("SELECT * FROM @ WHERE % = ?;").replace('@', m_table).replace('%', m_id);

	QSqlQuery *query = new QSqlQuery(q);
	query->bindValue("?", search);

	query->exec();

	return query;
}

QSqlQuery *Model::findAll(int offset, int limit)
{
	QString q = QString("SELECT * FROM @").replace('@', m_table).replace('%', m_id);

	if(limit > 0)
		q += " LIMIT " + QString::number(limit);

	if(limit >0 && offset > 0)
		q += " OFFSET " + QString::number(offset);

	q += ";";

	QSqlQuery *query = new QSqlQuery(q);
	query->exec();

	return query;
}

QSqlQuery *Model::del(const QPair<QString, QString> &keyValue)
{
	QString q = QString("DELETE FROM @ WHERE % = ?;").replace('@', m_table).replace('%', keyValue.first);

	QSqlQuery *query = new QSqlQuery(q);
	query->bindValue("?", keyValue.second);

	query->exec();

	return query;
}

bool Model::insert(const QMap<QString, QString> &keysValues)
{
	QString q = QString("INSERT INTO @ (%) VALUE (#);").replace('@', m_table);

	// build string for attributes.
	QMapIterator<QString, QString>it(keysValues);
	QString attribs, placeholder;

	while (it.hasNext()) {
		it.next();
		attribs = attribs.append(it.key());
		attribs = attribs.append(", ");
		placeholder = placeholder.append("?, ");
	}

	it.toFront();

	if(!attribs.isEmpty())
	{
		attribs.chop(2);
		placeholder.chop(2);
	}

	q.replace('%', attribs);



	QSqlQuery *query = new QSqlQuery(q);

	while (it.hasNext())
	{
		it.next();
		query->bindValue("?", it.value());
	}

	query->exec();

	return query;
}

bool Model::open()
{
	bool isOpen = m_db.open();

	if(!isOpen)
		qWarning() << "Warning: " << m_db.lastError().text();

	return isOpen;
}

void Model::close()
{
	m_db.close();
}

QSqlDriver *Model::driver() const
{
	return m_driver;
}
