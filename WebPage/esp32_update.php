<?php
$servername = "localhost";
$dBUsername = "id19945412_fcodl2001";
$dBPassword = "97_ysi-@<UoI+09c";
$dBName = "id19945412_daq_cntrl";
$conn = mysqli_connect($servername, $dBUsername, $dBPassword, $dBName);
if (!$conn) {
	die("Connection failed: ".mysqli_connect_error());
}

//Read the database
if (isset($_POST['check_LED_status'])) {
	$led_id = $_POST['check_LED_status'];	
	$sql = "SELECT * FROM Sensor WHERE id = '$led_id';";
	$result   = mysqli_query($conn, $sql);
	$row  = mysqli_fetch_assoc($result);
	if($row['status'] == 0){
		echo "LED_is_off";
	}
	else{
		echo "LED_is_on";
	}	
}	
//Request GET
if (isset($_GET)) {
	$sql = "SELECT * FROM Sensor WHERE id = '1';";
	$result   = mysqli_query($conn, $sql);
	$row  = mysqli_fetch_assoc($result);
	if($row['status'] == 0){
		echo "LED_is_off";
	}
	else{
		echo "LED_is_on";
	}	
}
//Update the database
if (isset($_POST['toggle_LED'])) {
	$led_id = $_POST['toggle_LED'];	
	$sql = "SELECT * FROM Sensor WHERE id = '$led_id';";
	$result   = mysqli_query($conn, $sql);
	$row  = mysqli_fetch_assoc($result);
	if($row['status'] == 0){
		$update = mysqli_query($conn, "UPDATE Sensor SET status = 1 WHERE id = 1;");
		echo "LED_is_on";
	}
	else{
		$update = mysqli_query($conn, "UPDATE Sensor SET status = 0 WHERE id = 1;");
		echo "LED_is_off";
	}	
}	
?>