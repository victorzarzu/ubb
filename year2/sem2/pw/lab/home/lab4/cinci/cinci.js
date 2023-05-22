
slider = {
    prevButton: document.getElementById("prevButton"),
    nextButton: document.getElementById("nextButton"),
    maxImages: 5,
    currentImage: 1,
    items: document.getElementById("sliderList").getElementsByTagName("li"),
    setUp: function() {
        prevButton.disabled = true;
        this.items[this.currentImage - 1].style.left = `0`;
        this.auto = setTimeout(() => {
            slider.next();
        }, 5000);
    },
    next: function() {
        var prevImage = this.currentImage;
        if(this.currentImage == this.maxImages) { 
            this.currentImage = 1;
        } else {
            this.currentImage += 1;
            this.prevButton.disabled = false;
        }

        this.update(prevImage, "next");
    },
    prev: function() {
        var prevImage = this.currentImage;
        this.currentImage -= 1;
        this.nextButton.disabled = false;
        this.update(prevImage, "prev");
    },
    update: function(prevImage, type) {
        let initialStep = 400;
        let step = initialStep;
        if(type == "next") {
            for(let i = 0;i < this.items.length;++i) {
                if(i != this.currentImage - 1 && i != prevImage - 1) {
                    this.items[i].style.display = "none";
                    this.items[i].style.left = "1000px";
                    this.items[i].style.display = "block";
                    this.items[i].style.zIndex = -100 - i;
                } 
            }
            this.items[this.currentImage - 1].style.zIndex = 0;
            this.items[prevImage - 1].style.zIndex = -1;
            let t = setInterval(function() {
                slider.items[slider.currentImage - 1].style.left = `${step}px`;
                slider.items[prevImage - 1].style.left = `calc(${initialStep} - ${step})px`;
                step -= 2;
                if(step == -2) {
                    clearInterval(t);
                }
            }, 1);
        } else {
            for(let i = 0;i < this.items.length;++i) {
                if(i != this.currentImage - 1 && i != prevImage - 1) {
                    this.items[i].style.display = "none";
                    this.items[i].style.left = "-1000px";
                    this.items[i].style.display = "block";
                    this.items[i].style.zIndex = -100 - i;
                } 
            }
            this.items[this.currentImage - 1].style.zIndex = 0;
            this.items[prevImage - 1].style.zIndex = -1;
            let t = setInterval(function() {
                slider.items[slider.currentImage - 1].style.left = `-${step}px`;
                slider.items[prevImage - 1].style.left = `-calc(${initialStep} - ${step})px`;
                step -= 2;
                if(step == -2) {
                    clearInterval(t);
                }
            }, 1);

        }
        clearTimeout(this.auto);
        this.auto = setTimeout(() => {
            slider.next();
        }, 5000);
    }
}

function next() {
    slider.next();
}

function prev() {
    slider.prev();
}

slider.setUp();