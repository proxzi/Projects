var canvas = document.getElementById("myCanvas");
var ctx = canvas.getContext('2d');


var fish = new Image();
fish.src = 'рыба.png';
var backfish = new Image();
backfish.src = 'рыбабэк.png';
var petyx = new Image();
petyx.src = 'petyx.png';
var petyxtwo = new Image();
petyxtwo.src = 'petyx2.png';
var bg = new Image();
bg.src = 'bg.jpg';
var bubble = new Image();
bubble.src = 'пузырь.png';
var bubbletwo = new Image();
bubbletwo.src = 'пузырь2.png';
var zoloto = new Image();
zoloto.src = 'золотая.png';
var zolotoback = new Image();
zolotoback.src = 'золотаябэк.png';

var xPos = 0;
var yPos = canvas.height/2 - 100;
var score = 10;
var arr = [fish,petyx,zoloto,backfish,petyxtwo,zolotoback];
var c = 0;
var X = 0;
var Y = 0;
var k = false;

function getRandom(min, max){
    return Math.floor(Math.random() * (max - min + 1)) + min;
  }

var Bubble = function (){
    this.size = getRandom(30,80);
    this.x = getRandom(0,canvas.width - this.size);
    this.y = canvas.height;
    this.xSpeed = 0;
    this.ySpeed = -(getRandom(3,8));
    s = getRandom(0,1);
    if (s == 0) this.png = bubble;
    else this.png = bubbletwo;
}
Bubble.prototype.draw = function(){
    ctx.drawImage(this.png,this.x,this.y,this.size,this.size);
}

Bubble.prototype.move = function(){
    this.x += this.xSpeed;
    this.y += this.ySpeed;
}

Bubble.prototype.check = function(){
    if (this.y < -(this.size)) {
        this.y = canvas.height;
        this.x = getRandom(0,canvas.width - this.size);
        s = getRandom(0,1);
        if (s == 0) this.png = bubble;
        else this.png = bubbletwo;
    }
}
function position(){
    n = getRandom(0,1);
    if (n == 0) return -sizeforpos;
    else return canvas.width;
}
var Fisher = function () {
    this.size = getRandom(100,200);
    sizeforpos = this.size;
    this.x = position();

    if(this.x == -this.size) number = getRandom(0,2);
    else number = getRandom(3,5);
    this.riba = arr[number];

    this.y = getRandom(0,canvas.height - this.size);
    this.xSpeed = getRandom(3,11);
    this.ySpeed = 0;
    
};

Fisher.prototype.draw = function(){
    ctx.drawImage(this.riba,this.x,this.y,this.size,this.size);
} 

Fisher.prototype.move = function(){
    this.x += this.xSpeed;
    this.y += this.ySpeed;
}

Fisher.prototype.check = function () {
    if (this.x > width) {
        this.xSpeed = -this.xSpeed;
        this.riba = arr[getRandom(3,5)];
    }
    else if (this.x < -this.size){
        this.xSpeed = -this.xSpeed;
        this.riba = arr[getRandom(0,2)];
    }
    if (this.x == width || this.x == -this.size) {
        this.size = getRandom(100,200);
        sizeforpos = this.size;
        this.x = position();
        this.xSpeed = getRandom(3,11);
        this.y = getRandom(0,canvas.height - this.size);
        if(this.x == -this.size) {
            number = getRandom(0,2);
            this.riba = arr[number];
        }
        else if (this.x == canvas.width){
            number = getRandom(3,5);
            this.xSpeed = -this.xSpeed;
            this.riba = arr[number];
        }
    }
}      

function MouseClick (e){
    X = e.pageX - e.target.offsetLeft;
    Y = e.pageY;
    // document.getElementById('mouseX').innerHTML = 'X = ' + X + ', SIZE = ' + SIZE + ', Y = ' + Y;
    // document.getElementById('mouseY').innerHTML = 'x = ' + x + ', y = ' + y;
    // if (x >=Fish[i].x && x<=Fish[i].x + Fish[i].size && y>= Fish[i].y && y <= Fish[i].y + Fish[i].size){
    //     document.getElementById('mouseY').innerHTML = 'x = ' + x + ', y = ' + y;
    //     score += 1;
    //     document.getElementById('score').innerHTML = 'SCORE: ' + score;
    // }
    // else {
    //     score -=1;
    //     if (score < 0){
    //         document.getElementById('score').innerHTML = 'SCORE: Вы проиграли';
    //         return false;
    //     }
    //     document.getElementById('score').innerHTML = 'SCORE: ' + score;
    // }
    k = true;
}

function drawbg(){
    ctx.drawImage(bg,0,0);
}


var Bubbles = [];
for(var i = 0; i < 10; i++){
    Bubbles[i] = new Bubble(); 
}


var Fish = [];        
for(var i = 0; i < 10; i++){
            Fish[i] = new Fisher(); 
}

var width = canvas.width;
var height = canvas.height;
var s = 0;


function MouseClick (e){
    X = e.pageX - e.target.offsetLeft;
    Y = e.pageY;
    k = true;
}
canvas.addEventListener('click',MouseClick);


function ClickButton(){
    score = 10;
    document.getElementById('score').innerHTML = '<p>ОСТАЛОСЬ<br> ПОПЫТОК: ' + score + '</p>';
    var timerId = setInterval(function () {
        ctx.clearRect(0, 0, width, height);
        ctx.drawImage(bg,0,0);
        for(let i = 0; i < 10; i++){
    
            if (X >=Fish[i].x && X<=Fish[i].x + Fish[i].size && Y>= Fish[i].y && Y <= Fish[i].y + Fish[i].size){
                s += 1;
                k = false;
                X = 0;
                Y = 0;
                s = getRandom(0,1);
                if (s == 0) m = -Fish[i].size;
                else m = canvas.width;
                Fish[i].x = m;
            }
            Fish[i].draw();
            Fish[i].move();
            Fish[i].check();
        } 
        if(k == true){
            score -= 1;
            document.getElementById('score').innerHTML = '<p>ОСТАЛОСЬ<br> ПОПЫТОК: ' + score + '</p>';
            k = false;
        }
    
        if(score == -1 ){
            document.getElementById('score').innerHTML = 'ВЫ ПРОИГРАЛИ';
            clearInterval(timerId);
        }
    
        X = 0;
        Y = 0;
        for(let i = 0; i < 10; i++){   
                Bubbles[i].draw();
                Bubbles[i].move();
                Bubbles[i].check();
        }
        ctx.strokeRect(0, 0, width, height);
    
    }, 30);

}

//setTimoute(fishdraw,10);
//setInterval(fishdraw, 1000);


//canvas.addEventListener('click',MouseClick);
//setInterval(draw, 15);
//setInterval(drawone, 10);