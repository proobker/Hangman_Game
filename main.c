#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 6
#define MAX_WORD_LENGTH 50

// List of words for the Hangman game
const char *words[] = {
    "amongus", "sigma","skibidi","ohio","fat","black","monkey"
};
const int num_words = 6;

// Function to display the hangman based on incorrect guesses
void display_hangman(int attempts_left) {
    switch (attempts_left) {
        case 6:
            printf("  +---+\n"
                   "      |\n"
                   "      |\n"
                   "      |\n"
                   "     ===\n");
            break;
        case 5:
            printf("  +---+\n"
                   "  O   |\n"
                   "      |\n"
                   "      |\n"
                   "     ===\n");
            break;
        case 4:
            printf("  +---+\n"
                   "  O   |\n"
                   "  |   |\n"
                   "      |\n"
                   "     ===\n");
            break;
        case 3:
            printf("  +---+\n"
                   "  O   |\n"
                   " /|   |\n"
                   "      |\n"
                   "     ===\n");
            break;
        case 2:
            printf("  +---+\n"
                   "  O   |\n"
                   " /|\\  |\n"
                   "      |\n"
                   "     ===\n");
            break;
        case 1:
            printf("  +---+\n"
                   "  O   |\n"
                   " /|\\  |\n"
                   " /    |\n"
                   "     ===\n");
            break;
        case 0:
            printf("  +---+\n"
                   "  O   |\n"
                   " /|\\  |\n"
                   " / \\  |\n"
                   "     ===\n");
            break;
    }
}

// Function to start a new game
void start_game(const char *selected_word) {
    char guessed_word[MAX_WORD_LENGTH];
    char guessed_char;
    int attempts_left = MAX_ATTEMPTS;
    int word_length = strlen(selected_word);
    int correct_guesses = 0;
    
    // Initialize the guessed word with underscores
    for (int i = 0; i < word_length; i++) {
        guessed_word[i] = '_';
    }
    guessed_word[word_length] = '\0';  // Null terminate the string

    // Game loop
    while (attempts_left > 0 && correct_guesses < word_length) {
        printf("\nWord: %s\n", guessed_word);
        printf("Attempts left: %d\n", attempts_left);
        display_hangman(attempts_left); // Show the hangman
        printf("\nEnter a letter to guess: ");
        scanf(" %c", &guessed_char);  // Take a single character input

        int found = 0;
        for (int i = 0; i < word_length; i++) {
            if (selected_word[i] == guessed_char && guessed_word[i] == '_') {
                guessed_word[i] = guessed_char;
                correct_guesses++;
                found = 1;
            }
        }

        if (!found) {
            attempts_left--;
            printf("Incorrect guess! You lose an attempt.\n");
        }

        if (correct_guesses == word_length) {
            printf("\nCongratulations! You've guessed the word: %s\n", selected_word);
            return;
        }
    }

    // If game over and the word was not guessed
    if (attempts_left == 0) {
        display_hangman(0);  // Display final hangman
        printf("\nGame Over! You lost. The word was: %s\n", selected_word);
    }
}

// Function to select a random word from the list
const char *get_random_word() {
    srand(time(NULL));  // Seed the random number generator
    int index = rand() % num_words;
    return words[index];
}

int main() {
    printf("Welcome to Hangman!\n");

    while (1) {
        const char *selected_word = get_random_word();
        printf("\nNew Game Started!\n");

        start_game(selected_word);

        char play_again;
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &play_again);
        if (play_again != 'y' && play_again != 'Y') {
            printf("Thanks for playing! Goodbye.\n");
            break;
        }
    }
    return 0;
}