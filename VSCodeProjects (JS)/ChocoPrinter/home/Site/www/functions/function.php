<?php
    // $mysqli = false;
    // $mysqli = new mysqli("localhost","root","","rp-base");
    // $mysqli->query("SET NAMES 'utf8'");
    // if( $mysqli == true) echo 'Nuxw';
    // $success = $mysqli->query ("INSERT INTO `users`(`first_name`, `last_name`, `group`) VALUES ('coto','dd','da')");
    // if ($success == true) echo 'ok';
    // echo 'hi';
    // $mysqli->close();
    $first_name = htmlspecialchars($_POST['first_name']);
    $last_name = htmlspecialchars($_POST['last_name']);
    $group = htmlspecialchars($_POST['group']);
    $rop = htmlspecialchars($_POST['rop']);
    $telephone = htmlspecialchars($_POST['telephone']);
    $email = htmlspecialchars($_POST['email']);
    // $first_name = 'Hello';
    // $last_name = 'Hi';
    // $group = 'gov';
    function godb ($a,$b,$c,$d,$e,$f){
        $mysqli = new mysqli("localhost","root","","rp-base");
        $mysqli->query("SET NAMES 'utf8'");
        $mysqli->query ("INSERT INTO `users`(`first_name`, `last_name`, `group`, `rop`, `phone`, `email`) VALUES ('$a','$b','$c','$d','$e','$f')");
        echo 'Сообщение отправлено';
        echo '- в базу данных занесено';
        $mysqli->close();
    }
    godb($first_name,$last_name,$group,$rop,$telephone,$email);
?>