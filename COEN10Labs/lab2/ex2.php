<html>
<body>
<?php
	$num1 = $_POST["num1"]
	$num2 = $_POST["num2"]
	$num3 = $_POST["num3"]
	if($num3 == $num1*$num2) {
		echo "Correct"
	} else {
		echo "Incorrect"
		
	}
?>
<form method="POST" action"ex.php">
	<input type="submit" value="Try again"/>
</form>


</body>
</html>
