<?php
session_start();

if(isset($_SESSION['message'])) {
  echo $_SESSION['message'];
  unset($_SESSION['message']);
}

$mysqli = new mysqli("localhost", "root", "", "lab7");
if($mysqli->connect_error) {
  exit('Could not connect');
}

echo '<form method="POST" action="add_grade.php">';

$sql = "SELECT id, name FROM subjects WHERE 1";

$stmt = $mysqli->prepare($sql);
$stmt -> execute();
$stmt -> bind_result($id, $name);
$stmt -> store_result();

echo "Disciplina: ";
echo '<select id="subject" name="subject">';
while($stmt->fetch()) {
  echo '<option value="'. $id .'">'. $name .'</option>';
}
echo '</select>';

$sql = "SELECT id, name FROM students WHERE 1";

$stmt = $mysqli->prepare($sql);
$stmt -> execute();
$stmt -> bind_result($id, $name);
$stmt -> store_result();

echo "Student: ";
echo '<select id="student" name="student">';
while($stmt->fetch()) {
  echo '<option value="'. $id .'">'. $name .'</option>';
}
echo '</select>';

echo '<input type="number" name="grade" id="grade" min="1" max="10"/>';
echo '<input type="submit" value="Adauga nota"/>';

echo "</form>";
?>