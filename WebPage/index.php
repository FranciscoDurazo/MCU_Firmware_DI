<?php

$servername = "localhost";
$dBUsername = "id19945412_fcodl2001";
$dBPassword = "97_ysi-@<UoI+09c";
$dBName = "id19945412_daq_cntrl";

$conn = mysqli_connect($servername, $dBUsername, $dBPassword, $dBName);

if (!$conn) {
	die("Connection failed: ".mysqli_connect_error());
}


if (isset($_POST['toggle_LED'])) {
	$sql = "SELECT * FROM Sensor;";
	$result   = mysqli_query($conn, $sql);
	$row  = mysqli_fetch_assoc($result);
	
	if($row['status'] == 0){
		$update = mysqli_query($conn, "UPDATE Sensor SET status = 1 WHERE id = 1;");		
	}		
	else{
		$update = mysqli_query($conn, "UPDATE Sensor SET status = 0 WHERE id = 1;");		
	}
}



$sql = "SELECT * FROM Sensor;";
$result = mysqli_query($conn, $sql);
$row  = mysqli_fetch_assoc($result);	

?>

<style>
	.wrapper{
		width: 100%;
		padding-top: 50px;
	}
	.col_3{
		width: 33.3333333%;
		float: left;
		min-height: 1px;
	}
	#submit_button{
		background-color: #2bbaff; 
		color: #FFF; 
		font-weight: bold; 
		font-size: 40; 
		border-radius: 15px;
    	text-align: center;
	}
	.led_img{
		height: 400px;		
		width: 100%;
		object-fit: cover;
		object-position: center;
	}
	
	@media only screen and (max-width: 600px) {
		.col_3 {
			width: 100%;
		}
		.wrapper{
			width: 100%;
			padding-top: 5px;
		}
		.led_img{
			height: 300px;		
			width: 80%;
			margin-right: 10%;
			margin-left: 10%;
			object-fit: cover;
			object-position: center;
		}
	}

</style>


<html>
<head>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.0/jquery.min.js" type="text/javascript"></script>
	<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
	<div class="wrapper" id="refresh">
		<div class="col_3">
		</div>

		<div class="col_3" >
			
			<?php echo '<h1 style="text-align: center;">Output Status: '.$row['status'].'</h1>';?>
			
			<div class="col_3">
			</div>
			
			<div class="col_3" style="text-align: center;">
			<form action="index.php" method="post" id="LED" enctype="multipart/form-data">			
				<input id="submit_button" type="submit" name="toggle_LED" value="Toggle Output" />
			</form>
				
			<script type="text/javascript">
			$(document).ready (function () {
				var updater = setTimeout (function () {
					$('div#refresh').load ('index.php', 'update=true');
				}, 1000);
			});
			</script>
			<!--<br>-->
			<?php
				if($row['status'] == 0){?>
			<!--	<div class="led_img">
					<img id="contest_img" src="led_off.png" width="50%" height="50%">
				</div>
				-->
			<?php	
				}
				else{ ?>
			<!--	<div class="led_img">
					<img id="contest_img" src="led_on.png" width="50%" height="50%">
				</div>
				-->
			<?php
				}
			?>
			<?php echo '<h1 style="text-align: center;">Sensor Reading: '.$row['sense'].'°C</h1>';?>	
				
				
			</div>
				
			<div class="col_3">
			</div>
		</div>

		<div class="col_3">
		</div>
	</div>
</body>
</html>

</html>
