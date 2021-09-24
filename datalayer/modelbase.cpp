#include "modelbase.h"

using namespace model;
using namespace businesslayer;

/**
 * @brief ModelBase::ModelBase
 *
 * Default constructor with parent object.
 *
 * @param parent default nullptr waits object parent.
 */
ModelBase::ModelBase(QObject *parent, const QString &connectionName) : QObject(parent)
{
	if(!m_db.isDriverAvailable("QSQLITE"))
		return;

	QString dbPath = QDir::homePath() + "/.local/share/lxcmanager/lxcimages";

	m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
	m_db.setDatabaseName(dbPath);
}

/**
 * @brief ModelBase::~ModelBase
 */
ModelBase::~ModelBase()
{

}

/**
 * @brief ModelBase::setTable										[public]
 *
 * This setter set table to query.
 *
 * @param table waits table name
 */
void ModelBase::setTable(const QString &table)
{
	m_table = table;
	emit tableChanged();
}

/**
 * @brief ModelBase::table										[public]
 *
 * This getter returns table name previously sets.
 *
 * @return table name
 */
QString ModelBase::table() const
{
	return m_table;
}

/**
 * @brief ModelBase::setId										[public]
 *
 * Set the default id for the current table.
 *
 * @param name waits id name.
 */
void ModelBase::setId(const QString &name)
{
	m_id = name;
	emit idChanged();
}

/**
 * @brief ModelBase::id											[public]
 * @return id previously set.
 */
QString ModelBase::id() const
{
	return m_id;
}

QSqlDatabase ModelBase::database()
{
	return m_db;
}

/**
 * @brief ModelBase::find										[public]
 *
 * This method finds in selected table with previous setted id.
 *
 * @param search waits the value to search.
 * @param comparison waits an Enum for comparison by default Equal comparision. To know about ComparisonType @see model::ComparisonType
 * @return QSqlQuery if rows found otherwize nullptr
 */
QSqlQuery *ModelBase::find(const QString &search, ComparisonType comparison)
{
	WhereClause clause;
	clause.compare = comparison;
	clause.where = QPair<QString, QString>(m_id, search);

	return find(clause);
}

/**
 * @brief ModelBase::find										[public]
 *
 * Overload method find
 *
 * @param search waits the value to search, the parameter will be converted to QString.
 * @param comparison waits an Enum for comparison by default Equal comparision. To know comparison type @see model::ComparisonType
 * @return QSqlQuery if rows found otherwize nullptr
 */
QSqlQuery *ModelBase::find(const int &search, ComparisonType comparison)
{
	WhereClause clause;
	clause.compare = comparison;
	clause.where = QPair<QString, QString>(m_id, QString::number(search));

	return find(clause);
}

/**
 * @brief ModelBase::find										[public]
 *
 * Overload method find
 *
 * @param clause waits WhereClause struct, @see model::WhereClause
 * @return QSqlQuery if rows found otherwize nullptr.
 */
QSqlQuery *ModelBase::find(const WhereClause &clause)
{
	QString q = QString("SELECT * FROM %1 WHERE %2 %3 ?").arg(m_table, clause.where.first, comparison(clause.compare));

	if(open())
	{
		QSqlQuery *query = new QSqlQuery(m_db);
		query->prepare(q);

		query->bindValue(0, clause.where.second);

		if(query->exec())
			return query;

		else
		{
			QString error = QString("SqlError number %1: %2\n%3").arg(QString::number(query->lastError().type()), query->lastError().text(), query->lastQuery());
			errors("ModelBase::find", error);
		}
	}

	return nullptr;
}

/**
 * @brief ModelBase::findAll										[public]
 *
 * This method returns all rows from selected table, the limit and offset can be
 * set to reduce the number of rows.
 *
 * @param limit waits interger to limit the number of rows, default 0
 * @param offset waits integer to adjustment of start of rows, default 0
 * @return QSqlQuery if rows found otherwize nullptr.
 */
QSqlQuery *ModelBase::findAll(int limit, int offset)
{
	QString q = QString("SELECT * FROM %1").arg(m_table);

	if(limit > 0)
		q += " LIMIT " + QString::number(limit);

	if(limit > 0 && offset > 0)
		q += " OFFSET " + QString::number(offset);


	if(open())
	{
		QSqlQuery *query = new QSqlQuery(m_db);
		query->prepare(q);

		if(query->exec())
			return query;

		else
		{
			QString error = QString("SqlError number %1: %2\n%3").arg(QString::number(query->lastError().type()), query->lastError().text(), query->lastQuery());
			errors("ModelBase::findAll", error);
		}
	}

	return nullptr;
}

/**
 * @brief ModelBase::insert										[public]
 *
 * This method inserts data into table. This method inserts only one row at time.
 *
 * @param keysValues waits first value column name, second value the value to insert.
 * @return true if the data have been insert otherwize false.
 */
bool ModelBase::insert(const QMap<QString, QString> &keysValues)
{
	if(keysValues.isEmpty())
		return false;

	bool success = false;
	QString q = QString("INSERT INTO %1 (@) VALUES (#)").arg(m_table);

	// build string for attributes.
	QMapIterator<QString, QString>it(keysValues);
	QString attribs, placeholder;

	while (it.hasNext())
	{
		it.next();
		attribs = attribs.append(it.key()).append(", ");
		placeholder = placeholder.append("?, ");
	}

	if(attribs.isEmpty() || !open())
		return success;


	attribs.chop(2);
	placeholder.chop(2);

	q.replace('@', attribs).replace('#', placeholder);


	QSqlQuery *query = new QSqlQuery(m_db);
	query->prepare(q);

	int pos = -1;
	it.toFront();
	while (it.hasNext())
	{
		it.next();
		pos++;
		query->bindValue(pos, it.value());
	}

	success = query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		QString error = QString("SqlError number %1: %2\n%3").arg(QString::number(query->lastError().type()), query->lastError().text(), query->lastQuery());
		errors("ModelBase::insert", error);
	}

	delete query;

	return success;
}

/**
 * @brief ModelBase::insert										[public]
 *
 * Overload method this method, will insert multiple rows. If one row failed to insert
 * the method will stop the rest of the list will not be insert.
 *
 * @param keysValuesList waits first value column name, second value the value to insert. This foreach row of the list.
 * @return true if the data have been insert otherwize false.
 */
bool ModelBase::insert(const QList<QMap<QString, QString>> &keysValuesList)
{
	QListIterator<QMap<QString,QString>>it(keysValuesList);
	bool success = false;

	while (it.hasNext())
	{
		success = insert(it.next());

		if(!success)
			break;
	}

	return success;
}

/**
 * @brief ModelBase::update										[public]
 *
 * This method will update a row.
 *
 * @param keysValues waits first value column name, second value the value to update.
 * @param clause condition where to update. Waits struct WhereClause @see model::WhereClause
 * @return true if update done otherwize false
 */
bool ModelBase::update(const QMap<QString, QString> &keysValues, const WhereClause &clause)
{
	QString q = QString("UPDATE %1 SET @ WHERE %2 %3 ?").arg(m_table, clause.where.first, comparison(clause.compare));

	QMapIterator<QString, QString>it(keysValues);

	QString attribs;

	while(it.hasNext())
	{
		it.next();
		attribs = attribs.append(it.key()).append(" = ?, ");
	}


	if(attribs.isEmpty() || !open())
		return false;

	attribs.chop(2);
	q.replace('@', attribs);

	QSqlQuery *query = new QSqlQuery(m_db);
	query->prepare(q);

	int pos = -1;
	it.toFront();
	while (it.hasNext())
	{
		it.next();
		pos++;
		query->bindValue(pos, it.value());
	}


	query->bindValue(++pos, clause.where.second);

	bool success = query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		QString error = QString("SqlError number %1: %2\n%3").arg(QString::number(query->lastError().type()), query->lastError().text(), query->lastQuery());
		errors("ModelBase::update", error);
	}

	delete query;

	return success;
}

/**
 * @brief ModelBase::update										[public]
 *
 * Override method, update a list of values.
 *
 * @param keysValuesList waits a list of QMap, first value column name, second value the value to update.
 * @param clauseList condition list for each line to update must be equal to keyValuesList length
 * @return true if update done otherwize false.
 */
bool ModelBase::update(const QList<QMap<QString, QString>> &keysValuesList, const QList<WhereClause> &clauseList)
{
	bool success = false;
	QListIterator<QMap<QString, QString>> itKeysValuesList(keysValuesList);
	QListIterator<WhereClause> itWhereList(clauseList);

	while(itKeysValuesList.hasNext())
	{
		success = update(itKeysValuesList.next(), itWhereList.next());

		if(!success)
		   break;
	}

	return success;
}

/**
 * @brief ModelBase::del										[public]
 *
 * This method will delete rows.
 *
 * @param clause waits clause condition where to delete @see model::WhereClause.
 * @return true if delete done otherwize false.
 */
bool ModelBase::del(const WhereClause &clause)
{
	bool success = false;
	QString q = QString("DELETE FROM %1 WHERE %2 %3 ?").arg(m_table, clause.where.first, comparison(clause.compare));

	if(!open())
		return success;

	QSqlQuery *query = new QSqlQuery(m_db);
	query->prepare(q);
	query->bindValue(0, clause.where.second);

	success = query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		QString error = QString("SqlError number %1: %2\n%3").arg(QString::number(query->lastError().type()), query->lastError().text(), query->lastQuery());
		errors("ModelBase::del", error);
	}

	delete query;

	return success;
}

/**
 * @brief ModelBase::del								[public]
 *
 * This method deletes from table a list of values. If a delete failed the method will
 * stop and the rest of the list will be not delete.
 *
 * @param clauseList waits a list of WhereClause structure @see model::WhereClause
 * @return true if success otherwize false.
 */
bool ModelBase::del(const QList<WhereClause> &clauseList)
{
	bool success = false;
	QListIterator<WhereClause>it(clauseList);

	while (it.hasNext())
	{
		success = del(it.next());

		if(!success)
			break;
	}

	return success;
}

/**
 * @brief ModelBase::open										[public]
 *
 * This method open connection to database. If the connection is already open
 * the method will not try to reopen.
 *
 * This method must be triggered before to query database, and instanciate QSqlQuery class.
 *
 * @return true if connection opened otherwize false.
 */
bool ModelBase::open()
{
	bool isOpen = m_db.isOpen();

	if(!isOpen)
	{
		isOpen = m_db.open();

		if(!isOpen)
		{
			Logs::writeLog(LogType::Warning, "ModelBase::open()", QString::number(m_db.lastError().type()) + ": " + m_db.lastError().text());
#ifdef QT_DEBUG
			qWarning() << "Warning: " << m_db.lastError().text();
#endif
		}
	}

	return isOpen;
}

/**
 * @brief ModelBase::isOpen										[public]
 *
 * This getter return the state of connection
 *
 * @return true if connection is open otherwize false.
 */
bool ModelBase::isOpen() const
{
	return m_db.isOpen();
}

/**
 * @brief ModelBase::close										[public]
 *
 * This method closes the connection to database.
 */
void ModelBase::close()
{
	QString connectionName = m_db.connectionName();
	m_db.close();
}

/**
 * @brief ModelBase::comparison										[public]
 *
 * This method returns the symbole
 *
 * @param cmpt waits ComparisonType value.
 * @return symbole equivalent to the enumerator type.
 */
QString ModelBase::comparison(ComparisonType comparison)
{
	QString type;

	switch (comparison)
	{
		case Equal:
			type = "=";
		break;

		case Superior:
			type = ">";
		break;

		case SuperiorOrEquale:
			type = ">=";
		break;

		case Inferior:
			type = "<";
		break;

		case InferiorOrEqual:
			type = "<=";
		break;

		case Different:
			type = "<>";
		break;

		default:
		break;
	}

	return type;
}

/**
 * @brief ModelBase::errors										[private]
 *
 * This method trigger Log::WriteLog method to write the error from QSqlite
 *
 * @param methodName waits the method name who call the method.
 * @param error	text to write.
 */
void ModelBase::errors(const QString &methodName, const QString &error)
{
	Logs::writeLog(LogType::Error, methodName, error);

#ifdef QT_DEBUG
		qDebug() << methodName << ": " << error;
#endif
}

