<?php


// if you want to access from ajax.html, enable JSON_INPUT
//define('JSON_INPUT', 1);
// if you want to access from Unity, disable JSON_INPUT by commenting out above line.

$json = null;
if (defined('JSON_INPUT'))
{
	$key = key($_REQUEST);
	$json = json_decode( stripslashes($key), true);
}
else {
	$json = $_REQUEST;
}

?>
