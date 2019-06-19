
#pragma once

#include <QtSql\QSqlDatabase>
#include <QtSql\QSqlError>
#include <QtSql\QSqlQuery>
#include <array>

namespace DatabaseCover{

	/*
	QSqlDatabase database;
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("MyDataBase.db");
	if (!database.open())
	{
	qDebug() << "Error: Failed to connect database." << database.lastError();
	}
	else
	{
	qDebug() << "Succeed to connect database.";
	}

	QSqlQuery sql_query;
	if (!sql_query.exec("create table student(id int primary key, name text, age int)"))
	{
	qDebug() << "Error: Fail to create table." << sql_query.lastError();
	}
	else
	{
	qDebug() << "Table created!";
	}

	if (!sql_query.exec("INSERT INTO student VALUES(1, \"Wang\", 23)"))
	{
	qDebug() << sql_query.lastError();
	}
	else
	{
	qDebug() << "inserted Wang!";
	}
	if (!sql_query.exec("INSERT INTO student VALUES(2, \"Li\", 23)"))
	{
	qDebug() << sql_query.lastError();
	}
	else
	{
	qDebug() << "inserted Li!";
	}

	sql_query.exec("update student set name = \"QT\" where id = 1");
	if (!sql_query.exec())
	{
	qDebug() << sql_query.lastError();
	}
	else
	{
	qDebug() << "updated!";
	}

	sql_query.exec("select * from student");
	if (!sql_query.exec())
	{
	qDebug() << sql_query.lastError();
	}
	else
	{
	while (sql_query.next())
	{
	int id = sql_query.value(0).toInt();
	QString name = sql_query.value(1).toString();
	int age = sql_query.value(2).toInt();
	qDebug() << QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
	}
	}

	sql_query.exec("delete from student where id = 1");
	if (!sql_query.exec())
	{
	qDebug() << sql_query.lastError();
	}
	else
	{
	qDebug() << "deleted!";
	}

	sql_query.exec("drop table student");
	if (sql_query.exec())
	{
	qDebug() << sql_query.lastError();
	}
	else
	{
	qDebug() << "table cleared";
	}

	database.close();
	*/

	class MySqLite
	{
	public:

		MySqLite(QString db)
		{
			
			if (QSqlDatabase::contains("qt_sql_default_connection"))
			{
				mDatabase = QSqlDatabase::database("qt_sql_default_connection");
			}
			else
			{
				mDatabase = QSqlDatabase::addDatabase("QSQLITE");
				mDatabase.setDatabaseName(db);
				mDatabase.setUserName("drose");
				mDatabase.setPassword("drose");
				open();
			}
		}

		bool open()
		{
			if (!mDatabase.open())
			{
				qDebug() << "Error: Failed to connect database." << mDatabase.lastError();
				return false;
			}
			else
			{
				qDebug() << "connect database success.";
			}

			return true;
		}

		void close()
		{
			mDatabase.close();
		}

		/*
		void creatTable()
		{
			QSqlQuery sql_query(mDatabase);
			QString create_sql = "create table student (id int primary key, name varchar(30), age int)";
			sql_query.prepare(create_sql);
			if (!sql_query.exec())
			{
				qDebug() << "Error: Fail to create table." << sql_query.lastError();
			}
			else
			{
				qDebug() << "Table created!";
			}
		}
		*/

		bool insert(QString table, QVector<QStringList> tQvector)
		{
			QSqlQuery sql_query;
			QString insert_sql = "INSERT INTO " + table;
			insert_sql += " (";
			for (size_t i = 0; i < tQvector.size(); i++)
			{
				insert_sql += tQvector[i][0];
				if (i != tQvector.size()-1)
				{
					insert_sql += ", ";
				}
			}
			insert_sql += ") VALUES (";

			for (size_t i = 0; i < tQvector.size(); i++)
			{
				insert_sql += tQvector[i][1];
				if (i != tQvector.size() - 1)
				{
					insert_sql += ", ";
				}
			}
			insert_sql += ")";
		//	sql_query.prepare(insert_sql);
			if (!sql_query.exec(insert_sql))
			{
				qDebug() << sql_query.lastError();
				return false;
			}
			else
			{
				qDebug() << "inserted ok!";
				return true;
			}
		}

		void select()
		{
			QSqlQuery sql_query;
			QString tSql = "select * from drose;";
			
			if (!sql_query.exec(tSql))
			{
				qDebug() << sql_query.lastError();
				
			}
			else
			{
				qDebug() << "inserted ok!";
				
			}
		}

	private:
		QSqlDatabase mDatabase;
	};







}
