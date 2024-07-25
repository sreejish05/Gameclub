#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define MAX_WORD_LEN 100
#define TIC_TAC_TOE_SIZE 3

typedef struct {
    char *word;
    char *display;
    int attempts;
} Hangman;

typedef struct {
    char **board;
    int size;
    char current_marker;
    int current_player;
} TicTacToe;

// Function prototypes for Hangman
void initialize_hangman(Hangman *game, const char *word);
void print_hangman(Hangman *game);
int guess_letter(Hangman *game, char letter);
int check_hangman_winner(Hangman *game);
void play_hangman();

// Function prototypes for Tic Tac Toe
void initialize_tictactoe(TicTacToe *game);
void print_tictactoe(TicTacToe *game);
int place_marker(TicTacToe *game, int row, int col);
int check_tictactoe_winner(TicTacToe *game);
void swap_player_and_marker(TicTacToe *game);
void play_tictactoe();
void free_tictactoe(TicTacToe *game);

// Function to choose and play the game
int main() {
    int choice;

    printf("Choose a game:\n");
    printf("1. Tic Tac Toe\n");
    printf("2. Hangman\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            play_tictactoe();
            break;
        case 2:
            play_hangman();
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            break;
    }

    return 0;
}

// Implementations for Hangman
void initialize_hangman(Hangman *game, const char *word) {
    game->word = strdup(word);
    int len = strlen(word);
    game->display = (char *)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++) {
        game->display[i] = '_';
    }
    game->display[len] = '\0';
    game->attempts = 0;
}

void print_hangman(Hangman *game) {
    printf("Word: %s\n", game->display);
    printf("Attempts left: %d\n", MAX_ATTEMPTS - game->attempts);
}

int guess_letter(Hangman *game, char letter) {
    int correct = 0;
    for (int i = 0; i < strlen(game->word); i++) {
        if (tolower(game->word[i]) == tolower(letter)) {
            game->display[i] = game->word[i];
            correct = 1;
        }
    }
    if (!correct) {
        game->attempts++;
    }
    return correct;
}

int check_hangman_winner(Hangman *game) {
    return strcmp(game->word, game->display) == 0;
}

void play_hangman() {
    Hangman game;
    const char *words[] = {"dog", "cat", "bat", "hat", "ball", "code", "java", "html", "css"};
    int num_words = sizeof(words) / sizeof(words[0]);
    
    // Filter words to ensure they are 5 characters or less
    const char *filtered_words[MAX_WORD_LEN];
    int filtered_count = 0;

    for (int i = 0; i < num_words; i++) {
        if (strlen(words[i]) <= 5) {
            filtered_words[filtered_count++] = words[i];
        }
    }

    srand(time(NULL));
    const char *word = filtered_words[rand() % filtered_count];
    initialize_hangman(&game, word);

    printf("Welcome to Hangman!\n");

    char guess;
    while (game.attempts < MAX_ATTEMPTS && !check_hangman_winner(&game)) {
        print_hangman(&game);
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        if (!guess_letter(&game, guess)) {
            printf("Incorrect guess.\n");
        }
    }

    if (check_hangman_winner(&game)) {
        printf("Congratulations! You've guessed the word: %s\n", game.word);
    } else {
        printf("You've run out of attempts. The word was: %s\n", game.word);
    }

    free(game.word);
    free(game.display);
}

// Implementations for Tic Tac Toe
void initialize_tictactoe(TicTacToe *game) {
    game->size = TIC_TAC_TOE_SIZE;
    game->board = (char **)malloc(game->size * sizeof(char *));
    for (int i = 0; i < game->size; i++) {
        game->board[i] = (char *)malloc(game->size * sizeof(char));
        for (int j = 0; j < game->size; j++) {
            game->board[i][j] = ' ';
        }
    }
    game->current_marker = 'X';
    game->current_player = 1;
}

void print_tictactoe(TicTacToe *game) {
    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            printf("%c", game->board[i][j]);
            if (j < game->size - 1) printf("|");
        }
        printf("\n");
        if (i < game->size - 1) {
            for (int j = 0; j < game->size; j++) {
                printf("-");
                if (j < game->size - 1) printf("+");
            }
            printf("\n");
        }
    }
}

int place_marker(TicTacToe *game, int row, int col) {
    if (game->board[row][col] != ' ') {
        return 0;
    }
    game->board[row][col] = game->current_marker;
    return 1;
}

int check_tictactoe_winner(TicTacToe *game) {
    // Check rows and columns
    for (int i = 0; i < game->size; i++) {
        int row_count = 0;
        int col_count = 0;
        for (int j = 0; j < game->size; j++) {
            if (game->board[i][j] == game->current_marker) row_count++;
            if (game->board[j][i] == game->current_marker) col_count++;
        }
        if (row_count == game->size || col_count == game->size) return 1;
    }

    // Check diagonals
    int diag1_count = 0;
    int diag2_count = 0;
    for (int i = 0; i < game->size; i++) {
        if (game->board[i][i] == game->current_marker) diag1_count++;
        if (game->board[i][game->size - i - 1] == game->current_marker) diag2_count++;
    }
    if (diag1_count == game->size || diag2_count == game->size) return 1;

    return 0;
}

void swap_player_and_marker(TicTacToe *game) {
    game->current_marker = (game->current_marker == 'X') ? 'O' : 'X';
    game->current_player = (game->current_player == 1) ? 2 : 1;
}

void play_tictactoe() {
    TicTacToe game;
    initialize_tictactoe(&game);

    int row, col;
    int winner = 0;

    printf("Welcome to Tic Tac Toe!\n");
    for (int i = 0; i < TIC_TAC_TOE_SIZE * TIC_TAC_TOE_SIZE; i++) {
        print_tictactoe(&game);
        printf("Player %d (%c), enter your move (row and column): ", game.current_player, game.current_marker);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= TIC_TAC_TOE_SIZE || col < 0 || col >= TIC_TAC_TOE_SIZE) {
            printf("Invalid move. Row and column must be between 0 and %d.\n", TIC_TAC_TOE_SIZE - 1);
            i--; // Retry the turn
            continue;
        }

        if (place_marker(&game, row, col)) {
            if (check_tictactoe_winner(&game)) {
                winner = game.current_player;
                break;
            }
            swap_player_and_marker(&game);
        } else {
            printf("Invalid move. The cell is already occupied.\n");
            i--; // Retry the turn
        }
    }

    print_tictactoe(&game);
    if (winner) {
        printf("Player %d wins!\n", winner);
    } else {
        printf("It's a draw!\n");
    }

    free_tictactoe(&game);
}

void free_tictactoe(TicTacToe *game) {
    for (int i = 0; i < game->size; i++) {
        free(game->board[i]);
    }
    free(game->board);
}
