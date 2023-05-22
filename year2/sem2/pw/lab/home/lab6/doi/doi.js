var page = 0;
var noPages = 0;
var perPage = 3;

function get_number_of_pages() {
    xttp = new XMLHttpRequest();

    xttp.open("GET", "http://localhost/lab6/doi/get_persons.php?type=count", false);
    xttp.send('');

    return Math.floor(xttp.responseText / perPage);
}

function get_page(page, perPage) {
   $("#table").load("http://localhost/lab6/doi/get_persons.php?type=persons&page=" + page + "&perPage=" + perPage, function() {
        if($("#table tr").not(":first").length < perPage) {
            $("#nextButton").prop("disabled", true);
        }
   });
}

$(function() {
    get_page(page, perPage);

    $("#nextButton").click(function() {
        page += 1;  
        $("#prevButton").prop("disabled", false);
        get_page(page, perPage);
    });

    $("#prevButton").click(function() {
        page -= 1;
        $("#nextButton").prop("disabled", false);
        if(page == 0) {
            $(this).prop("disabled", true);
        }
        get_page(page, perPage);
    });
});