<?php

 
$hostname = "localhost"; 
$username = "root"; 
$password = "hafizalihamza9"; 
$database = "soilmoisture_db"; 

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) { 
	die("Connection failed: " . mysqli_connect_error()); 
} 

echo "Database connection is OK<br>"; 

if(isset($_POST["Moisture"])) {
    $m = $_POST["Moisture"];

    $sql = "INSERT INTO dht11 (Moisture) VALUES (".$m.")"; 

    if (mysqli_query($conn, $sql)) { 
        echo "\nNew record created successfully"; 
    } else { 
        echo "Error: " . $sql . "<br>" . mysqli_error($conn); 
    }
}

?>