<?php

#header("Access-Control-Allow-Origin: *")
$mysqli = new mysqli("localhost", "root", "", "lab6");
if($mysqli->connect_error) {
  exit('Could not connect');
}

$sql = "SELECT DISTINCT departure FROM trains";

$stmt = $mysqli->prepare($sql);
$stmt->execute();
$stmt->bind_result($result);

echo "<option>---Select---</option>";
while ($stmt->fetch()) {
  echo "<option value='" . $result . "'>" . $result . "</option>";
}

$stmt->close();
?>
