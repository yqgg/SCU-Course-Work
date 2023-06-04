<html>
<body>
<?php
	$guess = $_POST["guess"];
	$numbers = array();
	for($i=0; $i<5; $i+=1)
	{
		array_push($numbers, rand(1,20));	
	}
	foreach($numbers as $num) {
		echo $num."  ";
	}
	echo "Your guess: ".$guess;	
	$result=False;
	$i=0;
	while($result==False && $i<5){
		if($guess==$numbers[$i]){
			echo "<br>";
			echo " You got it!";
			$result=True;
		}
		if($i==4) {
			echo "<br>";
			echo " Wrong!";
		}
		$i++;
	}		
?>

<form method="POST" action="ar.php">
	<input type="submit" value="Try again"/>
</form>
</body>
</html>
