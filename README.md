# Homework-2-Computer-Programming
Helped me to structure a project and to improve coding style

Nedelcu Horia
Group 311CA

Homework 2 - TicTacToe Poly:
   For each task we have created a function that solves it
which also calculates useful things for future tasks,
where appropriate (number of moves for X and 0; number of moves
winners without error for X and 0).

 - Task 1 (from the Gigel):
    I read each move in turn and post an error message if applicable,
otherwise I will execute it. For certain error moves, I generate if new is possible
move I execute. I remember the time when the moves were made and if
they had or did not have error in 2 matrices.
    Why we implemented this:
    The complexity of the runtime is equal to the number of initializations made
+ maximum number of moves that can be made (n ^ 4) * Round robin time Trr () (if for
each move shows an error) + the rest of the moves * O (1) (because they will only be read)
=> T1 (n) = 3 * n ^ 4 + minimum (m, n ^ 4) * Trr () + maximum (m-n ^ 4, 0) * O (1); if we do not use static variables,
Trr () would increase in execution with one step => a complexity of form: T1 (n) =
3 * n ^ 4 + 1 + 2 + ... + minimum (m, n ^ 4) + maximum (mn ^ 4, 0) * O (1) worst case = O (n ^ 4 * (n ^ 4 + 1) / 2) = O (n ^ 8);
with static variables we reduced Trr () = O (1) (each cell will be traversed only once)
=> T1 (n) worst_case = O (n ^ 4). On tests with n = 10, m = 10,000 and invalid moves method 2 a
was 40 times faster.

 - Task 2 (from Mary):
    For each cell of the macroboard I go to the characteristic submatrix
of the board that represents the minibar. I figure if anyone won
the minibus (he completed the fastest line) and the last move he won.
If the last move has no error, I gather it from the rest. In the end I calculate if anyone has
won the macroboard and display the result.
    Why we implemented this:
    The complexity of the execution time is equal to the number of cells of the macroboard (n ^ 2) *
who_won_miniboard function call time (which is 2 * n ^ 2 + 2 * n since only one goes
date and search in the board only the submarine microboard characteristic of the cell) + the call time of the function
who_won_macroboard (which is all 2 * n ^ 2 + 2 * n) => T2 (n) = n ^ 2 * n ^ 2 + n ^ 2 = O (n ^ 4).

 - Task 3 (all from Gigel):
    If the player has made moves, I calculate the coefficient of attention using
what I pre-calculated and post it, otherwise I post the required message.
    Complexity: T3 (n) = O (1).

   Thus the total complexity of the program in terms of n, with m approx = n ^ 4 (the board is completed)
is O (n ^ 4) gained in exchange for O (2 * n ^ 4) additional memory (Matrix for time and errors) which
can be recovered, if optimized with bit operations.
