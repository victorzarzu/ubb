Array.prototype.shuffle = function () {
    this.sort((x, y) => {
        return Math.random() * 2 - 1;
    });
}

const game = {
    type: "number",
    size: 2,
    images: ['images/Czibula-Istvan.jpg', 'images/Boian-Rares-133x100.jpg',
        'images/Darabant-Sergiu.jpg', 'images/Suciu-Mihai.jpg',
        'images/Bufnea-Darius.jpg', 'images/Suciu-Dan.jpg',
        'images/Vancea-Alexandru.jpg', 'images/Czibula-Gabriela.jpg'],
    set gameSize(value) {
        this.size = value;
        this.updateGame();
        this.updateGameView();
    },
    updateGame: function () {
        this.values = [];
        this.toGuess = this.size ** 2;
        for (let i = 1; i <= this.toGuess / 2; i++) {
            if (this.type == "number") {
                this.values.push(i);
                this.values.push(i);
            } else {
                this.values.push(this.images[i - 1]);
                this.values.push(this.images[i - 1]);
            }
        }
        this.values.shuffle();
    },
    updateGameView: function () {
        view = $("#gameDiv");
        view.empty();

        let valuesIndex = 0;
        for (let row = 0; row < this.size; row++) {
            view.append(`<div id="${row}row" style="display:flex;flex-direction:row"></div>`)

            for (let column = 0; column < this.size; column++) {
                $(`#${row}row`).append(`<button name="${this.values[valuesIndex]}" style="height: 100px;width: 100px; margin: 1px; vertical-align:middle;"></button>`)

                valuesIndex++;
            }
        }

        if(this.type == "image") {
            $("button").css({
                "background-repeat": "no-repeat",
                "background-size": "cover",
                "background-position": "center"
            });
        }
    },
}

function updateGame() {
    select = $("#select");
    game.gameSize = select.val();
}

function setButton(button) {
    if(game.type == "number") {
        button.text(button.attr("name")).attr("disabled", true);
    } else {
        button.css("background-image", `url(${button.attr("name")})`).attr("disabled", true);
    }
}

function unsetButton(button) {
    if(game.type == "number") {
        button.text("");
    } else {
        button.css("background-image", "");
    }
}

$(function () {
    $("#select").on("change", updateGame).change();

    $("button").click(function() {
        const other = $("button").filter(function() {
            if(game.type == "number") {
                return $(this).text() != "" && $(this).attr("name") != "done";
            } else {
                return $(this).css("background-image") !== "none" && $(this).attr("name") != "done";
            }
        });
        setButton(other);
        setButton($(this));

        if(other.length == 1) {
            if(other.attr("name") != $(this).attr("name")) {
                $("button").attr("disabled", true);
                
                setTimeout(() => {
                    unsetButton(other);
                    unsetButton($(this));
                    $("button").filter(function() {
                        if(game.type == "number") {
                            return $(this).text() == "";
                        } else {
                            return $(this).css("background-image") == "none";
                        }
                    }).attr("disabled", false);
                }, 1000);
            } else {
                other.attr("name", "done");
                $(this).attr("name", "done");
            }
        }

        if($("button").filter(function() {return $(this).attr("name") != "done";}).length == 0) {
            alert("Game won!");
            updateGame();
        } 
    });
});