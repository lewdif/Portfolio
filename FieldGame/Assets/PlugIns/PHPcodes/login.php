<?php

include "../parse_input.php";

header("Content-Type: application/json");

$response = [ "error" => "no" ];

session_start();

$userid = $_POST["userid"];
$passwd = $_POST["password"];

$_SESSION['userid'] = null;

$conn = mysql_connect("localhost", "graduate", "bitnami");
$db = mysql_select_db("my_game");

$sql = "select userid, name from UserAccount where userid='" . $userid . "' and passwd=sha2('" . $passwd . "', 224)";
$result = mysql_query($sql); // request query

$n_rows = mysql_num_rows($result); // if you find matched user/password, it will return 1.
if ($n_rows == 1) { // found the matched user.
	$obj = mysql_fetch_object($result); // retrieve userid, name with PHP object.

	$_SESSION["userid"] = $obj->userid;

	$response["userid"] = $obj->userid;
	$response["name"] = $obj->name;	// make sure you get the data from MySQL.
}
else {
	$response["error"] = "not registered or not matched password.";
}

mysql_free_result($result);
mysql_close($conn);

echo json_encode($response);

?>
