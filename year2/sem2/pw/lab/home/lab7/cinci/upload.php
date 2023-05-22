<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

session_start();

$target_dir = $_SERVER['DOCUMENT_ROOT'] . "/lab7/photos/" . $_SESSION['id'] . "/";
$target_file = $target_dir . basename($_FILES['image']['name']);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

if(isset($_POST['submit'])) {
    $check = getimagesize($_FILES['image']['tmp_name']);
    if($check !== false) {
        $uploadOk = 1;
    } else {
        $_SESSION['message'] = 'Imagine incorecta';
        header("Location: userView.php");
        header("Status: 404 Not Found");
        $uploadOk = 0;
    }
}

if (file_exists($target_file)) {
    $_SESSION['message'] = 'Imagine deja existenta';
    header("Location: userView.php");
    $uploadOk = 0;
}

if($_FILES['image']['size'] > 300000) {
    $_SESSION['message'] = 'Imagine prea mare';
    header("Location: userView.php");
    $uploadOk = 0;
}

if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg") {
    $_SESSION['message'] = "Singurele formate acceptate sunt: JPG, JPEG si PNG.";
    header("Location: userView.php");
    $uploadOk = 0;
}

if(move_uploaded_file($_FILES['image']['tmp_name'], $target_file)) {
    $_SESSION['message'] = "Imaginea a fost salvata cu succes";
    header("Location: userView.php");
} else {
    $_SESSION['message'] = "Imaginea nu a putut fi salvata";
    header("Location: userView.php");
}

?>
