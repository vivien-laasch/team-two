<?php

if(isset($_GET["temperature"]) && isset($_GET["humidity"])) {
   $temperature = $_GET["temperature"]; // get temperature value from HTTP GET
   $humidity = $_GET["humidity"];

   $servername = "localhost";
   $username = "root";
   $password = "";
   $dbname = "team-two";

   // Create connection
   $conn = new mysqli($servername, $username, $password, $dbname);
   // Check connection
   if ($conn->connect_error) {
      echo("Connection failed: " . $conn->connect_error);
   }

   $sql = "INSERT INTO measurements (temperature,humidity) VALUES ($temperature, $humidity)";

   if ($conn->query($sql) === TRUE) {
      echo "New record created successfully";
   } else {
      echo "Error: " . $sql . " => " . $conn->error;
   }

   $conn->close();
} else {
   echo "temperature or humidity is not set";
}
?>