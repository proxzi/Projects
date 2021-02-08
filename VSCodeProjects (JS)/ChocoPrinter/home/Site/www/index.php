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
		<script src="js/jquery-3.3.1.min.js"></script>
		<script src="js/bootstrap-select.js"></script>
		<script src="js/defaults-eu.js"></script>
		<script src="js/bootstrap-select.min.js"></script>
		<script src="js/bootstrap-dropdown.js"></script>
		<script src="js/jquery-3.3.1.min.js"></script>
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
                       <li class="active"><a href="index.php">О портале</a></li>
                       <li><a href="value.php">Подать заявку</a></li>
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
					   <form action="value.php">
							<button class="btn btn-default"type="submit" id="ididid">Просмотреть модель и отправить заявку на 3D-печать</button>
						</form>
						<br> 
                   </div>
               </div>
           </div>
        </div>

        <div id="about">

                    <p>Данный портал предоставляет возможность заказать на изготовление предмет любой сложности из материалов на выбор с последующей обработкой
                    </p>


                    <h2> Как это работает? </h2>
                    <p>
                        1. Загрузите модель в формате STL, предварительно
                        подготовленную к 3D-печати.
                    </p>
					
					<p><img src="1.png"></p>
					
                    <p>
                        2. Укажите требуемые вам условия печати
					
                    <p><img src="2.png"></p>
                    
                    <p>
                        3. После нажатия кнопки "Заказать 3d-модель", нужно заполнить заявку с личными данными.
                    </p>
                    <p><img src="3.png"></p>
                    <p>
                        4. Статус производства можно отследить в онлайн-документе статусов заказов по своему имени.
                    </p>
                    <p>
                        5. При готовности детали, будет отправлено письмо на указанный e-mail с указаниями о получении выполненного заказа.
                    </p>
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