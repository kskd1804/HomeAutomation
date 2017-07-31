<?php
header('Content-Type: application/json');
if(isset($_POST['hostname']) && isset($_POST['username']) && isset($_POST['database']) && isset($_POST['relay_id'])){
	$host = $_POST['hostname'];
	$username = $_POST['username'];
	$password = $_POST['password'];
	$database = $_POST['database'];
	$con = mysqli_connect($host,$username,$password,$database);
	if(mysqli_connect_errno()){
		die('Connection failure!');	
	}else{
		$relay_id = mysqli_real_escape_string($con,$_POST['relay_id']);
		$sql = "SELECT * FROM relay WHERE id IN (SELECT MAX(id) FROM relay GROUP BY device_id) AND relay_id='$relay_id'";
		$query = mysqli_query($con,$sql);
		if($query){
			$count = mysqli_num_rows($query);
			if($count>0){
				while($row = mysqli_fetch_assoc($query)){
					printf("%d\n",$row['id']);
					printf("%s\n",$row['relay_id']);
					printf("%s\n",$row['device_id']);
					printf("%s\n",$row['device_type']);
					printf("%s\n",$row['value']);
				}
			}else{
				echo 'No records!';	
			}
		}else{
			echo 'Query Unsuccessful!';	
		}
	}
}else{
	echo 'Please enter all values!';
}
?>