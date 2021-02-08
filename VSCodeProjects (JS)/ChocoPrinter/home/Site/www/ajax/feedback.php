<?php
    $first_name = htmlspecialchars($_POST['first_name']);
    $last_name = htmlspecialchars($_POST['last_name']);
    $group = htmlspecialchars($_POST['group']);
    $rop = htmlspecialchars($_POST['rop']);
    $telephone = htmlspecialchars($_POST['telephone']);
    $email = htmlspecialchars($_POST['email']);
    if (mail('test@mail.ru',$first_name,$last_name,$group))
        echo 'Сообщение отправлено';
    else
        echo 'Сообщение не отправлено';
?>