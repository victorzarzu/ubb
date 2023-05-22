<?php
session_start();

$mysqli = new mysqli("localhost", "root", "", "lab7");
if($mysqli->connect_error) {
  exit('Could not connect');
}

$sql = "SELECT id, text, user_name FROM comments WHERE approved = 0";

$stmt = $mysqli -> prepare($sql);
$stmt -> execute();
$stmt -> bind_result($id, $text, $user_name);
$stmt -> store_result();

echo '<table style="border: 1px solid black;border-collapse: collapse">';
echo '<tr><th>User name</th><th>Text</th><th>Approve</th></tr>';

while($stmt -> fetch()) {
    echo '<tr><td>'. $user_name .'</td><td>'. $text .'</td><td><button onclick="window.location.href=\'./approveComment.php?id='. $id .'\'">Approve</button></td></tr>';
}

echo '<table>';
?>