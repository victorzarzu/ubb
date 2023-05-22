$(function() {
    $.get("http://localhost/lab6/sase/get_products.php?type=info", function(data) {
        let result = JSON.parse(data);

        producatorselect = $("#producatorselect");
        producatorselect.append(`<option value="%">Toti producatorii</option>`);
        for(let i = 0;i < result.producatori.length;i++) {
            producatorselect.append(`<option value="${result.producatori[i]}">${result.producatori[i]}</option>`);
        }
        procesorselect = $("#procesorselect");
        procesorselect.append(`<option value="%">Toate procesoarele</option>`);
        for(let i = 0;i < result.procesoare.length;i++) {
            procesorselect.append(`<option value="${result.procesoare[i]}">${result.procesoare[i]}</option>`);
        }
    });

    $("#filterButton").click(function() {
        $.post("http://localhost/lab6/sase/get_products.php", {
            type: "data",
            producator: $("#producatorselect").val(),
            procesor: $("#procesorselect").val(),
        }, function(data) {
            $("#table").html(data);
        });
    });
})