var nume = "";
var prenume = "";
var telefon = "";
var email = "";
var notInit = true;

function isChanged() {
    if(notInit) {
        return false;
    }
    return $("#nume").val() != nume || $("#prenume").val() != prenume || $("#telefon").val() != telefon || $("#email").val() != email;
}

function updateReset() {
    if(isChanged()) {
        $("#saveButton").prop("disabled", false);
    } else {
        $("#saveButton").prop("disabled", true);
    }
}

function saveData() {
    $.post("http://localhost/lab6/trei/get_person.php", {
        type: "save",
        id: $("#idselect").val(),
        nume: $("#nume").val(),
        prenume: $("#prenume").val(),
        telefon: $("#telefon").val(),
        email: $("#email").val()
    }, function() {
        $("#saveButton").prop("disabled", true) ;
        nume = $("#nume").val();
        prenume = $("#prenume").val();
        telefon = $("#telefon").val();
        email = $("#email").val();
    });
}

$(function () {
    $("#idselect").load("http://localhost/lab6/trei/get_person.php?type=id");

    $("#idselect").change(function() {
        if(isChanged()) {
            if(confirm("Doresti salvarea datelor modificate?")) {
                saveData();
            } else {

            }
        }

        xttp = new XMLHttpRequest();

        xttp.onreadystatechange = function()  {
        if(xttp.readyState == 4 && xttp.status == 200) {
                result = JSON.parse(xttp.responseText);
                nume = result.Nume; prenume = result.Prenume; telefon = result.Telefon; email = result.Email;
                $("#nume").val(result.Nume); $("#prenume").val(result.Prenume); $("#telefon").val(result.Telefon); $("#email").val(result.Email);
                $("#saveButton").prop("disabled", true);
                notInit = false;
            }
        }

        xttp.open("GET", "http://localhost/lab6/trei/get_person.php?type=person&id=" + $(this).val());
        xttp.send();
    });

    $("#nume").on("input", function() {
        updateReset()
    });
    $("#prenume").on("input", function() {
        updateReset()
    });
    $("#telefon").on("input", function() {
        updateReset()
    });
    $("#email").on("input", function() {
        updateReset()
    });

    $("#saveButton").click(function() {
        saveData();
    });
});
