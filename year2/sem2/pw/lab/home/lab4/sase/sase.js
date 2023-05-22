Array.prototype.shuffle = function() {
    this.sort((x, y) => {
        return Math.random() * 2 - 1;
    });
}

const game = {
    type: "image",
    size: 4,
    set gameSize(value) {
        this.size = value;
        this.updateGame();
        this.updateGameView();
    },
    emptyRow: 0,
    emptyColumn: 0,
    values: [],
    image: "robotboy.jpeg",
    updateGame: function() {
        this.values = [];
        for(let i = 0;i < this.size ** 2;i++) {
            this.values.push(i);
        }
        this.values.shuffle();
    },
    updateGameView: function() {
        let table = document.getElementById("gameTable");
        table.innerHTML = "";
        let valuesIndex = 0;
        for(let i = 0;i < this.size;i++) {
            let row = document.createElement("tr");
            for(let j = 0;j < this.size;j++) {
                let cell = document.createElement("td")
                cell.style = "width:40px;height:40px";
                cell.style.padding = "5px";
                if(this.values[valuesIndex] > 0) {
                    if(this.type == "number") {
                        cell.textContent = this.values[valuesIndex];
                    } else {
                        let val = this.values[valuesIndex];
                        let valRow = Math.floor(val / this.size);
                        let valColumn = val % this.size;
                        cell.style.background = `url(${this.image})` + `calc(${-40 * valRow}px)` + `calc(${-40 * valColumn}px)`;
                    }
                } else {
                    this.emptyRow = i;
                    this.emptyColumn = j;
                }

                row.appendChild(cell);
                valuesIndex++;
            }

            table.appendChild(row);
        }
    },
    moveUp: function() {
        if(this.emptyRow == 0) {
            return;
        }
        let index = (this.emptyRow - 1) * this.size + this.emptyColumn;
        if (index < 0 || index >= this.values.length) {
            return;
        }
    
        [this.values[index], this.values[this.emptyRow * this.size + this.emptyColumn]] = [this.values[this.emptyRow * this.size + this.emptyColumn], this.values[index]];
    
        this.emptyRow--;
        this.updateGameView();
    },
    moveDown: function() {
        if(this.emptyRow == this.size - 1) {
            return;
        }
        let index = (this.emptyRow + 1) * this.size + this.emptyColumn;
        if (index < 0 || index >= this.values.length) {
            return;
        }
    
        [this.values[index], this.values[this.emptyRow * this.size + this.emptyColumn]] = [this.values[this.emptyRow * this.size + this.emptyColumn], this.values[index]];
    
        this.emptyRow--;
        this.updateGameView();
    },
    moveLeft: function() {
        if(this.emptyColumn == 0) {
            return;
        }
        let index = this.emptyRow * this.size + this.emptyColumn - 1;
        if (index < 0 || index >= this.values.length) {
            return;
        }
    
        [this.values[index], this.values[this.emptyRow * this.size + this.emptyColumn]] = [this.values[this.emptyRow * this.size + this.emptyColumn], this.values[index]];
    
        this.emptyRow--;
        this.updateGameView();
    },
    moveRight: function() {
        if(this.emptyColumn == this.size - 1) {
            return;
        }
        let index = this.emptyRow * this.size + this.emptyColumn + 1;
        if (index < 0 || index >= this.values.length) {
            return;
        }
    
        [this.values[index], this.values[this.emptyRow * this.size + this.emptyColumn]] = [this.values[this.emptyRow * this.size + this.emptyColumn], this.values[index]];
    
        this.emptyRow--;
        this.updateGameView();
    },
    setupKeyListeners: function() {
        document.addEventListener("keydown", (event) => {
            switch(event.code) {
                case "ArrowUp":
                    this.moveUp();
                    break;           
                case "ArrowDown":
                    this.moveDown();
                    break;           
                case "ArrowLeft":
                    this.moveLeft();
                    break;           
                case "ArrowRight":
                    this.moveRight();
                    break;           
            }
        });
    },
    verifyGameSolved: function() {
        for(let i = 1;i < this.size ** 2 - 2;i++) {
            if(this.values[i] < this.values[i - 1]) {
                return;
            }
        }
        alert("Game solved!");
        this.gameSize = this.size;
    }
}

function selectionChanged() {
    let value = document.getElementById("select").value;
    game.gameSize = Number.parseInt(value);
}

selectionChanged();
game.setupKeyListeners();