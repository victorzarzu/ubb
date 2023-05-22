Array.prototype.shuffle = function() {
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
    values: [1, 1, 2, 2],
    set gameSize(value) {
        this.size = value;
        this.updateGame();
        this.updateGameView();
    },
    prevClicked: undefined,
    toGuess: 4,
    disableButtons: function() {
        let buttons = document.getElementsByTagName("button");
        for(let i = 0;i < buttons.length;i++) {
          buttons[i].disabled = true;
        }
      },
      enableButtons: function() {
        let buttons = document.getElementsByTagName("button");
        for(let i = 0;i < buttons.length;i++) {
          if(buttons[i].textContent == "" && buttons[i].style.backgroundImage == "") {
            buttons[i].disabled = false;
          }
        }
      },
    updateGameView: function() {
        gameDiv = document.getElementById("gameDiv");
        gameDiv.innerHTML = "";

        let valuesIndex = 0;
        for(let row = 0;row < this.size;row++) {
            let rowDiv = document.createElement("div")
            rowDiv.style = "display:flex;flex-direction:row";
            for(let column = 0;column < this.size;column++) {
                let button = document.createElement("button");
                button.style = "height: 100px;width: 100px; margin: 1px; vertical-align:middle;";
                button.setAttribute("name", this.values[valuesIndex]);
                button.onclick = function() {game.cellClicked(button);};

                if(this.type == "image") {
                    button.style.backgroundRepeat = "no-repeat";
                    button.style.backgroundSize = "cover";
                    button.style.backgroundPosition = "center";
                }

                rowDiv.appendChild(button);
                valuesIndex++;
            }
            gameDiv.appendChild(rowDiv);
        }
    },
    updateGame: function() {
        this.values = [];
        this.toGuess = this.size ** 2;
        for(let i = 1;i <= this.toGuess / 2;i++) {
            if(this.type == "number") {
                this.values.push(i);
                this.values.push(i);
            } else {
                this.values.push(this.images[i - 1]);
                this.values.push(this.images[i - 1]);
            }
        }
        this.values.shuffle();

    },
    setButtonContent: function(button) {
        if(this.type == "number") {
            button.textContent = button.name;
        } else {
            button.style.backgroundImage = `url(${button.name})`;
        }
    },
    resetButtonContent: function(button) {
        if(this.type == "number") {
            button.textContent = "";
        } else {
            button.style.backgroundImage = "";
        }
    },
    cellClicked: async function (button) {
        if(this.prevClicked == undefined) {
            this.prevClicked = button;
            this.setButtonContent(this.prevClicked);
            button.disabled = true;
        } else {
            this.setButtonContent(button);
            this.disableButtons();
             
            if(this.prevClicked.name != button.name) {
                await new Promise((resolve) => {
                    setTimeout(() => {
                        this.resetButtonContent(button);
                        this.resetButtonContent(this.prevClicked);
                        button.setAttribute("disable", false);
                        this.prevClicked.setAttribute("disable", false);
                        this.prevClicked = undefined;
                        resolve();
                }, 1000);
                });
            } else {
                this.toGuess -= 2;
                button.setAttribute("disable", true);
                this.prevClicked.setAttribute("disable", true);
                this.prevClicked = undefined;
            }
            this.enableButtons();
        }
    
        if(this.toGuess == 0) {
            alert('Game won!');
            this.gameSize = this.size;
        }
    }
}

function selectionChanged() {
    let value = document.getElementById("select").value;
    game.gameSize = Number.parseInt(value);
}

selectionChanged();