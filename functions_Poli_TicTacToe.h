// Copyright 2018 Nedelcu Horia (nedelcu.horia.alexandru@gmail.com)

#ifndef FUNCTIONS_POLI_TICTACTOE_H
#define FUNCTIONS_POLI_TICTACTOE_H

#include <stdio.h>
#include <limits.h>
#define N_MAX 100

struct matrix_game {
    int board[N_MAX][N_MAX], time[N_MAX][N_MAX], no_err[N_MAX][N_MAX],
    macroboard[N_MAX][N_MAX];
};


/* Use macros to choose either
   extern inline for GNU C, 
   inline for C99,
   or neither for a definition */
#ifndef INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif
INLINE int valid_index(int n, int x, int y) {
    if (x < 0 || n <= x || y < 0 || n <= y) {
        return 0; // invalid index
    }
    return 1; // valid index
}

void initialize_matrix(int rows, int columns, int matrix[N_MAX][N_MAX]);
void round_robin_algorithm(int n, int board[N_MAX][N_MAX], int* px, int* py);
void make_moves_in_game(int n, int m, struct matrix_game *pmat,
    int* px_moves, int* po_moves);

void new_potential_winner(int n, int xo_count, int timepass_moves,
    int* pwho_won, int* ptime_who_won,
    int a, int b,  int* plastx, int* plasty);
int who_won_miniboard(int n, int board[N_MAX][N_MAX], int time[N_MAX][N_MAX],
    int x, int y, int* plastx, int* plasty);
int check_if_somebody_won(int xoc, int w, int n);
int who_won_macroboard(int n, int macroboard[N_MAX][N_MAX]);
void compute_macroboard(int n, struct matrix_game *pmat,
    int* px_won, int* po_won);

void compute_attention_coeficient(int x_moves, int o_moves,
    int x_won, int o_won);

#endif /* FUNCTIONS_POLI_TICTACTOE_H */
