
for (var i = 0; i < 9; i++){
    document.getElementById('game').innerHTML+=`<div class="block"></div>`
}  //создаем 9 блоков для поля игры, creating 9 block for gaming field

var move = 0;
var cll = document.getElementsByClassName('block');

var mass = [
    [cll[0], cll[1], cll[2]],
    [cll[3], cll[4], cll[5]],
    [cll[6], cll[7], cll[8]],
    [cll[0], cll[3], cll[6]],
    [cll[1], cll[4], cll[7]],
    [cll[2], cll[5], cll[8]],
    [cll[0], cll[4], cll[8]],
    [cll[2], cll[4], cll[6]],
]

function checkWinner(){
    for (i = 0; i < mass.length; i++){
        if (mass[i][0].innerHTML == mass[i][1].innerHTML && mass[i][1].innerHTML == mass[i][2].innerHTML && mass[i][0].innerHTML == '0') {
            alert("Zeros are winners!");
        }

        else if (mass[i][0].innerHTML==mass[i][1].innerHTML&&mass[i][1].innerHTML==mass[i][2].innerHTML&&mass[i][0].innerHTML=='x'){
            alert("Crosses are winners!");
        }
    }
}

function Marking() {
    if (event.target.className == 'block') {
        if (move % 2 == 0) { event.target.innerHTML = 'x';}
        else { event.target.innerHTML = '0'; };
        move++;
    }
}


document.getElementById('game').onclick = function (event) { 
    Marking();
    checkWinner(); 
}

document.getElementById('button').onclick = function (event) { 
    location.reload();
}



// else if(mass[i][0].innerHTML==mass[i][1].innerHTML&&mass[i][1].innerHTML==mass[i][2].innerHTML&&mass[i][0].innerHTML!=' '){
        //     alert('Draw!');}



      
// function XHoriz() { 
//     if (allblock[0].innerHTML == "x" && allblock[1].innerHTML == "x" && allblock[2].innerHTML == "x") { alert('Crosses are winned!') };
//     if (allblock[3].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[5].innerHTML == "x") { alert('Crosses are winned!') };
//     if (allblock[6].innerHTML == "x" && allblock[7].innerHTML == "x" && allblock[8].innerHTML == "x") { alert('Crosses are winned!') };
// }
        
// function XVert() {
//     if (allblock[0].innerHTML == "x" && allblock[3].innerHTML == "x" && allblock[6].innerHTML == "x") { alert('Crosses are winned!') };
//     if (allblock[1].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[7].innerHTML == "x") { alert('Crosses are winned!') };
//     if (allblock[2].innerHTML == "x" && allblock[5].innerHTML == "x" && allblock[8].innerHTML == "x") { alert('Crosses are winned!') };
// }

// function XDiag() {
//     if (allblock[0].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[8].innerHTML == "x") { alert('Crosses are winned!') };
//     if (allblock[2].innerHTML == "x" && allblock[4].innerHTML == "x" && allblock[6].innerHTML == "x") { alert('Crosses are winned!') };
// }    
// function OHoriz() { 
//     if (allblock[0].innerHTML == "0" && allblock[1].innerHTML == "0" && allblock[2].innerHTML == "0") { alert('Zeros are winned!') };
//     if (allblock[3].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[5].innerHTML == "0") { alert('Zeros are winned!') };
//     if (allblock[6].innerHTML == "0" && allblock[7].innerHTML == "0" && allblock[8].innerHTML == "0") { alert('Zeros are winned!') };
// }
        
// function OVert() {
//     if (allblock[0].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[8].innerHTML == "0") { alert('Zeros are winned!') };
//     if (allblock[2].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[6].innerHTML == "0") { alert('Zeros are winned!') };
//     if (allblock[2].innerHTML == "0" && allblock[5].innerHTML == "0" && allblock[8].innerHTML == "0") { alert('Zeros are winned!') };
// }

// function ODiag() {
//     if (allblock[0].innerHTML == "0" && allblock[3].innerHTML == "0" && allblock[6].innerHTML == "0") { alert('Zeros are winned!') };
//     if (allblock[1].innerHTML == "0" && allblock[4].innerHTML == "0" && allblock[7].innerHTML == "0") { alert('Zeros are winned!') };
    
// }

// function checkWinnerX(){
//     XHoriz();
//     XVert();
//     XDiag();
// }

// function checkWinnerO(){
//     OHoriz();
//     OVert();
//     ODiag();
// }

// function checkWinner() {
//     checkWinnerX();
//     checkWinnerO();
// }


