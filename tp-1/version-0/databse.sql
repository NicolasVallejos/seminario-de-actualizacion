CREATE DATABASE sistema_multiusuario;
USE sistema_multiusuario;

-- Tabla de Usuarios
CREATE TABLE Usuarios (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL
);

-- Tabla de Grupos de Usuarios
CREATE TABLE Grupos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL UNIQUE
);

-- Tabla de Acciones
CREATE TABLE Acciones (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL UNIQUE
);

-- Tabla de Usuarios y Grupos
CREATE TABLE Usuarios_Grupos (
    usuario_id INT,
    grupo_id INT,
    FOREIGN KEY (usuario_id) REFERENCES Usuarios(id),
    FOREIGN KEY (grupo_id) REFERENCES Grupos(id),
    PRIMARY KEY (usuario_id, grupo_id)
);

-- Tabla de Grupos y Acciones
CREATE TABLE Grupos_Acciones (
    grupo_id INT,
    accion_id INT,
    FOREIGN KEY (grupo_id) REFERENCES Grupos(id),
    FOREIGN KEY (accion_id) REFERENCES Acciones(id),
    PRIMARY KEY (grupo_id, accion_id)
);
