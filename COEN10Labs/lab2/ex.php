<html>
<body>
<?php
	$num1 = rand(0,12)
	$num2 = rand(0,12)
	echo $num1." x ".$num2
?>
<form action="ex2.php" method = "POST">
	<input type= "hidden" name="num1" value="<?php eccho $num1;?>"/>
	<input type= "hidden" name="num2" value="<?php echo $num2;?>"/>
	<input type= "number" name="num3"/>
	<input type="submit" value="Calculate!"/>
</form>

</body>
</html>
