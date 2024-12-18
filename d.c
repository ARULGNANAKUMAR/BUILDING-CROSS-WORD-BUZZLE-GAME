#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 10
#define COLS 10

// Trie data structure for word validation
struct TrieNode {
    struct TrieNode* children[26];
    bool isEndOfWord;
};

// Function to create a new Trie node
struct TrieNode* getNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;
    return node;
}

// Function to insert a word into the Trie
void insertWord(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;
    while (*word) {
        if (!current->children[*word - 'a'])
            current->children[*word - 'a'] = getNode();
        current = current->children[*word - 'a'];
        word++;
    }
    current->isEndOfWord = true;
}

// Function to search a word in the Trie
bool searchWord(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;
    while (*word) {
        if (!current->children[*word - 'a'])
            return false;
        current = current->children[*word - 'a'];
        word++;
    }
    return current != NULL && current->isEndOfWord;
}

// Function to place a word horizontally on the grid
bool placeWordHorizontally(char crossword[ROWS][COLS], const char* word, int row, int col) {
    int len = strlen(word);

    // Boundary check: does the word fit horizontally?
    if (col + len > COLS) {
        printf("Error: Word '%s' cannot be placed horizontally at (%d, %d) - out of bounds!\n", word, row, col);
        return false;
    }

    for (int i = 0; i < len; i++) {
        crossword[row][col + i] = word[i];
    }
    return true;
}

// Function to place a word vertically on the grid
bool placeWordVertically(char crossword[ROWS][COLS], const char* word, int row, int col) {
    int len = strlen(word);

    // Boundary check: does the word fit vertically?
    if (row + len > ROWS) {
        printf("Error: Word '%s' cannot be placed vertically at (%d, %d) - out of bounds!\n", word, row, col);
        return false;
    }

    for (int i = 0; i < len; i++) {
        crossword[row + i][col] = word[i];
    }
    return true;
}

// Function to display the crossword grid
void displayCrossword(char crossword[ROWS][COLS]) {
    printf("Current Crossword:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (crossword[i][j] == ' ') {
                printf(". ");
            } else {
                printf("%c ", crossword[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to get user input for a guess
bool getUser Input(char crossword[ROWS][COLS], struct TrieNode* dictionary) {
    int row, col;
    char guess[20];

    printf("Enter your word guess (or type 'quit' to exit): ");
    scanf("%s", guess);

    // Check for exit condition
    if (strcmp(guess, "quit") == 0) {
        return false;  // Break the loop and quit the game
    }

    printf("Enter row and column (0-indexed): ");
    scanf("%d %d", &row, &col);

    if (searchWord(dictionary, guess)) {
        // Insert the guessed word horizontally if it's valid
        if (!placeWordHorizontally(crossword, guess, row, col)) {
            printf("Failed to place word. Try again.\n");
        } else {
            printf("Correct! Word placed.\n");
        }
    } else {
        printf("Invalid word! Try again.\n");
    }
    return true;
}

void freeTrie(struct TrieNode* root) {
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            freeTrie(root->children[i]);
        }
    }