window.onload = function() {

    let Clock = document.createElement('div');
    Clock.style.fontSize = "300px";
    Clock.style.fontWeight = "bold";
    Clock.style.paddingTop = "100px";
    Clock.style.borderRadius = "99px";
    Clock.style.color = "white";
    Clock.style.backgroundColor = "black";
    Clock.style.textAlign = "center";
    document.body.appendChild(Clock);
    function MyClock() {
        let data = new Date();
        Clock.innerHTML = data.getHours() + ':' + data.getMinutes() + ':' + (data.getSeconds() < 10 ? '0' + data.getSeconds() : data.getSeconds());
    }
    setInterval(MyClock, 1000);
  

    






}
