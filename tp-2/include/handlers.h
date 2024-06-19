#ifndef HANDLERS_H
#define HANDLERS_H

#include "httplib.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace httplib;

void add_cors_headers(Response& res);

void crearUsuario(const Request& req, Response& res, sql::Connection* con);
void crearGrupo(const Request& req, Response& res, sql::Connection* con);
void crearAccion(const Request& req, Response& res, sql::Connection* con);
void asignarGrupo(const Request& req, Response& res, sql::Connection* con);
void asignarAccion(const Request& req, Response& res, sql::Connection* con);
void obtenerRelacionesUsuarioGrupo(const Request& req, Response& res, sql::Connection* con);

#endif // HANDLERS_H
