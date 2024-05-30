#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>

sql::Connection* connectDatabase(sql::mysql::MySQL_Driver* driver);

#endif // DATABASE_H
