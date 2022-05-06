/*
Project 1
Vicki Young
student ID: 20591845
start date: 2021.09.26
end date: 2021.10.18 at 2359
CS 221-02
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define TEXT_LENGTH 50

bool isStrongPassword(const char*, const char*);
bool isStrongDefaultPassword(const char*, const char*);
void generateDefaultPassword(char*, const char*);

int main(void) 
{
    char enteredUsername[TEXT_LENGTH+1];
    char enteredPassword[TEXT_LENGTH+1];
    char suggestedPassword[TEXT_LENGTH+1];

    srand(time(0)); //set the seed of the pseudorandom number generator using current time

    do {
        printf("Enter a username: ");
        scanf("%s", enteredUsername);

        printf("\nGenerating a default password...\n");
        generateDefaultPassword(suggestedPassword, enteredUsername);
        printf("Generated default password: %s\n\n", suggestedPassword);

        printf("Enter new password: ");
        scanf("%s", enteredPassword);

        if (isStrongPassword(enteredUsername, enteredPassword)) {
            printf("Strong password!\n");
            break;
        } else {
            printf("Your password is weak. Try again!\n\n");
        }

    } while (true);


	return 0;
}


/**
 *
 * A password strength meter and a default password generator, 
 * as defined in the CS221 course website for Project 1.
 *
 */

//write a function that validates password strength
//password must be at least 8 characters long
//must include at least 1 uppercase letter, 1 lowercase letter, and 1 digit
//must contain only letters and numbers
//must contain at least one string (consecutive letters) of at least 4 letters long (uppercase, lowercase, or combination of both)
//password cannot contain the username (username in the program is not case-sensitive/does not discern between uppercase and lowercase)
    //eg. if username is "vahab", and password contains "vaHaB", the password is considered weak

bool isStrongPassword(const char * username, const char * password) {
    const char *usernamePointer = username;
    const char *passwordPointer = password;
    int usernameLength = strlen(username);
	int passwordLength = strlen(password);
    bool lowercaseCheck = false;
    bool uppercaseCheck = false;
    bool digitCheck = false;

    int letterCount = 0;
    bool stringCheck = false;

    int commonCharacters;

    //password must be at least 8 characters long; if less than 8, return false
    if (passwordLength < 8) {
        return false;
    }

    //password must include only letters and numbers
    //password must also include at least 1 uppercase letter, 1 lowercase letter, and 1 digit
    while (*passwordPointer != '\0') {
        //if *passwordPointer is a lowercase letter, then lowercaseCheck becomes true; the password contains at least one lowercase letter
        if (*passwordPointer >= 'a' && *passwordPointer <= 'z') {
            lowercaseCheck = true;
            letterCount++;
        }
        //if *passwordPointer is an uppercase letter, then uppercaseCheck becomes true; the password contains at least one uppercase letter
        else if (*passwordPointer >= 'A' && *passwordPointer <= 'Z') {
            uppercaseCheck = true;
            letterCount++;
        }
        //if *passwordPointer is a number, then digitCheck becomes true; the password contains at least one digit
        //letterCount is reset to 0 (breaks the streak count of consecutive letters)
        else if (*passwordPointer >= '0' && *passwordPointer <= '9') {
            digitCheck = true;
            letterCount = 0;
        //RETURNS FALSE IF: *passwordPointer contains anything that is not a letter or number; password can only contain letters or numbers
        } else {
            return false;
        }

        //if the password has at least 4 letters (uppercase or lowercase) in a row, then stringCheck becomes true; password contains at least one string (consecutive letters) of at least 4 letters long
        if (letterCount >= 4) {
            stringCheck = true;
        }
        //increment passwordPointer to point to the next character in the password
        passwordPointer++;
    }
    //RETURNS FALSE IF:
    //password did not contain at least one lowercase letter, one uppercase letter, and one digit
    //password did not contain a string (consecutive letters) of at least 4 letters
    if (lowercaseCheck == false || uppercaseCheck == false || digitCheck == false || stringCheck == false) {
        return false;
    }

    //resets passwordPointer to point back to the first character in the password
    passwordPointer = &password[0];

    //now checks for if password contains the username
    //username in the program is not case-sensitive/does not discern between uppercase and lowercase
        //eg. if username is "vahab", and password contains "vaHaB", the password is considered weak
    //commonCharacters counts the number of CONSECUTIVE characters the username and password share in common
    commonCharacters = 0;
    while (*passwordPointer != '\0') {
        //checks if username and password have a digit in common (anything that is not a lowercase or uppercase letter)
        if (*usernamePointer == *passwordPointer) {
            commonCharacters++;
            usernamePointer++;
        }
        //checks if username and password have a letter in common (turns both to lowercase to check)
        //if arguments passed to the tolower() function are anything other than uppercase letter, returns same character back
        else if (tolower(*usernamePointer) == tolower(*passwordPointer)) { 
            commonCharacters++;
            usernamePointer++;
        //else if the username and password do not share any character in common, usernamePointer is reset to point back to the first character in the username
        //also resets commonCharacters (breaks the streak count for consecutive characters in that the username and password share in common) 
        } else {
            commonCharacters = 0;
            usernamePointer = &username[0];
        }

        //RETURNS FALSE IF: the password contains the username, because the number of consecutive characters the username and password share in common is equal to the length of the username
        if (commonCharacters == usernameLength) {
            return false;
        }
        //increment passwordPointer to point to the next character in the password
        passwordPointer++;
    }

    //finally if the password has passed all the checks and nothing has made function return false so far, then password meets the guidelines; returns true
	return true;
}

/** 
 * This function may *not* call isStrongPassword(). 
 * This function must call isStrongDefaultPassword().
 */
//generates default password randomly, which is then stored in the char array that default_password points to
//every character in default password is chosen randomly and independently from all allowed characters
//the size of the generated password is also random
//in a loop, program continually generates random strings
//then checks if the password requirements for the generated default password are met (calls isStrongDefaultPassword())
//once a compliant password is generated, the loop ends and program displays generated password
void generateDefaultPassword(char * default_password, const char * username) {
	const char charSet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int charSetSize = strlen(charSet); //exact number of allowed characters
    int key;

    //loop continues to generate new default_password until one satisfies isStrongDefaultPasswrd(), as in, until it returns True
	do {
        //default_password random size from 0 to 15
        int size = rand() % 16;
        //for loop which assigns characters randomly from charSet to default_password string array
        for (int i = 0; i < size; i++) {
            key = rand() % charSetSize; //random number from 0 to (size of the charSet array - 1)
            default_password[i] = charSet[key];
        }
        default_password[size] = '\0'; //indicate end of default_password string array
        //FOR TESTING printf("current generated password: %s\n", default_password);
    } while (!isStrongDefaultPassword(username, default_password));
}


/** 
 * Example: isStrongDefaultPassword("vahab", "Taher3h") returns false
 */
//checks if the given default password is strong based on new constraints:
    //must have all the requirements of a strong password (Part I) EXCEPT FOR THE FOLLOWING:
    //default password must be 15 characters or shorter
    //default password does not need to satisfy 4 consecutive letters requirement
bool isStrongDefaultPassword(const char* username, const char* password) {
    const char *usernamePointer = username;
    const char *passwordPointer = password;
    int usernameLength = strlen(username);
	int passwordLength = strlen(password);
    bool lowercaseCheck = false;
    bool uppercaseCheck = false;
    bool digitCheck = false;
    int commonCharacters;

    //password must be at least 8 characters long; if less than 8, return false
    //password is already 15 characters or less so dont need to check
    if (passwordLength < 8) {
        return false;
    }

    //password must include only letters and numbers
    //password must also include at least 1 uppercase letter, 1 lowercase letter, and 1 digit
    while (*passwordPointer != '\0') {
        //if *passwordPointer is a lowercase letter, then lowercaseCheck becomes true; the password contains at least one lowercase letter
        if (*passwordPointer >= 'a' && *passwordPointer <= 'z') {
            lowercaseCheck = true;
        }
        //if *passwordPointer is an uppercase letter, then uppercaseCheck becomes true; the password contains at least one uppercase letter
        else if (*passwordPointer >= 'A' && *passwordPointer <= 'Z') {
            uppercaseCheck = true;
        }
        //if *passwordPointer is a number, then digitCheck becomes true; the password contains at least one digit
        else if (*passwordPointer >= '0' && *passwordPointer <= '9') {
            digitCheck = true;
        //RETURNS FALSE IF: *passwordPointer contains anything that is not a letter or number; password can only contain letters or numbers
        } else {
            return false;
        }

        //increment passwordPointer to point to the next character in the password
        passwordPointer++;
    }
    //RETURNS FALSE IF:
    //password did not contain at least one lowercase letter, one uppercase letter, and one digit
    if (lowercaseCheck == false || uppercaseCheck == false || digitCheck == false) {
        return false;
    }

    //resets passwordPointer to point back to the first character in the password
    passwordPointer = &password[0];

    //now checks for if password contains the username
    //username in the program is not case-sensitive/does not discern between uppercase and lowercase
        //eg. if username is "vahab", and password contains "vaHaB", the password is considered weak
    //commonCharacters counts the number of CONSECUTIVE characters the username and password share in common
    commonCharacters = 0;
    while (*passwordPointer != '\0') {
        //checks if username and password have a digit in common (anything that is not a lowercase or uppercase letter)
        if (*usernamePointer == *passwordPointer) {
            commonCharacters++;
            usernamePointer++;
        }
        //checks if username and password have a letter in common (turns both to lowercase to check)
        //if arguments passed to the tolower() function are anything other than uppercase letter, returns same character back
        else if (tolower(*usernamePointer) == tolower(*passwordPointer)) { 
            commonCharacters++;
            usernamePointer++;
        //else if the username and password do not share any character in common, usernamePointer is reset to point back to the first character in the username
        //also resets commonCharacters (breaks the streak count for consecutive characters in that the username and password share in common) 
        } else {
            commonCharacters = 0;
            usernamePointer = &username[0];
        }

        //RETURNS FALSE IF: the password contains the username, because the number of consecutive characters the username and password share in common is equal to the length of the username
        if (commonCharacters == usernameLength) {
            return false;
        }
        //increment passwordPointer to point to the next character in the password
        passwordPointer++;
    }

    //finally if the password has passed all the checks and nothing has made function return false so far, then password meets the guidelines; returns true
	return true;
}