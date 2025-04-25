#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 3

// Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
bool checkWin(char board[SIZE][SIZE], char player);
bool isBoardFull(char board[SIZE][SIZE]);
void playerMove(char board[SIZE][SIZE], char player);
void computerMove(char board[SIZE][SIZE], char player);
bool isValidMove(char board[SIZE][SIZE], int row, int col);

int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int gameMode;
    bool gameOver = false;

    // Initialize random seed for computer moves
    srand(time(NULL));

    printf("Welcome to Tic Tac Toe!\n");
    printf("Choose game mode:\n");
    printf("1. 2-Player Mode\n");
    printf("2. Play against Computer\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &gameMode);

    initializeBoard(board);

    while (!gameOver) {
        printBoard(board);
        
        if (gameMode == 1 || currentPlayer == 'X') {
            printf("Player %c's turn\n", currentPlayer);
            playerMove(board, currentPlayer);
        } else {
            printf("Computer's turn\n");
            computerMove(board, currentPlayer);
        }

        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            if (gameMode == 1) {
                printf("Player %c wins!\n", currentPlayer);
            } else if (currentPlayer == 'X') {
                printf("Player X wins!\n");
            } else {
                printf("Computer wins!\n");
            }
            gameOver = true;
        } else if (isBoardFull(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            gameOver = true;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < SIZE - 1) {
            printf("-----------\n");
        }
    }
    printf("\n");
}

bool checkWin(char board[SIZE][SIZE], char player) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    return false;
}

bool isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void playerMove(char board[SIZE][SIZE], char player) {
    int row, col;
    do {
        printf("Enter row (1-3) and column (1-3) separated by space: ");
        scanf("%d %d", &row, &col);
        row--; // Convert to 0-based indexing
        col--;
    } while (!isValidMove(board, row, col));

    board[row][col] = player;
}

void computerMove(char board[SIZE][SIZE], char player) {
    // First, check if computer can win
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                if (checkWin(board, player)) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Then, check if need to block player
    char opponent = (player == 'X') ? 'O' : 'X';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = opponent;
                if (checkWin(board, opponent)) {
                    board[i][j] = player;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // If center is empty, take it
    if (board[1][1] == ' ') {
        board[1][1] = player;
        return;
    }

    // Otherwise, make a random move
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));

    board[row][col] = player;
}

bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }
    return board[row][col] == ' ';
} 