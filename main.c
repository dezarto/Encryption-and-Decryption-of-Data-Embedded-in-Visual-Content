#define _CRT_SECURE_NO_WARNINGS

//==================  library definitions -START ==================
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
//==================  library definitions END ==================

//==================  preprocessing identification -START ==================
#define BMP_HEADER_SIZE 54 // image title size
#define MESSAGE_SIZE 240 // message size 
#define ADMIN_SIZE 20 // admin username and surname size
#define MAX_FIELDS 10  // maximum size to separate text

#define ADMIN_DEBUG 0 /*
                        This is developer and admin mode,
                        if set to 1 it will work and
                        if set to 0 it will not work.
                      */
                      //==================  preprocessing identification END ==================

                      //==================  implementation of function -START ===============================
void vernamDecrypt(char* text, const short size, const char* key, const short keyLen);
void vernamEncrypt(char* text, const char* key, const short size, const short keyLen);
unsigned short int encryptData(FILE* imageFile);
void printHex(const char* text, const short size);
void extractMessage(FILE* image, const short size, const char* key);
void embedMessage(FILE* image, const char* message, const short size);
unsigned short int stringLength(const char* text);
void printSeparatedData(const char* text);
void embedRandomKey(FILE* image, const char* data, const int startPixel, const int length);
void extractRandomKey(FILE* image, char* extractedData, const int startPixel, const int length);
char* generateRandomKey(int length);
//================== implementation of function END ===============================

//==================  main function -START ===============================
int main() {
    char imageName[100], operation[2], answer,
        passw[ADMIN_SIZE], username[ADMIN_SIZE], extractedData[120];
    unsigned short int size = 200, counter = 0;

#if ADMIN_DEBUG
    while (1) {
        printf("Are you Admin or Developer? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y') {
            if (counter != 2) {
                printf("Enter a username: ");
                scanf("%s", username);
                printf("Enter a password: ");
                scanf("%s", passw);

                if (strcmp(username, "admin") == 0 && strcmp(passw, "admin2") == 0) {
                    printf("\n\n______oBBBBB8o_____oBBBBBBB\n");
                    printf("____o8BBBBBBBBBBBBBBBBBBBB8_______o88o,\n");
                    printf("__o8BBBBBB**8BBBBBBBBBBBBBB____oBBBBBBBo,\n");
                    printf("_oBBBBBBB*___***___BBBBBBBBBB____BBBBBBBBBBo,\n");
                    printf("8BBBBBBBBBBooooo_*BBBBBBB8_____BB_8BBBBBBo,\n");
                    printf("8BBBBBBBBBBBBBBBB8ooBBBBBBB8__________8BBBBBBB8,\n");
                    printf("__*BBBBBBBBBBBBBBBBBBBBBBBBBB8_o88BB88BBBBBBBBBBBB,\n");
                    printf("____*BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB8,\n");
                    printf("______*8BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB,\n");
                    printf("___________BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB8,\n");
                    printf("____________BBBBBBBBBBBBBBBBBBBBBBBB8888*, \n");
                    printf("_____________BBBBBBBBBBBBBBBBBBBBBBB*,\n");
                    printf("_____________BBBBBBBBBBBBBBBBBBBBB,\n");
                    printf("______________*BBBBBBBBBBBBBBBBBB8,\n");
                    printf("_______________BBBBBBBBBBBBBBBB,\n");
                    printf("________________8BBBBBBBBBBBBBBB8,\n");
                    printf("_________________8BBBBBBBBBBBBBBBo,\n");
                    printf("__________________BBBBBBBBBBBBBBB8,\n");
                    printf("__________________BBBBBBBBBBBBBBBB,\n");
                    printf("__________________8BBBBBBBBBBBBBBB8,\n");
                    printf("__________________*BBBBBBBBBBBBBBBB,\n");
                    printf("__________________8BBBBBBBBBBBBBBBB8,\n");
                    printf("_________________oBBBBBBBBBBBBBBBBBB,\n");
                    printf("________________oBBBBBBBBBBBBBBBBBBB,\n");
                    printf("________________BBBBBBBBBBBBBBBBBBBB,\n");
                    printf("_______________8BBBBBBBBBBBBBBBBBBB8,\n");
                    printf("______________oBBBBBBBBB88BBBBBBBBB8,\n");
                    printf("______________8BBBBBBBBB*8BBBBBBBBB*,\n");
                    printf("______________BBBBBBBBB*_BBBBBBBBB8,\n");
                    printf("______________BBBBBBBB8_oBBBBBBBBB*,\n");
                    printf("_____________8BBBBBBB_oBBBBBBBBB*, \n");
                    printf("_____________8BBBBBBB_oBBBBBBBB*,\n");
                    printf("______________BBBBBBB*__8BBBBBBB*,\n");
                    printf("_____________8BBBBBB*___BBBBBBB*,\n");
                    printf("___________8BBBBBB8__oBBBBBB8,\n");
                    printf("__________8BBBBBB8___8BBBBBB*,\n");
                    printf("_________oBBBBBB8___BBBBBBB8,\n");
                    printf("_________BBBBBBB8__BBBBBBBB*,\n");
                    printf("________oBBBBBBB8__BBBBBBBB,\n");
                    printf("________8BBBBBB8___BBBBBBB*,\n");
                    printf("_________BBBBBB*_____8BBBBB*,\n");
                    printf("_______oBBBB8______BBBBB*,\n");
                    printf("_______oBBB8_______BBBB*,\n");
                    printf("______8BBBB*_______*BBBBBBBB8o,\n");
                    printf("______BBBBB*____________*88BBBo\n");
                    printf("\nThere is an admin around, run away :)\n\n");
                    break;
                }
                else {
                    printf("Password or username wrong! Try again later...\n");
                    counter++;
                }
            }
            else {
                printf("You have logged in incorrectly many times, we do not recognize you. bye");
                return 1;
            }
        }
        else {
            printf("Okay, no problem! bye...\n");
            return 1;
        }
    }
#endif

    printf("Please enter the image name (must be a maximum of 100 characters and a .bmp image): ");
    scanf("%100s", imageName);

    FILE* imageFile = fopen(imageName, "rb+");

    if (imageFile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Select the operation (encrypt (e)/decrypt (d)): ");
    scanf("%s", operation);
    printf("\n");

    if (strcmp(operation, "e") == 0) {
        size = encryptData(imageFile);
    }
    else if (strcmp(operation, "d") == 0) {
        extractRandomKey(imageFile, extractedData, 458, 11);

#if ADMIN_DEBUG
        printf("\nExtracted random key: %s\n", extractedData);
#endif

        extractMessage(imageFile, size, extractedData);

        printf("\n\t*       *       *       \n\t*     ***     ***     *\n\t**   *****   *****   **\n\t*** ******* ******* ***\n\t***********************\n\t***********************\n\tSee you soon stranger\n\t************************\n");
    }
    else {
        printf("Invalid operation!\n");
    }

    fclose(imageFile);

    return 0;
}
//==================  main function END ===============================

//==================  encryptData function -START ===============================
unsigned short int encryptData(FILE* imageFile) {
    char name[40], surname[30], ssn[12], timeValue[8],
        birthday[11], gender[3],
        plaintext[MESSAGE_SIZE], ciphertext[MESSAGE_SIZE], answer;
    unsigned short int key_size = 11; //key will be 11 characters

    do {
        // Information is obtained from the user
        printf("Name (max 39 character): ");
        scanf("%39s", name);
        printf("Surname (max 29 character): ");
        scanf("%29s", surname);
        printf("SSN (xxxxxxxxxxx): ");
        scanf("%11s", ssn);
        printf("Time (hh:mmAM or hh:mmPM): ");
        scanf("%s", timeValue);
        printf("Birthday (dd/mm/yyyy): ");
        scanf("%s", birthday);
        printf("Gender (F or M): ");
        scanf("%2s", gender);

        printf("\n\tYour name and surname: %s %s\n\tSSN: %s\n\tTime: %s\n\tBrithday: %s\n\tGender: %s",
            name, surname, ssn, timeValue, birthday, gender);
        printf("\nAre you sure you entered this information? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y') {
            sprintf(plaintext, "%s+%s+%s+%s+%s+%s+*", name, surname, ssn, timeValue, birthday, gender); // * palintext sonunutemsil eder
#if ADMIN_DEBUG
            printf("\Plaintext Data: %s\n", plaintext);
#endif
            strcpy(ciphertext, plaintext);
            size_t textLen = stringLength(ciphertext);

            char* randomKey = generateRandomKey(key_size);
#if ADMIN_DEBUG
            printf("\nRandom key is: ");
            for (int i = 0; i < key_size; i++) {
                printf("%c", randomKey[i]);
            }
#endif
            vernamEncrypt(ciphertext, randomKey, textLen, key_size);
#if ADMIN_DEBUG
            printf("\nEncrypted Data (Hex): ");
            printHex(ciphertext, textLen);
            printf("\nRandom key: %s\n", randomKey);
#endif
            embedMessage(imageFile, ciphertext, textLen);

            embedRandomKey(imageFile, randomKey, 458, key_size);

            return textLen;
        }
        else {
            printf("\nRe-enter all information...\n");
        }
    } while (answer != 'y');
}
//==================  encryptData function END ===============================

//==================  vernamEncrypt function -START ===============================
void vernamEncrypt(char* text, const char* key, const short size, const short keyLen) {

    for (size_t i = 0; i < size; ++i) {

#if ADMIN_DEBUG
        printf("\nBefore: %d\n", text[i]);
#endif

        text[i] = text[i] ^ key[i % keyLen];
        if (text[i] == '\0') {
            text[i] = '?'; /*NULL value corresponds to 0.
                            There is a problem when extracting the data.
                            We replace it with a question mark
                            corresponding to the value 63 in the ASCII table.*/
            i++;
        }

#if ADMIN_DEBUG
        printf("After: %d\n", text[i]);
#endif

    }
}
//==================  vernamEncrypt function END ===============================

//==================  vernamDecrypt function -START ===============================
void vernamDecrypt(char* text, const short size, const char* key, const short keyLen) {

    for (size_t i = 0; i < size; ++i) {
        if (text[i] == '?') {
            text[i] = '\0'; // ? with ASCII code 63 We replace the character with the NULL character whose ASCII code is 0.
            text[i] = text[i] ^ key[i % keyLen];
        }
        else {
            text[i] = text[i] ^ key[i % keyLen];
        }
    }
}
//==================  vernamDecrypt function END ===============================

//==================  embedMessage function -START ===============================
void embedMessage(FILE* image, const char* message, const short size) {

    fseek(image, BMP_HEADER_SIZE, SEEK_SET);

    for (size_t i = 0; i < size; ++i) {
        char ch = message[i];

        for (int j = 7; j >= 0; --j) {
            uint8_t pixel;
            fread(&pixel, sizeof(uint8_t), 1, image);

            pixel = (pixel & 0xFE) | ((ch >> j) & 1);
            fseek(image, -1, SEEK_CUR);
            fwrite(&pixel, sizeof(uint8_t), 1, image);
        }
    }

    printf("\nMessage successfully embed!");
}
//==================  embedMessage function END ===============================

//==================  extractMessage function -START ===============================
void extractMessage(FILE* image, const short size, const char* key) {
    char extractedMessage[MESSAGE_SIZE];
    memset(extractedMessage, 0, MESSAGE_SIZE);

    fseek(image, BMP_HEADER_SIZE, SEEK_SET);

    int index = 0;
    char ch = 0;

    while (1) {
        for (int j = 7; j >= 0; --j) {
            uint8_t pixel;
            fread(&pixel, sizeof(uint8_t), 1, image);

            ch = (ch << 1) | (pixel & 1);

            if (++index % 8 == 0) {
                if (ch == '\0') {
#if ADMIN_DEBUG
                    printf("\nExtracted Message: %s\n", extractedMessage);
                    printf("\nExtracted Message Data (Hex): ");
                    printHex(extractedMessage, size);
#endif
                    vernamDecrypt(extractedMessage, size, key, 11);
#if ADMIN_DEBUG
                    printf("Decrypted Message: %s\n", extractedMessage);
#endif
                    printSeparatedData(extractedMessage);
                    return;
                }
                extractedMessage[index / 8 - 1] = ch;
                ch = 0;
            }
        }
    }
}
//==================  extractMessage function END ===============================,

//==================  printHex function -START ===============================
void printHex(const char* text, const short size) {

    printf("0x");
    for (size_t i = 0; i < size; ++i) {
        printf("%02X", (unsigned char)text[i]);
    }
    printf("\n");
}
//==================  printHex function END ===============================

//==================  stringLength function -START ===============================
unsigned short int stringLength(const char* text) {
    size_t length = 0;
    while (text[length] != '\0') {
        length++;
    }
    return length;
}
//==================  stringLength function END ===============================

//==================  printSeparatedData function -START ===============================
void printSeparatedData(const char* text) {
    char* tokens[MAX_FIELDS];
    int index = 0;

    char* token = strtok((char*)text, "+");
    while (token != NULL && *token != '*') {
        tokens[index++] = token;
        token = strtok(NULL, "+");
    }

    if (index > 0) {
        const char* fields[] = { "Name", "Surname", "SSN", "Time", "Birthday", "Gender" };
        int fieldCount = sizeof(fields) / sizeof(fields[0]);

        for (int i = 0; i < index; ++i) {
            if (i < fieldCount) {
                printf("%s: %s\n", fields[i], tokens[i]);
            }
        }
    }
}
//==================  printSeparatedData function END ===============================

//==================  embedRandomKey function -START ===============================
void embedRandomKey(FILE* image, const char* data, const int startPixel, const int length) {
    fseek(image, BMP_HEADER_SIZE + startPixel * 3, SEEK_SET);

    for (int i = 0; i < length && data[i] != '\0'; ++i) {
        char ch = data[i];

        for (int j = 7; j >= 0; --j) {
            uint8_t pixel;
            fread(&pixel, sizeof(uint8_t), 1, image);

            pixel = (pixel & 0xFE) | ((ch >> j) & 1);
            fseek(image, -1, SEEK_CUR);
            fwrite(&pixel, sizeof(uint8_t), 1, image);
        }
    }

#if ADMIN_DEBUG
    printf("\nEmbedded random key: %s\n", data);
    printf("Random key embedded successfully!\n");
#endif
}
//==================  embedRandomKey function END ===============================

//==================  extractRandomKey function -START ===============================
void extractRandomKey(FILE* image, char* extractedData, const int startPixel, const int length) {
    fseek(image, BMP_HEADER_SIZE + startPixel * 3, SEEK_SET);

    for (int i = 0; i < length; ++i) {
        char ch = 0;

        for (int j = 7; j >= 0; --j) {
            uint8_t pixel;
            fread(&pixel, sizeof(uint8_t), 1, image);

            ch = (ch << 1) | (pixel & 1);
        }

        extractedData[i] = ch;
    }

    extractedData[length] = '\0';

#if ADMIN_DEBUG
    printf("\nRandom key successfully extracted!\n");
#endif
}
//==================  extractRandomKey function END ===============================

//==================  generateRandomKey function -START ===============================
char* generateRandomKey(int length) {
    char* key = (char*)malloc((length + 1) * sizeof(char));
    if (key == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    srand((unsigned int)time(NULL));

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < length; ++i) {
        int index = rand() % (sizeof(charset) - 1);
        key[i] = charset[index];
    }
    key[length] = '\0';

#if ADMIN_DEBUG
    printf("\nGenerated random key: %s\n", key);
#endif

    return key;
}
//==================  generateRandomKey function END ===============================