create database contacto;

use contacto;

CREATE TABLE `usuarios` (
  `cod` int(50) NOT NULL,
  `nom` varchar(50) NOT NULL,
  `correo` varchar(50) NOT NULL,
  `tel` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

ALTER TABLE `usuarios`
  ADD PRIMARY KEY (`cod`);
  
  ALTER TABLE `usuarios`
  MODIFY `cod` int(50) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=32448;
  
  INSERT INTO `usuarios` (`cod`, `nom`, `correo`, `tel`) VALUES
(32412, 'Lionel Andres Messi', 'Lionel123@outlock.com', 123456789),
(32413, 'Claudio Tapia', 'claudito223@gmail.com', 342568124),
(32414, 'Raul Gonzales Blanco', 'raul7@hotmail.com', 134653246),
(32425, 'Ronaldo Nazario', 'NazarioOK@gmail.com', 2147483647),
(32447, 'Martin Palermo', 'martinloco9@gmail.com', 111111111);