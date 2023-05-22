var game = "---------".split('');

function updateTable() {
    $.get("http://localhost/lab6/patru/game.php?game=" + game.join(''), function(data, status) {
        if(data.length < 9) {
            alert(data);
            game = "---------".split('');
            for(let i = 0;i < 9;i++) {
                $("#" + i).text("");
            }
            $("td").on('click', function() {
                game[this.id] = 'x';
                updateTable();

                $(this).off('click');
            });
        }
        else {
            game = data.split('');
            for(let i = 0;i < 9;i++) {
                if(game[i] != '-') {
                    $("#" + i).text(game[i])
                }
            }
        }
    });
}

$(function() {
    updateTable();
    $("table").css({
        "border": "1px solid black",
        "border-collapse": "collapse"
    })
    $("td").css({
        "border": "1px solid black",
        "height": "80px",
        "width": "80px",
        "text-align": "center"
    }).click(function() {
        game[this.id] = 'x';
        updateTable();

        $(this).off('click');
    });
})