<?php

#header("Access-Control-Allow-Origin: *")
$mysqli = new mysqli("localhost", "root", "", "lab6");
if($mysqli->connect_error) {
  exit('Could not connect');
}


if($_GET['type']=="count") {
  $sql = "SELECT COUNT(*) FROM persons WHERE 1";

  $stmt = $mysqli->prepare($sql);
  $stmt -> execute();
  $stmt -> bind_result($count);
  $stmt -> fetch();
  $stmt -> close();

  echo $count;
    
} else {

  $sql = "SELECT Nume, Prenume, Telefon, Email FROM persons WHERE 1";
  $stmt = $mysqli->prepare($sql);
  $stmt -> execute();
  $stmt -> bind_result($nume, $prenume, $telefon, $email);
  $stmt -> store_result();

  $page = $_GET['page'];
  $perPage = $_GET['perPage'];
  $start = $page * $perPage;
  $end = ($page + 1) * $perPage;
  $index = 0;

  echo "<table>";
  echo "<tr><th>Nume</th><th>Prenume</th><th>Telefon</th><th>Email</th></tr>";
  while($stmt->fetch()) {
    if($index >= $start && $index < $end) {
      echo "<tr><td>" . $nume . "</td><td>" . $prenume . "</td><td>" . $telefon . "</td><td>" . $email . "</td></tr>";
    } else if($index >= $end) {
      break;
    }
    $index++;
  }
  echo "</table>";

  $stmt->free_result();
  $stmt->close();
}
?>
