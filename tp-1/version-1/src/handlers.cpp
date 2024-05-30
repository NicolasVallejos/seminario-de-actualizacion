#include "handlers.h"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

void add_cors_headers(Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

void crearUsuario(const Request& req, Response& res, sql::Connection* con) {
    add_cors_headers(res);
    if (req.method == "OPTIONS") {
        return;
    }

    try {
        json j = json::parse(req.body);
        std::string nombre = j["nombre"];
        std::string email = j["email"];
        std::string password = j["password"];

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Usuarios (nombre, email, password) VALUES (?, ?, ?)"));
        pstmt->setString(1, nombre);
        pstmt->setString(2, email);
        pstmt->setString(3, password);
        pstmt->execute();

        json response = {{"message", "Nuevo usuario creado!"}};
        res.set_content(response.dump(), "application/json");
    } catch (const sql::SQLException& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void crearGrupo(const Request& req, Response& res, sql::Connection* con) {
    add_cors_headers(res);
    if (req.method == "OPTIONS") {
        return;
    }

    try {
        json j = json::parse(req.body);
        std::string nombre = j["nombre"];

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Grupos (nombre) VALUES (?)"));
        pstmt->setString(1, nombre);
        pstmt->execute();

        json response = {{"message", "Nuevo grupo creado!"}};
        res.set_content(response.dump(), "application/json");
    } catch (const sql::SQLException& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void crearAccion(const Request& req, Response& res, sql::Connection* con) {
    add_cors_headers(res);
    if (req.method == "OPTIONS") {
        return;
    }

    try {
        json j = json::parse(req.body);
        std::string nombre = j["nombre"];

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Acciones (nombre) VALUES (?)"));
        pstmt->setString(1, nombre);
        pstmt->execute();

        json response = {{"message", "Nueva acción creada!"}};
        res.set_content(response.dump(), "application/json");
    } catch (const sql::SQLException& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void asignarGrupo(const Request& req, Response& res, sql::Connection* con) {
    add_cors_headers(res);
    if (req.method == "OPTIONS") {
        return;
    }

    try {
        int usuarioID = std::stoi(req.matches[1]);
        json j = json::parse(req.body);
        int grupoID = j["grupo_id"];

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Usuarios_Grupos (usuario_id, grupo_id) VALUES (?, ?)"));
        pstmt->setInt(1, usuarioID);
        pstmt->setInt(2, grupoID);
        pstmt->execute();

        json response = {{"message", "Grupo asignado al usuario!"}};
        res.set_content(response.dump(), "application/json");
    } catch (const sql::SQLException& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void asignarAccion(const Request& req, Response& res, sql::Connection* con) {
    add_cors_headers(res);
    if (req.method == "OPTIONS") {
        return;
    }

    try {
        int grupoID = std::stoi(req.matches[1]);
        json j = json::parse(req.body);
        int accionID = j["accion_id"];

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO Grupos_Acciones (grupo_id, accion_id) VALUES (?, ?)"));
        pstmt->setInt(1, grupoID);
        pstmt->setInt(2, accionID);
        pstmt->execute();

        json response = {{"message", "Acción asignada al grupo!"}};
        res.set_content(response.dump(), "application/json");
    } catch (const sql::SQLException& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void obtenerRelacionesUsuarioGrupo(const Request& req, Response& res, sql::Connection* con) {
    add_cors_headers(res);
    if (req.method == "OPTIONS") {
        return;
    }

    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> resSet(stmt->executeQuery("SELECT Usuarios.id AS usuario_id, Usuarios.nombre AS usuario_nombre, Grupos.id AS grupo_id, Grupos.nombre AS grupo_nombre FROM Usuarios JOIN Usuarios_Grupos ON Usuarios.id = Usuarios_Grupos.usuario_id JOIN Grupos ON Grupos.id = Usuarios_Grupos.grupo_id"));

        json response = json::array();
        while (resSet->next()) {
            json relation = {
                {"usuario_id", resSet->getInt("usuario_id")},
                {"usuario_nombre", resSet->getString("usuario_nombre")},
                {"grupo_id", resSet->getInt("grupo_id")},
                {"grupo_nombre", resSet->getString("grupo_nombre")}
            };
            response.push_back(relation);
        }

        res.set_content(response.dump(), "application/json");
    } catch (const sql::SQLException& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        res.status = 500;
        json response = {{"error", e.what()}};
        res.set_content(response.dump(), "application/json");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
