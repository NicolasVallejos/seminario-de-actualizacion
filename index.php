<?php
include_once("src/conexion.php"); 
?>
<html>
<head>    
		<title>Contactos</title>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="styles/style.css">
</head>
<body>
    <table>

			<tr><th colspan="5"><h1>Contactos</h1><th><a style="font-weight: normal; font-size: 14px;" onclick="abrirform()">Agregar</a></th></tr>
			<tr>
		    <th>Nro</th>
			<th>Código</th>
            <th>Nombre</th>
            <th>Correo</th>
            <th>Teléfono</th>
            <th>Acción</th>
			</tr>
        <?php 

   
        $queryusuarios = mysqli_query($conn, "SELECT * FROM usuarios ORDER BY cod asc");
    
		$numerofila = 0;
        while($mostrar = mysqli_fetch_array($queryusuarios)) 
		{    $numerofila++;    
            echo "<tr>";
			echo "<td>".$numerofila."</td>";
            echo "<td>".$mostrar['cod']."</td>";
            echo "<td>".$mostrar['nom']."</td>";
            echo "<td>".$mostrar['correo']."</td>";    
			echo "<td>".$mostrar['tel']."</td>";  
            echo "<td style='width:26%'><a href=\"src/editar.php?cod=$mostrar[cod]\">Modificar</a> | <a href=\"src/eliminar.php?cod=$mostrar[cod]\" onClick=\"return confirm('¿Estás seguro de eliminar a $mostrar[nom]?')\">Eliminar</a></td>";           
}
        ?>
    </table>
	 <script>
function abrirform() {
  document.getElementById("formregistrar").style.display = "block";
  
}

function cancelarform() {
  document.getElementById("formregistrar").style.display = "none";
}

</script>
<div class="caja_popup" id="formregistrar">
  <form action="src/agregar.php" class="contenedor_popup" method="POST">
        <table>
		<tr><th colspan="2">Nuevo usuario</th></tr>
            <tr> 
                <td>Nombre</td>
                <td><input type="text" name="txtnombre" required></td>
            </tr>
            <tr> 
                <td>Correo</td>
                <td><input type="email" name="txtcorreo" required></td>
            </tr>
            <tr> 
                <td>Teléfono</td>
                <td><input type="number" name="txttelefono" required></td>
            </tr>
            <tr> 	
               <td colspan="2">
				   <button type="button" onclick="cancelarform()">Cancelar</button>
				   <input type="submit" name="btnregistrar" value="Registrar" onClick="javascript: return confirm('¿Deseas registrar a este usuario?');">
			</td>
            </tr>
        </table>
    </form>
</div>
</body>
</html>