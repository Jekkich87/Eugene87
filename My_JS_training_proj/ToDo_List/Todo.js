const listsContainer = document.querySelector("#data-lists");
const newListForm = document.querySelector('#data-new-list-form');
const newListInput = document.querySelector('#data-new-list-input');
const deleteListBtn = document.querySelector('#delete-list-btn');
const listDisplayContainer = document.querySelector('#datalist-display-container');
const listTitleElement = document.querySelector('#datalist-title');
const listCountElement = document.querySelector('#datalist-count');
const tasksContainer = document.querySelector('data-tasks');


const LOCAl_STORAGE_LIST_KEY = 'task.list'  //prevent overwriting local storage
const LOCAL_STORAGE_SELECTED_LIST_ID_KEY = 'task.selectedListId';

let lists = JSON.parse(localStorage.getItem(LOCAl_STORAGE_LIST_KEY))||[]; //getting info from local storage or, an empty aray, if info doesn`t exist
let selectedListId = localStorage.getItem(LOCAL_STORAGE_SELECTED_LIST_ID_KEY); //choosing list as 'active list'


function render() { 
    clearElement(listsContainer);
    renderLists();

    const selectedList = lists.find(list => list.id === selectedListId);
    if (selectedListId == null) {
        listDisplayContainer.style.display = 'none';  //don`t display tasks box, if no one list is selected
    }
    else {
        listDisplayContainer.style.display = '';
        listTitleElement.innerText = selectedList.name; //changing title of choosed list according to its title in 'todo lists' list;
     }
}

function renderLists() { //rendering list of 'todo'-lists
    lists.forEach(list => {
        const listElement = document.createElement('li');
        listElement.dataset.listId = list.id; //marking wich list id active
        listElement.classList.add('list-name');
        listElement.innerText = list.name;
        if (list.id === selectedListId) {
            listElement.classList.add('active-list') //adding class"active-list" to the choosen list
        }
        listsContainer.appendChild(listElement);
    })
}

function clearElement(element) {
    while (element.firstChild) {
        element.removeChild(element.firstChild);
    }
}

render();

newListForm.addEventListener('submit', e => { //posibility to create new 'todo'-lists
    e.preventDefault();
    const listName = newListInput.value;
    if (listName == null || listName === '') return;
    const list = createList(listName);
    newListInput.value = null;
    lists.push(list);
    saveAndRender(); 
})

function createList(name) { //creating new 'todo'-list
    return {
        id: Date.now().toString(), name: name, tasks: []
    }
}

function save() {  
    localStorage.setItem(LOCAl_STORAGE_LIST_KEY, JSON.stringify(lists));  //saving info in local storage
    localStorage.setItem(LOCAL_STORAGE_SELECTED_LIST_ID_KEY, selectedListId); //
    
}

function saveAndRender() { //rendering saved info from Local Storage
    save();
    render();
}

listsContainer.addEventListener('click', e => { //marking clicked list as active (selected) list
    if (e.target.tagName.toLowerCase() === 'li') {
        selectedListId = e.target.dataset.listId; //wich id is selecting
        saveAndRender();
    }
});

deleteListBtn.addEventListener('click', e => { //function to delete list
    lists = lists.filter(lists => lists.id != selectedListId);
    selectedListId = null;
    saveAndRender();
})