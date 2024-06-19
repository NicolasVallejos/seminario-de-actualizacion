#include "httplib.h"
#include "handlers.h"
#include "database.h"
#include <iostream>

using namespace httplib;

int main() {
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection* con = connectDatabase(driver);

    Server svr;

    svr.Post("/usuarios", [con](const Request& req, Response& res) { crearUsuario(req, res, con); });
    svr.Post("/grupos", [con](const Request& req, Response& res) { crearGrupo(req, res, con); });
    svr.Post("/acciones", [con](const Request& req, Response& res) { crearAccion(req, res, con); });
    svr.Post(R"(/usuarios/(\d+))", [con](const Request& req, Response& res) { asignarGrupo(req, res, con); });
    svr.Post(R"(/grupos/(\d+))", [con](const Request& req, Response& res) { asignarAccion(req, res, con); });
    svr.Get("/relaciones", [con](const Request& req, Response& res) { obtenerRelacionesUsuarioGrupo(req, res, con); });

    // Manejar opciones CORS 
    svr.Options("/usuarios", [](const Request&, Response& res) { add_cors_headers(res); });
    svr.Options("/grupos", [](const Request&, Response& res) { add_cors_headers(res); });
    svr.Options("/acciones", [](const Request&, Response& res) { add_cors_headers(res); });
    svr.Options(R"(/usuarios/(\d+))", [](const Request&, Response& res) { add_cors_headers(res); });
    svr.Options(R"(/grupos/(\d+))", [](const Request&, Response& res) { add_cors_headers(res); });
    svr.Options("/relaciones", [](const Request&, Response& res) { add_cors_headers(res); });

    std::cout << "Servidor escuchando en http://localhost:8080" << std::endl;
    svr.listen("localhost", 8080);

    delete con;
    return 0;
}
