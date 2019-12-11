for (var i = 0; i < 9; i++){
    document.getElementById('game').innerHTML+=`<div class="block"></div>`
}  //создаем 9 блоков для поля игры, creating 9 block for gaming field

var hod = 0;

document.getElementById('game').onclick = function (event) { 
    console.log(event);
    if (event.target.className == 'block') {
        if (hod % 2 == 0) { event.target.innerHTML = 'X';}
        else { event.target.innerHTML = '0'; };
        hod++;
    }

    
} //событие клик для записи значка в клетку
