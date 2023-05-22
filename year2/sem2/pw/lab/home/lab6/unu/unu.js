$(function() {
    $("#departures").load("http://localhost/lab6/unu/get_departures.php")
    .change(function() {
        $("#arrivals").load("http://localhost/lab6/unu/get_arrivals.php?departure=" + $("#departures").val());
    });
    $("#arrivals").load("http://localhost/lab6/unu/get_arrivals.php?departure=" + $("#departures").val());
})