"use strict";

const redBorder = "border: 1px solid red";
const greenBorder = "border: 1px solid green";

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

function resetStyle() {
    document.getElementById("name").style = "";
    document.getElementById("date").style = "";
    document.getElementById("email").style = "";
}

function send() {
    resetStyle();
    const wrong = [];
    let nameInput = document.getElementById("name");
    let dateInput = document.getElementById("date");
    let emailInput = document.getElementById("email");
    if(!verifyName(nameInput.value)) {
       wrong.push("name");
       nameInput.style = redBorder;
    }
    if(!verifyDate(dateInput.value)) {
       wrong.push("date");
       dateInput.style = redBorder;
    }
    if(!verifyEmail(emailInput.value)) {
        wrong.push("email");
        emailInput.style = redBorder;
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
}