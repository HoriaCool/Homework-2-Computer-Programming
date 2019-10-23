// Copyright 2018 Nedelcu Horia (nedelcu.horia.alexandru@gmail.com)

#define INLINE
#include "./functions_Poli_TicTacToe.h"

int main() {
    int n, m, x_moves, o_moves, x_won, o_won;
    struct matrix_game mat;
    // n - board size
    // m - number of moves
    // x_moves, o_moves - number of moves made by X and 0
    // x_won, o_won - number of winning moves with no error made by X and 0
    // time[i][j] - time when the move from board[i][j] was made
    // no_err[i][j] - 1 (true) moves with no erro, 0 (false) moves with erro
    // board or macroboard - moves: 0 <=> empty cell; +1 <=> X; -1 <=> 0
    // mat - collection of enumerated matrix

    scanf("%d%d", &n, &m);

    make_moves_in_game(n, m, &mat, &x_moves, &o_moves);
    compute_macroboard(n, &mat, &x_won, &o_won);
    compute_attention_coeficient(x_moves, o_moves, x_won, o_won);

    return 0;
}
