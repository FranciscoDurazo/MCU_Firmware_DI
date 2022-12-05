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
//Update the database
if (isset($_POST['value1'])) {
	$val = $_POST['value1'];	
	$sql = "SELECT * FROM Sensor WHERE id = 1;";
	$result   = mysqli_query($conn, $sql);
	$row  = mysqli_fetch_assoc($result);
	
	$update = mysqli_query($conn, "UPDATE Sensor SET sense = '$val' WHERE id = 1;");
	//echo $led_id;
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
	
?>