// Copyright 2018 Nedelcu Horia (nedelcu.horia.alexandru@gmail.com)

#include "./functions_Poli_TicTacToe.h"

void new_potential_winner(int n, int xo_count, int timepass_moves,
    int* pwho_won, int* ptime_who_won,
    int lx, int ly,  int* plastx, int* plasty) {
    // the function check if the moves along the same
    // line (row, column, diagonal) are the same and if they
    // are made in a shorter time than the previous ones

    // pwho_won - pointer to winner
    // ptime_who_won - pointer to winner's time
    // plastx, plasty - pointers to row and column for the winning move
    if (xo_count == +n  && *ptime_who_won > timepass_moves) {
        // there are only X on line
        *pwho_won = +1; // so +1 <=> X won
        *ptime_who_won = timepass_moves;
        *plastx = lx;
        *plasty = ly;
    }

    if (xo_count == -n  && *ptime_who_won > timepass_moves) {
        // there are only 0 on line
        *pwho_won = -1; // so -1 <=> 0 won
        *ptime_who_won = timepass_moves;
        *plastx = lx;
        *plasty = ly;
    }
}

int who_won_miniboard(int n, int board[N_MAX][N_MAX], int time[N_MAX][N_MAX],
    int x, int y, int* plastx, int* plasty) {
    // the function determines 1) who won the miniboard for the cell x,y
    // from macroboard and 2) the row and column of the winning move;
    // cell[x][y] of macroboard <=> submatrix
    // from board[n*x][n*y] to board[n*(x+1)-1][n*(y+1)-1]

    int i, j, xoc, tm, lt, lx, ly, w, tw;
    // xoc <=> xo_count - count types of moves along the same line
    // tm <=> timepass_moves - time for all moves to be made
    // lt <=> time of last move
    // lx, ly - row and column for the last move
    // w <=> who_won - winner
    // tw <=> time_who_won - winner's time
    // plastx, plasty - pointers to row and column for the last and winning move

    w = 0; // 0 <=> nobody won
    tw = INT_MAX;
    *plastx = -1; // there is no last move
    *plasty = -1; // there is no last move

    #define reinitialization_variables(xoc, tm, lt, lx, ly)                    \
        {                                                                      \
           xoc = 0;                                                            \
           tm = 0;                                                             \
           lt = -1;                                                            \
           lx = -1;                                                            \
           ly = -1;                                                            \
        }  while (0);                                                          \

    // brd = board[i][j], tmp = time[i][j]
    #define processing_line(xoc, tm, lt, lx, ly, brd, tmp, i, j)               \
        {                                                                      \
           xoc += brd;                                                         \
           tm += tmp;                                                          \
           /* the last move is made in the longest time */                     \
           if (lt < tmp) {                                                     \
               lt = tmp;                                                       \
               lx = i;                                                         \
               ly = j;                                                         \
           }                                                                   \
        }                                                                      \

    for (i = n * x; i < n * (x + 1); ++i) {
        reinitialization_variables(xoc, tm, lt, lx, ly);
        for (j = n * y; j < n * (y + 1); ++j) {
            processing_line(xoc, tm, lt, lx, ly, board[i][j], time[i][j], i, j);
        }
        // check new potential winner on row i:
        new_potential_winner(n, xoc, tm, &w, &tw, lx, ly, plastx, plasty);
    }

    for (j = n * y; j < n * (y + 1); ++j) {
        reinitialization_variables(xoc, tm, lt, lx, ly);
        for (i = n * x; i < n * (x + 1); ++i) {
            processing_line(xoc, tm, lt, lx, ly, board[i][j], time[i][j], i, j);
        }
        // check new potential winner on column j:
        new_potential_winner(n, xoc, tm, &w, &tw, lx, ly, plastx, plasty);
    }

    reinitialization_variables(xoc, tm, lt, lx, ly);
    for (i = n * x, j = n * y; i < n * (x + 1); ++i, ++j) {
        processing_line(xoc, tm, lt, lx, ly, board[i][j], time[i][j], i, j);
    }
    // check new potential winner on main diagonal:
    new_potential_winner(n, xoc, tm, &w, &tw, lx, ly, plastx,  plasty);

    reinitialization_variables(xoc, tm, lt, lx, ly);
    for (i = n * x, j = n * (y + 1) - 1; i < n * (x + 1); ++i, --j) {
        processing_line(xoc, tm, lt, lx, ly, board[i][j], time[i][j], i, j);
    }
    // check new potential winner on secondary diagonal:
    new_potential_winner(n, xoc, tm, &w, &tw, lx, ly, plastx, plasty);

    return w;
}

int check_if_somebody_won(int xoc, int w, int n) {
    // if both players have a full line, the game is draw
    if (xoc == +n  && w == -1) {
        return 2;
    }
    // if both players have a full line, the game is draw
    if (xoc == -n  && w == +1) {
        return 2;
    }
    // if the line is full with +1, X won
    if (xoc == +n) {
        return +1;
    }
    // if the line is full with -1, 0 won
    if (xoc == -n) {
        return -1;
    }

    return w;
}

int who_won_macroboard(int n, int macroboard[N_MAX][N_MAX]) {
    // the function determines who won the macroboard

    int i, j, xoc, w;
    // xoc <=> xo_count - count types of moves along the same line
    // w <=> who_won - (winner)

    w = 0; // 0 <=> nobody won

    for (i = 0; i < n; ++i) {
        xoc = 0;
        for (j = 0; j < n; ++j) {
            xoc += macroboard[i][j]; // check the row i
        }
        w = check_if_somebody_won(xoc, w, n);
        if (w == 2) { // game is draw
            return 0;
        }
    }

    for (j = 0; j < n; ++j) {
        xoc = 0;
        for (i = 0; i < n; ++i) {
            xoc += macroboard[i][j]; // check the column j
        }
        w = check_if_somebody_won(xoc, w, n);
        if (w == 2) { // game is draw
            return 0;
        }
    }

    xoc = 0;
    for (i = 0, j = 0; i < n && j < n; ++i, ++j) {
        xoc += macroboard[i][j]; // check the main diagonal
    }
    w = check_if_somebody_won(xoc, w, n);
    if (w == 2) { // game is draw
        return 0;
    }

    xoc = 0;
    for (i = 0, j = n - 1; i < n && j >= 0; ++i, --j) {
        xoc += macroboard[i][j]; // check the secondary diagonal
    }
    w = check_if_somebody_won(xoc, w, n);
    if (w == 2) { // game is draw
        return 0;
    }

    return w;
}

void compute_macroboard(int n, struct matrix_game *pmat,
    int* px_won, int* po_won) {
    // *pmat - pointer to collection of game matrix

    int i, j, who_won_the_game, lx, ly;
    // lx, ly - row and column for the last (winning) move in miniboard

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            pmat->macroboard[i][j] =
            who_won_miniboard(n, pmat->board, pmat->time, i, j, &lx, &ly);

            if (valid_index(n * n, lx, ly) && pmat->no_err[lx][ly] == 1) {
                // valid index for last move & no error made
                if (pmat->macroboard[i][j] == +1) {
                    (*px_won)++;
                } else if (pmat->macroboard[i][j] == -1) {
                    (*po_won)++;
                }
            }

            switch (pmat->macroboard[i][j]) {
                case +1 : printf("X"); // X won the miniboard
                          break;
                case -1 : printf("0"); // 0 won the miniboard
                          break;
                case  0 : printf("-"); // nobody won the miniboard
                          break;
            }
        }
        printf("\n");
    }

    who_won_the_game = who_won_macroboard(n, pmat->macroboard);

    if (who_won_the_game == +1) {
        printf("X won\n");
    } else if (who_won_the_game == -1) {
        printf("0 won\n");
    } else {
        printf("Draw again! Let's play darts!\n");
    }
}
