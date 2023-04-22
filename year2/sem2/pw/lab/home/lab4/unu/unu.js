"use strict";
const l = new Set(["Unu", "Doi", "Trei", "Patru"]);
const r = new Set(["Cinci", "Sase", "Sapte", "Opt", "Noua"]);

function updateLists() {
    let content_l = "", content_r = "";
    for(let val of l) {
        content_l += `<option ondblclick="elementClicked(this.id)" id="${val}" value="${val}">${val}</option>`;
    }
    for(let val of r) {
        content_r += `<option ondblclick="elementClicked(this.id)" id="${val}" value="${val}">${val}</option>`;
    }

    document.getElementById("selectl").innerHTML = content_l;
    document.getElementById("selectr").innerHTML = content_r;
}

function elementClicked(value) {
    if(l.has(value)) {
        l.delete(value);
        r.add(value);
    } else {
        r.delete(value);
        l.add(value);
    }
    updateLists();
}

updateLists();