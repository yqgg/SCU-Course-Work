<html>
<body>
<?php
	$num1 = $_POST["num1"];
	$num2 = $_POST["num2"];
	$num3 = $_POST["num3"];
	$num4 = $_POST["num4"];
	$num5 = $_POST["num5"];
	$nums = array($num1, $num2, $num3, $num4, $num5);
	
	$size = count($nums);
	echo "Numbers Submitted: ";
	//print user's guesses
	for($i=0; $i<$size; $i++){
		echo $nums[$i]." ";
	}

	$lotNums = array();
	$size = count($nums);
	
	echo"<br>";
	echo"Lottery Numbers: ";
	//create an array of five random unique integers. The lottery numbers.
	for($i=0; $i<$size; $i++){
		$lotNums[$i]=rand(1,20);
		for($j=$i-1; $j>=0; $j--){
			if($lotNums[$i]==$lotNums[$j]){
				$i--;
				break;
			}
		} 	 
	}
	
	//print out randomly generated unique lottery numbers
	for($i=0; $i<$size; $i++) {
		echo $lotNums[$i]." ";
	}
	
	$matchesFound = False;
	$count = 0;
	//Find any matches between user input and lottery numbers.
	for($i=0; $i<$size; $i++) {
		for($j=0; $j<$size; $j++) {
			if($nums[$j] == $lotNums[$i]){
				$matchesFound = True;
				$count++;
			}
		}
	}
	
	echo "<br>";
	if($matchesFound = True) {
		echo "You correctly guessed ".$count." numbers";
	} else {
		echo "You didn't guess any numbers correctly :(";
	}

?>
<form method="POST" action="lottery1.php">
	<input type="submit" value="Guess Again!" />
</form>
</body>
</html>


