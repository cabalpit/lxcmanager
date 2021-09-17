#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include <QPair>

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
	class Model : public QObject
	{
			Q_OBJECT
			Q_PROPERTY(QString table READ table WRITE setTable NOTIFY tableChanged);
			Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged);

		public:
			explicit Model(QObject *parent = nullptr);
			~Model();

			virtual void setTable(const QString &table);
			virtual QString table() const;

			virtual void setId(const QString &name);
			virtual QString id() const;

			virtual const QSqlQuery *find(const QString &search);
			virtual QSqlQuery *findAll(int offset = 0, int limit = 0);
			virtual QSqlQuery *del(const QPair<QString, QString> &keyValue);
			virtual bool insert(const QMap<QString, QString> &keysValues);
			virtual bool update(const QMap<QString, QString> &keysValues, const QPair<QString, QString> &where);

			bool open();
			void close();

			QSqlDriver *driver() const;

		signals:
			void tableChanged();
			void idChanged();
			void inserted();
			void updated();

		protected:

		private:
			QSqlDriver *m_driver;
			QSqlDatabase m_db;
			QString m_table;
			QString m_id;
	};
}
#endif // MODEL_H
