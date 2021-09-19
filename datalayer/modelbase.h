#ifndef MODELBASE_H
#define MODELBASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include <QPair>
#include <QDir>

namespace model
{
	/**
	 * @brief The ComparisonType enum
	 * The enum type is used to describ the comparison in sql where clause =, >, >=, <, <=, <>
	 */
	enum ComparisonType { Equal, Superior, SuperiorOrEquale, Inferior, InferiorOrEqual, Different };

	/**
	 * @brief The WhereClause struct
	 *
	 * Used store and construct where clause sql.
	 * where variable stores a QPair with the first value is 'column_name' and second value the value to compaire.
	 * compare variable stores an Enum type CompareType @see model::ComparisonType default value Equale
	 */
	struct WhereClause
	{
			QPair<QString, QString> where;				/** where Tuple first value 'column_name', second value the value could be located into column */
			ComparisonType compare = Equal;				/** compare ComparisonType */
	};

	/**
	 * @brief The Model class
	 *
	 * This class should not be used directly. Use Models class instead.
	 * If you want to create your own Model, you can subclass this class and reimplement its pure virtual functions and those virtual functions.
	 *
	 * This class provid database connection and base functions to reimplement.
	 *
	 * @version 1.1
	 * @since 2021-09-16
	 * @author pcata
	 */
	class ModelBase : public QObject
	{
			Q_OBJECT
			Q_PROPERTY(QString m_table READ table WRITE setTable NOTIFY tableChanged);
			Q_PROPERTY(QString m_id READ id WRITE setId NOTIFY idChanged);

		public:
			explicit ModelBase(QObject *parent = nullptr);
			~ModelBase();

			virtual void setTable(const QString &table);
			virtual QString table() const;

			virtual void setId(const QString &name);
			virtual QString id() const;

			virtual QSqlQuery *find(const QString &search, ComparisonType comparison = Equal);
			virtual QSqlQuery *find(const int &search, ComparisonType comparison = Equal);
			virtual QSqlQuery *find(const WhereClause &clause);
			virtual QSqlQuery *findAll(int limit = 0, int offset = 0);

			virtual bool insert(const QMap<QString, QString> &keysValues);
			virtual bool insert(const QList<QMap<QString, QString>> &keysValuesList);

			virtual bool update(const QMap<QString, QString> &keysValues, const WhereClause &clause);
			virtual bool update(const QList<QMap<QString, QString>> &keysValuesList, const QList<WhereClause> &clauseList);

			virtual bool del(const WhereClause &clause);
			virtual bool del(const QList<WhereClause> &clauseList);

			bool open();
			bool isOpen() const;
			void close();

			QString comparison(ComparisonType comparison);


		signals:
			void tableChanged();
			void idChanged();
			void inserted();
			void updated();

		protected:

		private:
			QSqlDatabase m_db;
			QString m_table;
			QString m_id;
	};
}
#endif // MODELBASE_H
