+function () {
    document.querySelector('.gallery__div').classList.add('active');
    document.querySelector('.projects__menu-p').classList.add('active');

    function selectPanel(e) {
        var target = e.target.dataset.target;

        document.querySelectorAll('.projects__menu-p, .gallery__div').forEach(el => { el.classList.remove('active') });
        e.target.classList.add('active');
        document.querySelector('.' + target).classList.add('active');
        
    }
    
    document.querySelectorAll('.projects__menu-p').forEach(el => { el.addEventListener('click', selectPanel) });
    
}();


