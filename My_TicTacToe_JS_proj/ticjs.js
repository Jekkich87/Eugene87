for (var i = 0; i < 9; i++){
    document.getElementById('game').innerHTML+=`<div class="block"></div>`
}  //создаем 9 блоков для поля игры, creating 9 block for gaming field

var move = 0;
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
    if (allblock[0].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[8].innerHTML == "x") { alert('Crosses are winned!') };
    if (allblock[2].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[6].innerHTML == "x") { alert('Crosses are winned!') };
}    
function OHoriz() { 
    if (allblock[0].innerHTML == "0" && allblock[1].innerHTML == "0" && allblock[2].innerHTML == "0") { alert('Zeros are winned!') };
    if (allblock[3].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[5].innerHTML == "0") { alert('Zeros are winned!') };
    if (allblock[6].innerHTML == "0" && allblock[7].innerHTML == "0" && allblock[8].innerHTML == "0") { alert('Zeros are winned!') };
}
        
function OVert() {
    if (allblock[0].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[8].innerHTML == "0") { alert('Zeros are winned!') };
    if (allblock[2].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[6].innerHTML == "0") { alert('Zeros are winned!') };
}

function ODiag() {
    if (allblock[0].innerHTML == "0" && allblock[3].innerHTML == "0" && allblock[6].innerHTML == "0") { alert('Zeros are winned!') };
    if (allblock[1].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[7].innerHTML == "0") { alert('Zeros are winned!') };
    if (allblock[2].innerHTML == "0" && allblock[5].innerHTML == "0" && allblock[8].innerHTML == "0") { alert('Zeros are winned!') };
}

function checkWinnerX(){
    XHoriz();
    XVert();
    XDiag();
}

function checkWinnerO(){
    OHoriz();
    OVert();
    ODiag();
}

function checkWinner() {
    checkWinnerX();
    checkWinnerO();
}

function Marking() {
    if (event.target.className == 'block') {
        if (hod % 2 == 0) { event.target.innerHTML = 'x';}
        else { event.target.innerHTML = '0'; };
        move++;
    }
}


document.getElementById('game').onclick = function (event) { 
    Marking();
    checkWinner(); 
}
