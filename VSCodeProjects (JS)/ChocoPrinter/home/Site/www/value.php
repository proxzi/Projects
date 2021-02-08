<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0"> <!-- для корректной работы на моб.устройствах -->
        <title>RP-Technology</title>
		<link rel="stylesheet" type="text/css" href="css/style.css">
        <link rel="stylesheet" href="css/bootstrap.css">
        <link rel="stylesheet" href="css/fontawesome.min.css">
        <link rel="stylesheet" href="css/main.css">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
        <link href="https://fonts.googleapis.com/css?family=IBM+Plex+Serif|Open+Sans" rel="stylesheet">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="http://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.6.3/css/font-awesome.min.css">
        <link rel="stylesheet" href="css/Footer-with-button-logo.css">
		<link rel="stylesheet" type="text/css" href="css/3DObjectViewer.css">
		<link rel="stylesheet" href="css/bootstrap-select.css">
		<link rel="stylesheet" href="css/bootstrap-select.min.css">
		<script src="js/jquery-1.8.2.js"></script>
		<script src="js/jquery-3.3.1.min.js"></script>
		<script src="js/3DObjectViewer.js"></script>
		<script src="js/load.js"></script>
		<script src="js/bootstrap-select.js"></script>
		<script src="js/defaults-eu.js"></script>
		<script src="js/bootstrap-select.min.js"></script>
		<script src="js/bootstrap-dropdown.js"></script>
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
                       <li class="active"><a href="value.php">Подать заявку</a></li>
                       <li><a href="zayvka.php">Статус заказа</a></li>
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
	   <div class="col-xl">
    <div class="row centered">
      <br><br>
      <div class="col-lg-6 col-sm-6" style="margin-top: 10%;">
        <h4>Просмотр модели</h4>
		<p><label> <input type="file" id="modelOBJ" class="btn btn-default" onChange="runViewer();" disabled></label></p>
			<div id="container1"></div>
						<div id="container2">
                </div>
                <br>
                <p>Добавить модель в открытую базу данных?<br>
                    <button type="submit" class="btn btn-info">Добавить</button>	<p>	
      </div>
      <div class="container">
      <div class="col-lg-6 col-sm-6">
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
                    if (first_name.length == false) fail = 'Введите имя';
                        // $('#first').toggleClass("has-error");
                    else if (last_name.length < 1) {
                        fail = 'Введите фамилию';
                    }
                    else if (telephone.length < 1){
                        fail = 'Введите телефон'
                    }
                    else if ((/^((8|\+7)[\- ]?)?(\(?\d{3}\)?[\- ]?)?[\d\- ]{7,10}$/i.test(telephone)) == false) {
                        fail = 'Вы ввели некорректный номер телефона';
                    }
                    else if (email.length < 1) {
                        fail = 'Введите email';
    
                    }
                    else if ((/^([a-z0-9_\.-])+@[a-z0-9-]+\.([a-z]{2,4}\.)?[a-z]{2,4}$/i.test(email)) == false) {
                        fail = 'Вы ввели некорректный email';
                    }
                    else if (group.length < 1) {
                        fail = 'Введите номер группы';
                    }
                    else if (($('input[name=options]:checked').val()) == undefined) fail = 'Выберите технологию печати';
                    else if (($('input[name=r]:checked').val()) == undefined) fail = 'Выберите материал';
                    else if (($('input[name=color]:checked').val()) == undefined) fail = 'Выберите цвет';

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
            <h3>Заявка на печать модели</h3>
        <h4>Информация о детале:</h3>
		<p>Размер: 26.0 x 58.1 x 10.0 мм<br>Номер модели: 11111</p>
        <form>
                        <fieldset class="form-group" id='first'>
                        <label for="first_name">* Имя</label>
                        <input type="text" placeholder='Имя' class="form-control" id="first_name" name="first_name">
                        </fieldset>
                        <fieldset class="form-group" id='last'>
                        <label for="last_name">* Фамилия</label>
                        <input type="text" placeholder='Фамилия' class="form-control" id="last_name" name="last_name">
                        </fieldset>
                        <label for="rop">Руководитель Образовательного Проекта</label>
                        <input type="text" placeholder='ФИО' class="form-control" id="rop" name="rop">
                        </fieldset>
                        <fieldset class="form-group" id='phone'>
                        <label for="telephone">* Телефон</label>
                        <input type="text" placeholder='+7 (___) ___ __ __' class="form-control" id="telephone" name="telephone">
                        </fieldset>
                        <fieldset class="form-group" id='email_l'>
                        <label for="email">* Email</label>
                        <input type="text" placeholder='example@mail.ru' class="form-control" id="email" name="email">
                        </fieldset>
                        <fieldset class="form-group" id='group-p'>
                        <label for="group">* Номер группы</label><br>
                        <input type="text" placeholder='Начните вводить номер группы' name="team" id="group" list="group_1" class="form-control" >
                        <datalist id="group_1" >
                        <option>161-343</option>
                        <option>162-333</option>
                        <option>160-222</option>
                        <option>125-123</option>
                        <option>161-343</option>
                        <option>162-333</option>
                        <option>160-222</option>
                        <option>125-123</option>
                        <option>45</option>
                        <option>162-333</option>
                        <option>160-222</option>
                        <option>125-123</option>
                        </datalist>
                        </fieldset>    
						<h3>Выберите технологию печати:</h3>
		<div class="btn-group" data-toggle="buttons">
  <label class="btn btn-warning">
    <input type="radio" name="options" id="option1" autocomplete="off"> 3d-печать
  </label>
  <label class="btn btn-warning">
    <input type="radio" name="options" id="option2" autocomplete="off"> Литьё
  </label>
</div>
<h3>Выберите материал:</h3>

  <div class="btn-group" data-toggle="buttons">
    <label class="btn btn-warning">
    <input type="radio"  name="r" id="absPlast"> ABS-пластик стандартный   
  </label>
  <label class="btn btn-warning">
    <input type="radio" name="r" id="absProm"> ABS-пластик промышленный
  </label>
  <label class="btn btn-warning">
  <input type="radio" name="r" id="Polyamid"> Полиамид
  </label>
</div>


  <h3>Выберите цвет:</h3>
  <div class="btn-group" data-toggle="buttons">
    <label class="btn btn-danger">
    <input type="radio" name="color" id="option2" autocomplete="off"> Красный
  </label>
  <label class="btn btn-success">
    <input type="radio" name="color" id="option1" autocomplete="off"> Зеленый
  </label>
  <label class="btn btn-primary">
  <input type="radio" name="color" id="option2" autocomplete="off"> Синий
  </label>
</div>
    <br>
    <br>
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
      </div>
    </div>



       <script src="https://code.jquery.com/jquery-1.10.2.min.js"></script>
       <script src="js/bootstrap.min.js"></script>

       <div id="0" style="height: 100px">
           <br>
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