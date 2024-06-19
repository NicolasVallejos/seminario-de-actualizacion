#include "database.h"
#include <cppconn/exception.h>
#include <iostream>

sql::Connection* connectDatabase(sql::mysql::MySQL_Driver* driver) {
    sql::Connection* con = nullptr;
    try {
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("sistema_multiusuario");
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
        throw;
    }
    return con;
}
