for (var i = 0; i < 9; i++){
    document.getElementById('game').innerHTML+=`<div class="block"></div>`
}  //создаем 9 блоков для поля игры, creating 9 block for gaming field

var hod = 0;
var allblock = document.getElementsByClassName('block');
    function XHoriz() { 
        if (allblock[0].innerHTML == "x" && allblock[1].innerHTML == "x" && allblock[2].innerHTML == "x") { alert('Crosses are winned!') };
        if (allblock[3].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[5].innerHTML == "x") { alert('Crosses are winned!') };
        if (allblock[6].innerHTML == "x" && allblock[7].innerHTML == "x" && allblock[8].innerHTML == "x") { alert('Crosses are winned!') };
    }
        
    function XVert() {
        if (allblock[0].innerHTML == "x" && allblock[3].innerHTML == "x" && allblock[6].innerHTML == "x") { alert('Crosses are winned!') };
        if (allblock[1].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[7].innerHTML == "x") { alert('Crosses are winned!') };
        if (allblock[2].innerHTML == "x" && allblock[5].innerHTML == "x" && allblock[8].innerHTML == "x") { alert('Crosses are winned!') };
}

    function XDiag() {
            if (allblock[0].innerHTML == "x" && allblock[3].innerHTML == "x" && allblock[6].innerHTML == "x") { alert('Crosses are winned!') };
            if (allblock[1].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[7].innerHTML == "x") { alert('Crosses are winned!') };
            if (allblock[2].innerHTML == "x" && allblock[5].innerHTML == "x" && allblock[8].innerHTML == "x") { alert('Crosses are winned!') };
    }

function checkWinnerX(){
    XHoriz();
    XVert();
    XDiag();
}


document.getElementById('game').onclick = function (event) { 
    console.log(event);
    if (event.target.className == 'block') {
        if (hod % 2 == 0) { event.target.innerHTML = 'x';}
        else { event.target.innerHTML = '0'; };
        hod++; // если клетки четные, добавляем Х; иначе Y; проверяем ход 
        checkWinnerX();
    }

    
    
} //событие клик для записи значка в клетку
