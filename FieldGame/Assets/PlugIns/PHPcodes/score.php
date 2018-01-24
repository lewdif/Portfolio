<?php

include "../parse_input.php";

header("Content-Type: application/json");

session_start();

$inc = $_POST["score_res"];

$response = [ "error" => "no" ];

if (empty($_SESSION["userid"])) {
	$response["error"] = "you haven't logged.";
	echo json_encode($response);
	return;
}

$userid = $_SESSION['userid'];

$conn = mysql_connect("localhost", "graduate", "bitnami");
$db = mysql_select_db('my_game');

// the following is called only when hp is not configured yet.
if (empty($_SESSION['score']) ) // if hp is not available in the session, get it from MySQL.
{
	$sql = "select score from UserAccount where userid='" . $userid . "'";
	$result = mysql_query($sql);

	$n_rows = mysql_num_rows($result);
	if ($n_rows == 1) {
		$obj = mysql_fetch_object($result);

		$_SESSION["score"] = $obj->score;
	}
	else {
		$response["error"] = "not registered or not matched password.";
		echo json_encode($response);
		return;
	}
	mysql_free_result($result);
}

// $_SESSION["hp"] should not be empty.

$_SESSION["score"] = $inc;

$sql = "update UserAccount set score=" . $_SESSION['score'] . " where userid='" . $userid . "'";
mysql_query($sql);

// use mysql_affected_rows to make sure your update is done correctly.
if ( mysql_affected_rows($conn) == false) {
	$response["error"] = 'update failed';
}

mysql_close($conn);

$response["score"] = $_SESSION["score"];

echo json_encode($response);

?>
