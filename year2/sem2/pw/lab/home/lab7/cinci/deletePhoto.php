<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

session_start();

if(isset($_GET['filename'])) {
    unlink($_GET['filename']);
    $_SESSION['message'] = 'Imaginea a fost stearsa cu succes';
} else {
    $_SESSION['message'] = 'Imaginea nu a putut fi stearsa';
}

header("Location: userView.php");

?>