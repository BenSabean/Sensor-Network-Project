//menus.js
//Handles the dropdown menus that "drop down"
//(really "appear" and "disappear") from the
//main menu on each page of the website

//Flag to indicate if a dropdown menu is visible
var isShowing = false;

//Reference to the current dropdown menu
var dropdownMenu = null;

//Show the drop-down menu with the given id, if it exists, and set flag
function show(id)
{
    hide(); /* First hide any previously showing dropdown menu */
    dropdownMenu = document.getElementById(id);
    if (dropdownMenu != null)
    {
        dropdownMenu.style.visibility = 'visible';
        isShowing = true;
    }
}

//Hide the currently visible dropdown menu and set flag
function hide()
{       
    if (isShowing) dropdownMenu.style.visibility = 'hidden';
    isShowing = false;
}