/*-------------------------------------------
Name: Mustafa Ausaf
Project 2: WEAVER
Course: CS 211
Spring 2023
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Set the maximum length of each word
int ALL_LENGTH = 150;

// Declare a pointer to a character pointer to represent the dictionary of words
char **listOfWords;

// Declare a variable to keep track of the number of words in the dictionary
int numbsOfWords = 0;

// Define a function to free the memory associated with the dictionary of words
void WordsDictionary(char **dictionary, int length)
{
    // Loop through each word in the dictionary
    for (int i = 0; i < length; i++)
    {
        // Free the memory associated with the current word
        free(dictionary[i]);
    }

    // Free the memory associated with the dictionary itself
    free(dictionary);
}

/*
This function takes in two integer parameters:
wordLength: The length of the words to be searched for in the dictionary.
allWords: The number of words that can be stored in the array of pointers to strings.
*/

int dictionary(int wordLength, int allWords)
{
    char infile[] = "words.txt";
    // Open the file for reading.
    FILE *filePoi = fopen(infile, "r");
    if (filePoi == NULL)
    {
        printf("Error: Could not open dictionary file.\n");
        return 0;
    }

    // Allocate memory for the array of pointers to strings.
    char **additionalWords = (char **)malloc(allWords * sizeof(char *));
    if (additionalWords == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        fclose(filePoi);
        return 0;
    }

    // Read words from the file and store words of the specified length in the array of pointers to strings.
    char currWord[150];
    int wordInd = 0;
    while (fscanf(filePoi, "%s", currWord) != EOF)
    {
        if (strlen(currWord) == wordLength)
        {
            // Resize the array of pointers to strings if necessary.
            if (wordInd == allWords)
            {
                allWords *= 2;
                char **temp = (char **)realloc(additionalWords, allWords * sizeof(char *));
                if (temp == NULL)
                {
                    printf("Error: Memory allocation failed.\n");
                    fclose(filePoi);
                    WordsDictionary(additionalWords, wordInd);
                    return 0;
                }
                additionalWords = temp;
            }
            // Allocate memory for the string and copy the word to the string.
            additionalWords[wordInd] = (char *)malloc((wordLength + 1) * sizeof(char));
            if (additionalWords[wordInd] == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                fclose(filePoi);
                WordsDictionary(additionalWords, wordInd);
                return 0;
            }
            strcpy(additionalWords[wordInd], currWord);
            wordInd++;
        }
    }
    // Print the number of words stored and close the file.
    printf("Number of %d-letter words found: %d.\n\n", wordLength, wordInd);
    fclose(filePoi);

    // Print the words stored in the array of pointers to strings and the number of words stored.
    WordsDictionary(listOfWords, numbsOfWords);
    // Update the array of pointers to strings and the number of words stored.
    listOfWords = additionalWords;
    numbsOfWords = wordInd;

    // Return 1 to indicate success.
    return 1;
}

/*
The purpose of this function is to check whether a given word is in the dictionary 
of words that were previously loaded from the file.
*/
int wordCheck(char *word)
{
    // Loop through all the words in the dictionary
    for (int i = 0; i < numbsOfWords; i++)
    {
        // Check if the current word in the dictionary is equal to the given word
        if (strcmp(word, listOfWords[i]) == 0)
        {
            // If they're equal, return 1 (i.e. true)
            return 1;
        }
    }

    // If the word was not found in the dictionary, return 0 (i.e. false)
    return 0;
}


/**
 * Counts the number of positions where two words differ.
 * @param word1 the first word to compare
 * @param word2 the second word to compare
 * @param length the length of the words
 * @return the number of positions where the words differ
 */

/*
The purpose of this function is to compare two words (word1 and word2)
of a specified length and count the number of differing letters between them.
The function loops through each letter in the words up to the specified length and compares the letters at each position.
*/

int check_differ(char *word1, char *word2, int length)
{
    int count = 0;
    // Loop through each letter in the words up to the specified length
    for (int i = 0; i < length; i++)
    {
        // If the letters at the positions are different, increment the words counter
        if (word1[i] != word2[i])
        {
            count++;
        }
    }
    // Return the number of differing letters between the words
    return count;
}

int main()
{
    srand(1);

    printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
    printf("Enjoy!\n\n");

    // Prompt user for the desired word length
    int wordLength;
    printf("How many letters do you want to have in the words? ");
    scanf("%d", &wordLength);

    // Allocate memory for the list of words
    int allWords = 1500;
    listOfWords = (char **)malloc(allWords * sizeof(char *));
        if (listOfWords == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    // Call the dictionary function to populate the list of words
    if (!dictionary(wordLength, allWords))
    {
    // If the dictionary function returns an error, free allocated memory and return
        for (int i = 0; i < numbsOfWords; i++)
        {
            free(listOfWords[i]);
        }
            free(listOfWords);
        return 1;
    }


    int userWordChoice = 0;
    while (userWordChoice != 3)
    {
        // If the user chooses to change the word length
        if (userWordChoice == 2)
        {
            printf("How many letters do you want to have in the words? ");
            scanf("%d", &wordLength);
            // Free the memory allocated for previous list of words
            for (int i = 0; i < numbsOfWords; i++)
            {
                free(listOfWords[i]);
            }
            free(listOfWords);

            numbsOfWords = 0;

            allWords = 1000;

            // Allocate memory for new list of words
            listOfWords = (char **)malloc(allWords * sizeof(char *));
            if (listOfWords == NULL)
            {
                printf("Error: Memory allocation failed.\n");
                return 1;
            }
            // Populate the new list of words with words of the desired length
            if (!dictionary(wordLength, allWords))
            {
                for (int i = 0; i < numbsOfWords; i++)
                {
                    free(listOfWords[i]);
                }
                free(listOfWords);
                return 1;
            }
        }

        char startWord[150];
        char endWord[150];

        printf("Enter starting and ending words, or 'r' for either for a random word: ");
        while (1)
        {
            scanf("%s", startWord);
            scanf("%s", endWord);

            if (strcmp(startWord, "r") == 0)
            {
                int index = rand() % numbsOfWords;
                while (strlen(listOfWords[index]) != wordLength)
                {
                    index = rand() % numbsOfWords;
                }
                strcpy(startWord, listOfWords[index]);
            }

            if (strcmp(endWord, "r") == 0)
            {
                int index = rand() % numbsOfWords;
                while (strlen(listOfWords[index]) != wordLength || strcmp(listOfWords[index], startWord) == 0)
                {
                    index = rand() % numbsOfWords;
                }
                strcpy(endWord, listOfWords[index]);
            }

            if (strlen(startWord) != wordLength)
            {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", startWord, wordLength);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
            }
            else if (!wordCheck(startWord))
            {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n", startWord);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
            }
            else if (strcmp(startWord, endWord) == 0)
            {
                printf("Your and ending words are the same. Try again.\n");
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
            }
            else if (strlen(endWord) != wordLength)
            {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", endWord, wordLength);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
            }
            else if (!wordCheck(endWord))
            {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n", endWord);
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
            }
            else
            {
                break;
            }
        }

        char tempWord[150];
        strcpy(tempWord, startWord);
        printf("Your starting word is: %s.\n", startWord);
        printf("Your ending word is: %s.\n", endWord);
        printf("\nOn each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
        printf("You may also type in 'q' to quit guessing.\n");

        char userWordInput[150];
        int numWordMove = 0;
        char currWord[150];
        strcpy(currWord, startWord);
        char str2[50];
        strcpy(str2, startWord);
        int roundCount = 1;
        while (strcmp(currWord, endWord) != 0)
        {
            printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", roundCount, startWord, endWord);
            scanf("%s", userWordInput);

            if (strcmp(userWordInput, "q") == 0)
            {
                break;
            }
            if (strlen(userWordInput) != wordLength)
            {
                printf("Your word, '%s', is not a %d-letter word. Try again.\n", userWordInput, wordLength);
                continue;
            }
            else if (!wordCheck(userWordInput))
            {
                printf("Your word, '%s', is not a valid dictionary word. Try again.\n", userWordInput);
                continue;
            }
            else if (check_differ(currWord, userWordInput, wordLength) != 1)
            {
                printf("Your word, '%s', is not exactly 1 character different. Try again.\n", userWordInput);
                continue;
            }
            else
            {
                strcpy(startWord, userWordInput);
                roundCount++;
            }

            numWordMove++;
            strcpy(currWord, userWordInput);
        }
        if (strcmp(userWordInput, endWord) == 0)
        {
            printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", str2, endWord, numWordMove);
        }

        printf("\nEnter: \t1 to play again,\n");
        printf("\t2 to change the number of letters in the words and then play again, or\n");
        printf("\t3 to exit the program.\n");
        printf("Your choice --> ");

        scanf("%d", &userWordChoice);
    }

    printf("\nThanks for playing!\n");
    printf("Exiting...\n");

  
    for (int i = 0; i < numbsOfWords; i++)
    {
        free(listOfWords[i]);
    }
    free(listOfWords);

    return 0;
}