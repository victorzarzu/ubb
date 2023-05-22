<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

$mysqli = new mysqli("localhost", "root", "", "lab7");
if($mysqli->connect_error) {
  exit('Could not connect');
}

$approved = 0;
$sql = "INSERT INTO comments(text, approved, user_name) VALUES(?, ?, ?)";

$stmt = $mysqli -> prepare($sql);
$stmt -> bind_param("sis", $_POST['comment'], $approved, $_POST['name']);
$stmt -> execute();

header("Location: index.html");

?>