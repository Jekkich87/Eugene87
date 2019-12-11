for (var i = 0; i < 9; i++){
    document.getElementById('game').innerHTML+=`<div class="block"></div>`
}  //создаем 9 блоков для поля игры, creating 9 block for gaming field

var hod = 0;

document.getElementById('game').onclick = function (event) { 
    console.log(event);
    
    
} //событие клик для записи значка в клетку
