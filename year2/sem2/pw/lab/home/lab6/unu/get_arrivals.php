<?php

#header("Access-Control-Allow-Origin: *")
$mysqli = new mysqli("localhost", "root", "", "lab6");
if($mysqli->connect_error) {
  exit('Could not connect');
}

$sql = "SELECT DISTINCT arrival FROM trains WHERE departure = ?";

$stmt = $mysqli->prepare($sql);
$stmt -> bind_param("s", $_GET['departure']);
$stmt -> execute();
$stmt -> bind_result($result);

while ($stmt->fetch()) {
  echo "<li>" . $result . "</li>";
}

$stmt->close();
?>

<?php