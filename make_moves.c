// Copyright 2018 Nedelcu Horia (nedelcu.horia.alexandru@gmail.com)

#include "./functions_Poli_TicTacToe.h"

void initialize_matrix(int rows, int columns, int matrix[N_MAX][N_MAX]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = 0; // empty cell
        }
    }
}

void round_robin_algorithm(int n, int board[N_MAX][N_MAX],
    int* px, int* py) {
    // the function check for a empty cell if exist or
    // returns invalid x and y otherwise
    static int d0i = 0, ind_d = 1, dpi = 0, dmi = 0;
    int i, j;

    // d0i - start point of d(0) diagonal
    // ind_d - index for the current set of diagonals d(+j) and d(-j)
    // dpi - d(plus)i - start point of d(+j) diagonal
    // dmi - d(minus)i - start point of d(-j) diagonal

    *px = -1; // pointer for x row
    *py = -1; // pointer for y column

    // check d(0) diagonal:
    for (i = d0i; i < n * n; ++i, ++d0i) {
        if (board[i][i] == 0) {
            *px = i;
            *py = i;
            return;
        }
    }

    for (j = ind_d; j < n * n; ++j, ind_d++) {
        // check d(+j) diagonal:
        for (i = dpi; i + j < n * n; ++i, dpi++) {
            if (board[i][i + j] == 0) {
                *px = i;
                *py = i + j;
                return;
            }
        }

        // check d(-j) diagonal:
        for (i = j + dmi; i < n * n; ++i, dmi++) {
            if (board[i][i - j] == 0) {
                *px = i;
                *py = i - j;
                return;
            }
        }
        // new set of diagonal, so reinitialize starting points
        dpi = dmi = 0;
    }
}

void make_moves_in_game(int n, int m, struct matrix_game *pmat,
    int* px_moves, int* po_moves) {
    // *pmat - pointer to collection of game matrix

    char name; // name of player (X or 0)
    int x, y, k, xo_name, xo_turn, invalid_move, ignore_move;

    initialize_matrix(n * n, n * n, pmat->board);
    initialize_matrix(n * n, n * n, pmat->time);
    initialize_matrix(n * n, n * n, pmat->no_err);
    xo_turn = +1; // first time is X turn
    ignore_move = 0; // false (if the board is full, the moves are only read)
    *px_moves = *po_moves = 0; // pointers to numbers for moves of X and 0

    for (k = 1; k <= m; ++k) {
        scanf("%c%c%d%d", &name, &name, &x, &y);

        if (ignore_move == 1) {
            continue;
        }

        invalid_move = 0; // false (assume that are not errors)

        if (name == 'X') {
            xo_name = +1; // X player
        } else {
            xo_name = -1; // O player
        }

        if (xo_name != xo_turn) {
            printf("NOT YOUR TURN\n");
            continue;
        } else {
            xo_turn *= -1; // change the turn of player
        }

        if (xo_name == +1) {
            (*px_moves)++;
        } else {
            (*po_moves)++;
        }

        if (!valid_index(n * n, x, y)) {
            printf("INVALID INDEX\n");
            invalid_move = 1; // true
        }

        if (valid_index(n * n, x, y) && pmat->board[x][y] != 0) {
            printf("NOT AN EMPTY CELL\n");
            invalid_move = 1; // true
        }

        if (invalid_move == 0) { // false (no errors)
            pmat->board[x][y] = xo_name;
            pmat->time[x][y] = k;
            pmat->no_err[x][y] = 1; // true (move from position x, y has no err)
            continue;
        }

        round_robin_algorithm(n, pmat->board, &x, &y);
        if (valid_index(n * n, x, y)) {
            pmat->board[x][y] = xo_name;
            pmat->time[x][y] = k;
        } else {
            // the round robin algorithm didn't find a empty cell
            printf("FULL BOARD\n");
            ignore_move = 1; // true; from now on, rest of the moves are ignored
        }
    }
}
