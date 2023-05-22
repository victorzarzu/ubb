$(function() {
    currentImage = 1
    
    t = setInterval(function() {
        $("#nextButton").click();
    }, 3000);

    $("#prevButton").click(function() {
        current = $("li").filter(function() {
            return $(this).css("left") == '0px';
        });

        prev = current;
        if(current.prev().length == 0) {
            current = $("#last") 
        } else {
            current = current.prev()
        }
        current.css({
            "left": "-250px",
            "z-index": 1
        });
        prev.css("z-index", 0);
        current.animate({
            "left": 0,
        }, 750, function() {
            prev.css({
                "left": "-250px",
            });
        });

        clearInterval(t);
        t = setInterval(function() {
            $("#nextButton").click();
        }, 3000);
    });

    $("#nextButton").click(function() {
        current = $("li").filter(function() {
            return $(this).css("left") == '0px';
        });

        prev = current;
        if(current.next().length == 0) {
            current = $("#first") 
        } else {
            current = current.next()
        }
        current.css({
            "left": "250px",
            "z-index": 1
        });
        prev.css("z-index", 0);
        current.animate({
            "left": 0,
        }, 750, function() {
            prev.css({
                "left": "250px",
            });
        });

        clearInterval(t);
        t = setInterval(function() {
            $("#nextButton").click();
        }, 3000);
    });
});