"use strict";
const l = new Set(["Unu", "Doi", "Trei", "Patru"]);
const r = new Set(["Cinci", "Sase", "Sapte", "Opt", "Noua"]);

$(() => {

    selectr = $("#selectr");
    selectl = $("#selectl");

    for(let val of l) {
        selectl.append(`<option id="${val}" value=$"${val}">${val}</option>`)
    }
    for(let val of r) {
        selectr.append(`<option id="${val}" value=$"${val}">${val}</option>`)
    }

    $("option").dblclick(function() {
        let id = $(this).attr("id");
        console.log(id)
        let parent = $(this).parent();
        parent.remove(`#${id}`);

        if (parent.is(selectl)) {
            selectr.append(this);
        } else {
            selectl.append(this);
        }
    });
})