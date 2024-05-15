<?php
$conn = new mysqli("127.0.0.1","root","","contacto");
	
	if($conn->connect_errno)
	{
		echo "No hay conexión: (" . $conn->connect_errno . ") " . $conn->connect_error;
	}
?>