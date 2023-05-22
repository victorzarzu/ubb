<?php
$mysqli = new mysqli("localhost", "root", "", "lab7");
if($mysqli->connect_error) {
  exit('Could not connect');
}

$sql = "UPDATE comments SET approved = 1 WHERE id = ?";

$stmt = $mysqli -> prepare($sql);
$stmt -> bind_param('i', $_GET['id']);
$stmt -> execute();

header("Location: adminPage.php");
?>