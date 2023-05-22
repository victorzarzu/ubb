<?php

$mysqli = new mysqli("localhost", "root", "", "lab6");
if($mysqli->connect_error) {
  exit('Could not connect');
}

if($_GET['type'] == 'info') {
    $sql1 = "SELECT DISTINCT producator FROM products";
    $sql2 = "SELECT DISTINCT procesor FROM products";
    $sql3 = "SELECT DISTINCT memorie FROM products";

    $stmt1 = $mysqli->prepare($sql1);
    $stmt1->execute();
    $result1 = $stmt1->get_result();

    $stmt2 = $mysqli->prepare($sql2);
    $stmt2->execute();
    $result2 = $stmt2->get_result();

    $stmt3 = $mysqli->prepare($sql3);
    $stmt3->execute();
    $result3 = $stmt3->get_result();

    $producator_array = array();
    while ($row1 = $result1->fetch_assoc()) {
        $producator_array[] = $row1['producator'];
    }

    $procesor_array = array();
    while ($row2 = $result2->fetch_assoc()) {
        $procesor_array[] = $row2['procesor'];
    }

    $memorie_array = array();
    while ($row3 = $result3->fetch_assoc()) {
        $memorie_array[] = $row3['memorie'];
    }

    $result_array = array(
        "producator" => $producator_array,
        "procesor" => $procesor_array,
        "memorie" => $memorie_array
    );

    echo json_encode($result_array);
}

?>
