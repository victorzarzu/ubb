<?php

#header("Access-Control-Allow-Origin: *")
$mysqli = new mysqli("localhost", "root", "", "lab6");
if($mysqli->connect_error) {
  exit('Could not connect');
}

if($_GET['type'] == "id") {
    $sql = "SELECT id FROM persons";

    $stmt = $mysqli->prepare($sql);
    $stmt -> execute();
    $stmt -> bind_result($ids);

    while($stmt->fetch()) {
        echo "<option>" . $ids . "</option>";
    }

    $stmt -> close();

} else if ($_GET['type'] == "person") {

    $sql = "SELECT Nume, Prenume, Telefon, Email FROM persons WHERE id = ?";
    $stmt = $mysqli->prepare($sql);
    $stmt -> bind_param("i", $_GET['id']);
    $stmt -> execute();
    $stmt -> bind_result($nume, $prenume, $telefon, $email);
    $stmt -> fetch();
  
    $data = array("Nume" => $nume, "Prenume" => $prenume, "Telefon" => $telefon, "Email" => $email);

    header("Content-Type: application/json");
    echo json_encode($data);

    $stmt->free_result();
    $stmt->close();    
} else {
    $sql = "UPDATE persons SET Nume = ?, Prenume = ?, Telefon = ?, Email = ? WHERE id = ?";

    $stmt = $mysqli->prepare($sql);
    $stmt -> bind_param("ssssi", $_POST['nume'], $_POST['prenume'], $_POST['telefon'], $_POST['email'], $_POST['id']);
    $stmt -> execute();
}
?>
