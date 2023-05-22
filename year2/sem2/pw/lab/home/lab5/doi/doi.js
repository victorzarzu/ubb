"use strict";

const redBorder = "1px solid red";
const greyBorder = "1px solid grey";

function verifyName(name) {
    if(name.length == 0) {
        return false;
    }
    if(name[0] < 'A' || name[0] > 'Z') {
        return false;
    }
    for(let char of name.slice(1)) {
        if (char < 'a' || char > 'z') {
            return false;
        }
    }
    return true;
}

function verifyDate(date) {
    if(date.length == 0) {
        return false;
    }
    let d = new Date(date);
    if (d == "Invalid Date") {
        return false;
    }
    if(d > new Date()) {
        return false;
    }
    return true;
}

function verifyEmail(email) {
    if(email.length == 0) {
        return false;
    }
    let a = email.indexOf("@");
    if(a <= 0) {
        return false;
    }
    let p = email.indexOf(".", a + 2);
    if(p > -1 && p < email.length - 1) {
        return true;
    }
    return false;
}

function setAge() {
    let date = document.getElementById("date").value;
    if(verifyDate(date)) {
        let ms_dif = new Date() - new Date(date);
        let age_diff = new Date(ms_dif)

        document.getElementById("age").value = Math.abs(age_diff.getFullYear() - 1970);
    }
}

$(() => {
    $("#date").on("input", function() {
        let date = $("#date").val()
        if(verifyDate(date)) {
            let ms_dif = new Date() - new Date(date);
            let age_diff = new Date(ms_dif)
            
            console.log(age_diff)
            
            $("#age").val(Math.abs(age_diff.getFullYear() - 1970))
        }
    });
    $("#date").datepicker({changeYear: true, dateFormat: 'dd/mm/yyyy', firstDay: 1, dayNamesMin: ['D', 'L', 'Ma', 'Mi', 'J', 'V', 'S'], dayNames: ['Duminica', 'Luni', 'Marti', 'Miercuri', 'Joi', 'Vineri', 'Sambata'], monthNames: ['Ianurie', 'Februarie', 'Martie', 'Aprilie', 'Mai', 'Iunie', 'Iulie', 'August', 'Septembrie', 'Octobrie', 'Noiembrie', 'Decembrie'], changeMonth: true, monthNamesShort: ['Ian', 'Feb', 'Mar', 'Apr', 'Mai', 'Iun', 'Iul', 'Aug', 'Sep', 'Oct', 'Noi', 'Dec'], defaultDate: new Date(), maxDate: new Date()});

    $("#submit").click(function() {
        const wrong = [];
        if(!verifyName($("#name").val())) {
            wrong.push("name");
            $("#name").css("border", redBorder);
        } 
        else {
            $("#name").css("border", greyBorder);
        }

        if($("#email").get(0).checkValidity() == false) {
            wrong.push("email");
            $("#email").css("border", redBorder);
        } else {
            $("#email").css("border", greyBorder);
        }


        if(wrong.length > 0) {
            let message = "Invalid ";
            let len = wrong.length;
            for(let i = 0;i < len;i++) {
                message += wrong[i];
                if(i < len - 1) {
                    message += ", ";
                } else {
                    message += "!";
                }
            }

            alert(message);
        }
    });
});