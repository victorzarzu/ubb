<?php
    $game = str_split($_GET['game']);

    $isStarted = false;
    for($i = 0; $i < 9; $i++) {
        if($game[$i] != '-') {
            $isStarted = true;
            break;
        }
    }

    if($isStarted) {
        $finished = true;
        for($i = 0; $i < 9; $i++) {
            if($game[$i] == '-') {
                $finished = false;
                break;
            }
        }

        if(!$finished) {
            $position = rand(0, 8);
            while($game[$position] != '-') {
                $position = rand(0, 8);
            }
            $game[$position] = '0';
        }

        for($i = 0;$i < 3;$i++) {
            if($game[$i * 3 + 0] == $game[$i * 3 + 1] && $game[$i * 3 + 1] == $game[$i * 3 + 2] && $game[$i * 3] != '-') {
                echo $game[$i * 3 + $j] . "win!";
                exit();
            }
        }
        for($i = 0;$i < 3;$i++) {
            if($game[$i] == $game[$i + 3] && $game[$i + 3] == $game[$i + 6] && $game[$i] != '-') {
                echo $game[$i * 3 + $j] . "win!";
                exit();
            }
        }
        if($game[0] == $game[4] && $game[4] == $game[8] && $game[0] != '-') {
            echo $game[$i * 3 + $j] . "win!";
            exit();
        }
        if($game[2] == $game[4] && $game[4] == $game[6] && $game[2] != '-') {
            echo $game[$i * 3 + $j] . "win!";
            exit();
        }

        if($finished) {
            echo "remiza";
            exit();
        }

        echo implode("", $game);
    } else {
        $who = rand(0, 1);

        if($who == 0) {
            echo implode("", $game);
        } else {
            $position = rand(0, 8);
            $game[$position] = '0';
            echo implode("", $game);
        }
    }
?>
