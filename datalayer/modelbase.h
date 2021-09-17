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
	 * @brief The Model class
	 *
	 * This class should not be used directly. Use Models class instead.
	 * If you want to create your own Model, you can subclass this class and reimplement its pure virtual functions and those virtual functions.
	 *
	 * This class provid database connection and base functions to reimplement.
	 */
	class ModelBase : public QObject
	{
			Q_OBJECT
			Q_PROPERTY(QString table READ table WRITE setTable NOTIFY tableChanged);
			Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged);

		public:
			explicit ModelBase(QObject *parent = nullptr);
			~ModelBase();

			virtual void setTable(const QString &table);
			virtual QString table() const;

			virtual void setId(const QString &name);
			virtual QString id() const;

			virtual QSqlQuery *find(const QString &search);
			virtual QSqlQuery *find(const int &search);
			virtual QSqlQuery *findAll(int limit = 0, int offset = 0);
			virtual QSqlQuery *del(const QPair<QString, QString> &keyValue);
			virtual bool insert(const QMap<QString, QString> &keysValues);
			virtual bool update(const QMap<QString, QString> &keysValues, const QPair<QString, QString> &where);

			bool open();
			void close();

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
