<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0"> <!-- для корректной работы на моб.устройствах -->
        <title>RP-Technology</title>
        <link rel="stylesheet" href="css/bootstrap.css">
        <link rel="stylesheet" href="css/fontawesome.min.css">
        <link rel="stylesheet" href="css/main.css">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
        <link href="https://fonts.googleapis.com/css?family=IBM+Plex+Serif|Open+Sans" rel="stylesheet">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="http://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.6.3/css/font-awesome.min.css">
        <link rel="stylesheet" href="css/Footer-with-button-logo.css">
    
    </head>
    <body>
       <div class = "navbar navbar-inverse navbar-fixed-top">
           <div class="container">
               <div class="navbar-header">
                   <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                       <span class="icon-bar"></span>
                       <span class="icon-bar"></span>
                       <span class="icon-bar"></span>
                    </button>
                    <img src="img/logo.png" alt="" class="img-responsive">
                    <a class="navbar-brand" href="#">RP - Techn<i class="fa fa-circle"></i>logy</a>
               </div>
               <div class="navbar-collapse collapse">
                   <ul class="nav navbar-nav navbar-right">
                       <li><a href="index.php">О портале</a></li>
                       <li><a href="value.php">Подать заявку</a></li>
                       <li class="active"><a href="zayvka.php">Статус заказа</a></li>
					   <li><a href="about.php">Наше оборудование</a></li>
                       <li><a data-toggle="modal" data-target="#myModal" href="#myModal"><i class="fa fa-envelope-o"></i></a></li>
                   </ul>
               </div>
           </div>
       </div>
       <div id="headerwrap">
           <div class="container">
               <div class="row centered">
                   <div class="col-lg-8 col-lg-offset-2">
                       <h1>Welcome</h1>
                       <h2>Printing Moscow Polytechnic University</h2>
                   </div>
               </div>
           </div>
       </div>
       <div class="container wb">
           <div class="row centered">
               <div class="col-lg-8 col-lg-offset-2">

                    <h4>Заявка на печать модели</h4>
                    <p></p>
                    <?php
                        //require_once 'functions/function.php';
                    ?>
                    <script src="//ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
                    <script>
                        $(document).ready(function (){
                            $('#done').click(function(){
                                var first_name = $("#first_name").val();
                                var last_name = $('#last_name').val();
                                var group = $('#group').val();
                                var rop = $('#rop').val();
                                var telephone = $('#telephone').val();
                                var email = $('#email').val();
                                var fail = '';
                                if (first_name.length < 1) fail = 'Введите имя';
                                else if (last_name.length < 1) fail = 'Введите фамилию';
                                else if (group.length < 1) fail = 'Введите номер группы';
                                else if (telephone.length < 1) fail = 'Введите телефон';
                                else if (email.length < 1) fail = 'Введите email';
                                else if (email.split ('@').length - 1 == 0 || email.split('.').length - 1 == 0)
                                    fail = 'Вы ввели некорректный email';
                                if (fail != ''){
                                    $('#messageShow').html (fail)
                                    $('messageShow').show ();
                                    return false;
                                }
                                fail = '';
                                $.ajax({
                                    url: '/functions/function.php',
                                    type: 'POST',
                                    data: {'first_name':first_name, 'last_name':last_name,
                                    'group':group,'rop':rop,'telephone':telephone, 'email': email},
                                    dataType: 'html',
                                    success: function (data){
                                            $('#messageSho').html (data);
                                            $('#messageSho').show ();
                                    }                                    
                                });

                                $.ajax({
                                    url: '/ajax/feedback.php',
                                    type: 'POST',
                                    cache: false,
                                    data: {'first_name':first_name, 'last_name':last_name,
                                    'group':group,'telephone':telephone, 'email': email},
                                    dataType: 'html',
                                    success: function (data){
                                            
                                    }
                                });
                                                         
                            });
                        });
                    </script>
                <form>
                        <fieldset class="form-group">
                        <label for="first_name">* Имя</label>
                        <input type="text" placeholder='Имя' class="form-control" id="first_name" name="first_name">
                        </fieldset>
                        <fieldset class="form-group">
                        <label for="last_name">* Фамилия</label>
                        <input type="text" placeholder='Фамилия' class="form-control" id="last_name" name="last_name">
                        </fieldset>
                        <fieldset class="form-group">
                        <label for="group">* Номер группы</label>
                        <select class="custom-select" id="group" name="group">
                        <option value="1">One</option>
                        <option value="2">Two</option>
                        <option value="3">Three</option>
                        </select>
                        </fieldset>
                        <fieldset class="form-group">
                        <label for="rop">Руководитель Образовательного Проекта</label>
                        <input type="text" placeholder='ФИО' class="form-control" id="rop" name="rop">
                        </fieldset>
                        <fieldset class="form-group">
                        <label for="telephone">* Телефон</label>
                        <input type="text" placeholder='+7 (___) ___ __ __' class="form-control" id="telephone" name="telephone">
                        </fieldset>
                        <fieldset class="form-group">
                        <label for="email">* Email</label>
                        <input type="text" placeholder='example@mail.ru' class="form-control" id="email" name="email">
                        </fieldset>
                        <div id='messageShow' style = 'color: red'></div><br>     
                        
                        <div id='messageSho' style = 'color: green'></div>
                        <!-- <p>Если у вас есть 3D-модель (формат .STL), пожалуйста, прикрепите его к заявке. </p>
                        <p>Ограничение на размер файла 50 Мб.</p>
                        <p><label><input class="btn btn-default" type="file" id="file" /> </label></p> -->
                        <input type="button" name='done' id='done' class="btn btn-default" value='Отправить'>
                </form>                
            </div>
            </div>
        </div>
    </div>
    <script src="https://code.jquery.com/jquery-1.10.2.min.js"></script>
    <script src="js/bootstrap.min.js"></script>

    <div class="content">
    </div>
        <footer id="myFooter">
            <div class="container">
                <div class="row">
                    <div class="col-sm-3">
                        <h2 class="logo"><img src="img/logo.png" alt="" class="img-responsive"></h2>
                    </div>
                    <div class="col-sm-2">
                        <h5>Начало</h5>
                        <ul>
                            <li><a href="#">Главная страница</a></li>
                        </ul>
                    </div>
                    <div class="col-sm-2">
                        <h5>О нас</h5>
                        <ul>
                            <li><a href="#">Информация</a></li>
                            <li><a href="#">Контакты</a></li>
                        </ul>
                    </div>
                    <div class="col-sm-2">
                        <h5>Помощь</h5>
                        <ul>
                            <li><a href="#">FAQ</a></li>
                        </ul>
                    </div>
                    <div class="col-sm-3">
                        <div class="social-networks">
                            <a href="#" class="google"><i class="fa fa-google-plus"></i></a>
                        </div>
                    </div>
                </div>
            </div>
            <div class="footer-copyright">
                <p>© 2018 Copyright Text </p>
            </div>
        </footer>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
        <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>



    </body>
</html>