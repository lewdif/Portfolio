<?php
	
include "../parse_input.php";
	
header("Content-Type: application/json");

session_start();

$response = [ "error" => "no" ];

if (empty($_SESSION['userid'])) {
	$response["error"] = "you haven't logged.";
}

echo json_encode($response);

session_destroy();

?>