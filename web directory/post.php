<?php
header("Content-Type: text/html; charset=utf-8");
$conn=mysql_connect('localhost','user','134679852zk') or die("MYSQL_connect:".mysql_errno());
mysql_query("use test");
mysql_query("set names 'utf8'");
$user_name=$_POST['username'];
$user_password=$_POST['userpassword'];
if ($user_name==''||$user_password==''){
	echo "<meta http-equiv=refresh content='0;url=../lose.html'>";
	return;
}
if (mysql_query("insert into information set name='$user_name',password='$user_password'",$conn)){
	echo "<meta http-equiv=refresh content='0;url=../success.html'>";
}
else{
	echo "<meta http-equiv=refresh content='0;url=../lose.html'>";
}

?>
