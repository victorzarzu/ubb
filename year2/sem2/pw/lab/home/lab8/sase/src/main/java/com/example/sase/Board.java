package com.example.sase;

import java.util.Arrays;

public class Board {
    private char[][] cells;
    private char currentPlayer;

    public Board() {
        cells = new char[3][3];
        for (char[] row : cells) {
            Arrays.fill(row, '-');
        }
        currentPlayer = 'X';
    }

    public boolean isValidMove(String cellId) {
        int row = (cellId.charAt(0) - '0') - 1;
        int col = (cellId.charAt(1) - '0') - 1;
        return row >= 0 && row < 3 && col >= 0 && col < 3 && cells[row][col] == '-';
    }

    public void makeMove(String cellId) {
        int row = (cellId.charAt(0) - '0') - 1;
        int col = (cellId.charAt(1) - '0') - 1;
        cells[row][col] = currentPlayer;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    public char[][] getCells() {
        return cells;
    }
}

