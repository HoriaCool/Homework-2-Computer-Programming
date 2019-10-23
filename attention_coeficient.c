// Copyright 2018 Nedelcu Horia (nedelcu.horia.alexandru@gmail.com)

#include "./functions_Poli_TicTacToe.h"

void compute_attention_coeficient(int x_moves, int o_moves,
    int x_won, int o_won) {
    if (x_moves) { // verify if the attention coefficient can be computed
        printf("X %.10lf\n", (double) x_won / x_moves);
    } else {
        printf("X N/A\n"); // x_moves is equal 0
    }

    if (o_moves) { // verify if the attention coefficient can be computed
        printf("0 %.10lf\n", (double) o_won / o_moves);
    } else {
        printf("0 N/A\n"); // o_moves is equal 0
    }
}
