<?php

session_start();

$mysqli = new mysqli("localhost", "root", "", "lab7");
if($mysqli->connect_error) {
  exit('Could not connect');
}

if(!is_int($_POST['grade']) || $_POST['grade'] < 1 || $_POST['grade'] > 10) {
    $_SESSION['message'] = "Nota nu a putut fi adaugata";
    header("Location: teacherView.php");
}

$sql = "INSERT INTO grades(subject_id, student_id, grade) VALUES(?,?, ?)";

$stmt = $mysqli->prepare($sql);
$stmt -> bind_param('iii', $_POST['subject'], $_POST['student'], $_POST['grade']);

if($stmt->execute()) {
    $_SESSION['message'] = "Nota adaugata cu success";
    header("Location: teacherView.php");
} else {
    $_SESSION['message'] = "Nota nu a putut if adaugata";
    header("Location: teacherView.php");
}
?>