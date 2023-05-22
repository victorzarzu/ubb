var root = "lab6";

function get_files(node) {
}

function update_anchors() {
    $("a").click(function() {
        var id = $(this).attr("id");
        $.get(id, function(data) {
            $("#file").text(data);
        });
    });
}    


function loadFiles(id) {
    $.get("http://localhost/lab6/cinci/get_files.php?file=" + id, function(data, status) {
        var $ul = $("<ul>").html(data);
        $("#" + id).append($ul);

        $ul.find("li").click(function(event) {
            event.stopPropagation();
          });

        $("#" + id).off("click");
        update_anchors();
    });
}

$(function() {
    $("#tree").load("http://localhost/lab6/cinci/get_files.php?file=lab6", function() {
        update_anchors();
    });
});