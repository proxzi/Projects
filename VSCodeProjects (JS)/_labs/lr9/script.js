window.onload = () => {
    let spoiler = document.getElementsByClassName('cl');

    let hideshow = (idName,idHead) => {
        let content = document.getElementById(idName);
        let header = document.getElementById(idHead);
        if(content.style.display == 'block') {
            header.innerHTML = 'Показать';
            content.style.display = 'none';
        } else {
            header.innerHTML = 'Скрыть';
            content.style.display = 'block';
        }
    };
    for(let element of spoiler) {
        element.onclick = function() {
            hideshow('content','header'); 
        };
    }
}