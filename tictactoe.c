#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

#define SIZE 3

// Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
bool checkWin(char board[SIZE][SIZE], char player);
bool isBoardFull(char board[SIZE][SIZE]);
void playerMove(char board[SIZE][SIZE], char player);
void computerMove(char board[SIZE][SIZE], char player);
bool isValidMove(char board[SIZE][SIZE], int row, int col);
void clearScreen();
void printScore(int playerScore, int computerScore, int draws);
void printInstructions();

int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int gameMode;
    bool gameOver = false;
    bool playAgain = true;
    int playerScore = 0;
    int computerScore = 0;
    int draws = 0;
    int difficulty;

    // Initialize random seed for computer moves
    srand(time(NULL));

    while (playAgain) {
        clearScreen();
        printf("Welcome to Tic Tac Toe!\n");
        printScore(playerScore, computerScore, draws);
        printf("\nChoose game mode:\n");
        printf("1. 2-Player Mode\n");
        printf("2. Play against Computer\n");
        printf("Enter your choice (1 or 2): ");
        
        while (scanf("%d", &gameMode) != 1 || (gameMode != 1 && gameMode != 2)) {
            printf("Invalid input! Please enter 1 or 2: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        if (gameMode == 2) {
            printf("\nChoose difficulty level:\n");
            printf("1. Easy (Random moves)\n");
            printf("2. Medium (Basic strategy)\n");
            printf("3. Hard (Advanced strategy)\n");
            printf("Enter your choice (1-3): ");
            
            while (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 3) {
                printf("Invalid input! Please enter 1, 2, or 3: ");
                while (getchar() != '\n'); // Clear input buffer
            }
        }

        initializeBoard(board);
        gameOver = false;
        currentPlayer = 'X';

        while (!gameOver) {
            clearScreen();
            printScore(playerScore, computerScore, draws);
            printBoard(board);
            printInstructions();
            
            if (gameMode == 1 || currentPlayer == 'X') {
                printf("Player %c's turn\n", currentPlayer);
                playerMove(board, currentPlayer);
            } else {
                printf("Computer's turn\n");
                computerMove(board, currentPlayer);
            }

            if (checkWin(board, currentPlayer)) {
                clearScreen();
                printScore(playerScore, computerScore, draws);
                printBoard(board);
                if (gameMode == 1) {
                    printf("Player %c wins!\n", currentPlayer);
                    if (currentPlayer == 'X') playerScore++;
                    else computerScore++;
                } else if (currentPlayer == 'X') {
                    printf("Player X wins!\n");
                    playerScore++;
                } else {
                    printf("Computer wins!\n");
                    computerScore++;
                }
                gameOver = true;
            } else if (isBoardFull(board)) {
                clearScreen();
                printScore(playerScore, computerScore, draws);
                printBoard(board);
                printf("It's a draw!\n");
                draws++;
                gameOver = true;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        printf("\nWould you like to play again? (1 for Yes, 0 for No): ");
        int choice;
        while (scanf("%d", &choice) != 1 || (choice != 0 && choice != 1)) {
            printf("Invalid input! Please enter 0 or 1: ");
            while (getchar() != '\n'); // Clear input buffer
        }
        playAgain = (choice == 1);
    }

    return 0;
}

void clearScreen() {
    system("cls");
}

void printScore(int playerScore, int computerScore, int draws) {
    printf("\nScore Board:\n");
    printf("Player X: %d\n", playerScore);
    printf("Player O/Computer: %d\n", computerScore);
    printf("Draws: %d\n", draws);
}

void printInstructions() {
    printf("\nBoard Positions:\n");
    printf(" 1 | 2 | 3 \n");
    printf("-----------\n");
    printf(" 4 | 5 | 6 \n");
    printf("-----------\n");
    printf(" 7 | 8 | 9 \n\n");
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
    int position;
    int row, col;
    do {
        printf("Enter position (1-9): ");
        while (scanf("%d", &position) != 1 || position < 1 || position > 9) {
            printf("Invalid input! Please enter a number between 1 and 9: ");
            while (getchar() != '\n'); // Clear input buffer
        }
        
        // Convert position to row and column
        row = (position - 1) / 3;
        col = (position - 1) % 3;
        
        if (!isValidMove(board, row, col)) {
            printf("Position already taken! Try again.\n");
        }
    } while (!isValidMove(board, row, col));

    board[row][col] = player;
}

void computerMove(char board[SIZE][SIZE], char player) {
    static int difficulty = 2; // Default to medium difficulty
    
    // Easy difficulty: Make random moves
    if (difficulty == 1) {
        int row, col;
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (!isValidMove(board, row, col));
        board[row][col] = player;
        return;
    }

    // Medium and Hard difficulty: Check for winning moves
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

    // Medium and Hard difficulty: Block opponent's winning moves
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

    // Hard difficulty only: Advanced strategies
    if (difficulty == 3) {
        // Try to create a fork (two winning opportunities)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player;
                    int winningPaths = 0;
                    
                    // Check rows
                    for (int row = 0; row < SIZE; row++) {
                        if (board[row][0] == player && board[row][1] == player && board[row][2] == ' ') winningPaths++;
                        if (board[row][0] == player && board[row][2] == player && board[row][1] == ' ') winningPaths++;
                        if (board[row][1] == player && board[row][2] == player && board[row][0] == ' ') winningPaths++;
                    }
                    
                    // Check columns
                    for (int col = 0; col < SIZE; col++) {
                        if (board[0][col] == player && board[1][col] == player && board[2][col] == ' ') winningPaths++;
                        if (board[0][col] == player && board[2][col] == player && board[1][col] == ' ') winningPaths++;
                        if (board[1][col] == player && board[2][col] == player && board[0][col] == ' ') winningPaths++;
                    }
                    
                    // Check diagonals
                    if (board[0][0] == player && board[1][1] == player && board[2][2] == ' ') winningPaths++;
                    if (board[0][0] == player && board[2][2] == player && board[1][1] == ' ') winningPaths++;
                    if (board[1][1] == player && board[2][2] == player && board[0][0] == ' ') winningPaths++;
                    
                    if (board[0][2] == player && board[1][1] == player && board[2][0] == ' ') winningPaths++;
                    if (board[0][2] == player && board[2][0] == player && board[1][1] == ' ') winningPaths++;
                    if (board[1][1] == player && board[2][0] == player && board[0][2] == ' ') winningPaths++;
                    
                    if (winningPaths >= 2) {
                        return;
                    }
                    board[i][j] = ' ';
                }
            }
        }
    }

    // Medium and Hard difficulty: Take center if available
    if (board[1][1] == ' ') {
        board[1][1] = player;
        return;
    }

    // Medium and Hard difficulty: Take corners
    int corners[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
    for (int i = 0; i < 4; i++) {
        if (board[corners[i][0]][corners[i][1]] == ' ') {
            board[corners[i][0]][corners[i][1]] = player;
            return;
        }
    }

    // Medium and Hard difficulty: Take edges
    int edges[4][2] = {{0,1}, {1,0}, {1,2}, {2,1}};
    for (int i = 0; i < 4; i++) {
        if (board[edges[i][0]][edges[i][1]] == ' ') {
            board[edges[i][0]][edges[i][1]] = player;
            return;
        }
    }
}

bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }
    return board[row][col] == ' ';
} 