build:
	gcc -Wall -Wextra -std=c99 main.c make_moves.c compute_winner_macroboard.c attention_coeficient.c -o gigel -lm
clean:
	rm -rf gigel
