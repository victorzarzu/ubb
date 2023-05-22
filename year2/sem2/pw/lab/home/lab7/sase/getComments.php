<?php
$mysqli = new mysqli("localhost", "root", "", "lab7");
if($mysqli->connect_error) {
  exit('Could not connect');
}

$sql = "SELECT text, user_name FROM comments WHERE approved = 1";

$stmt = $mysqli -> prepare($sql);
$stmt -> execute();
$stmt -> bind_result($text, $user_name);
$stmt -> store_result();

echo '<ul style="list-style-type: none">';

while($stmt -> fetch()) {
    echo '<li>'. $user_name .': '. $text .'</li>';
}

echo '</ul>';
?>