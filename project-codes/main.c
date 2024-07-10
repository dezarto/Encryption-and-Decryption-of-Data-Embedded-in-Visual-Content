#define _CRT_SECURE_NO_WARNINGS

//==================  library definitions -START ==================
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
//==================  library definitions END ==================

//==================  preprocessing identification -START ==================
#define BMP_HEADER_SIZE 54 // image title size
#define MESSAGE_SIZE 240 // message size 
#define ADMIN_SIZE 20 // admin username and surname size
#define MAX_FIELDS 10  // maximum size to separate text

#define ADMIN_DEBUG 1 /*
                        This is developer and admin mode,
                        if set to 1 it will work and
                        if set to 0 it will not work.
                      */
#define VALIDATIONS_CONTROL 0 // You can control validations on/off
                      //==================  preprocessing identification END ==================

                      //==================  implementation of function -START ===============================
void vernamDecrypt(char* text, const short size, const char* key, const short keyLen);
void vernamEncrypt(char* text, const char* key, const short size, const short keyLen);
unsigned short int encryptData(FILE* imageFile);
void printHex(const char* text, const short size);
void printDec(const char* text, const short size);
void extractMessage(FILE* image, const short size, const char* key);
void embedMessage(FILE* image, const char* message, const short size);
unsigned short int stringLength(const char* text);
void printSeparatedData(const char* text);
void embedRandomKey(FILE* image, const char* data, const int length);
void extractRandomKey(FILE* image, char* extractedData, const int length);
char* generateRandomKey(int length);
int validateInput(const char* name, const char* surname, const char* ssn, const char* timeValue, const char* birthday, const char* gender);
int isValidSSN(const char* ssn);
int isValidTime(const char* time);
int isValidBirthday(const char* birthday);
int isValidGender(const char* gender);
//================== implementation of function END ===============================

//==================  main function -START ===============================
int main() {
    char imageName[100], operation[2], answer, passw[ADMIN_SIZE], username[ADMIN_SIZE], extractedData[120];
    unsigned short int size = 200, counter = 0;

#if ADMIN_DEBUG
    // Admin mode for debug
    while (1) {
        printf("Are you Admin or Developer? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y') {
            if (counter != 2) {
                printf("Enter a username: ");
                scanf("%s", username);
                printf("Enter a password: ");
                scanf("%s", passw);

                if (strcmp(username, "admin") == 0 && strcmp(passw, "admin") == 0) {
                    // Admin access granted
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
            printf("Only the Administrator can run this program, not you. Okay, no problem! bye...\n");
            return 1;
        }
    }
#endif

    while (1) {
        // Normal user flow
        printf("Please enter the image name (must be a maximum of 100 characters and a .bmp image): ");
        scanf("%100s", imageName);

        FILE* imageFile = fopen(imageName, "rb+");

        if (imageFile == NULL) {
            printf("Error opening the file. Try again..\n");
        }
        else {
            printf("Select the operation (encrypt (e)/decrypt (d)): ");
            scanf("%s", operation);
            printf("\n");

            if (strcmp(operation, "e") == 0) {
                // Create new image name
                char* dot = strrchr(imageName, '.');
                if (dot != NULL) {
                    *dot = '\0';
                }
                strcat(imageName, "_encrypted.bmp");

                FILE* newImageFile = fopen(imageName, "wb");

                if (newImageFile == NULL) {
                    printf("Error creating the new file.\n");
                    fclose(imageFile);
                    return 1;
                }

                // Copy original image to new image file
                char buffer[1024];
                size_t bytesRead;
                while ((bytesRead = fread(buffer, 1, sizeof(buffer), imageFile)) > 0) {
                    fwrite(buffer, 1, bytesRead, newImageFile);
                }

                fseek(imageFile, 0, SEEK_SET);
                fseek(newImageFile, 0, SEEK_SET);

                size = encryptData(newImageFile);

                fclose(newImageFile);

                return 0;
            }
            else if (strcmp(operation, "d") == 0) {
                extractRandomKey(imageFile, extractedData, 11);
#if ADMIN_DEBUG
                printf("\nExtracted random key: %s\n", extractedData);
#endif
                extractMessage(imageFile, size, extractedData);
                printf("\nSee you soon stranger\n");

                return 0;
            }
            else {
                printf("Invalid operation!\n");
            }

            fclose(imageFile);
        }
    }
    return 0;
}
//==================  main function END ===============================

//==================  encryptData function -START ===============================
unsigned short int encryptData(FILE* imageFile) {
    char name[40], surname[30], ssn[12], timeValue[10],
        birthday[11], gender[3],
        plaintext[MESSAGE_SIZE], ciphertext[MESSAGE_SIZE], answer = 'n';
    unsigned short int key_size = 11; // key will be 11 characters

    do {
        printf("Name (max 39 character): ");
        scanf("%39s", name);
        printf("Surname (max 29 character): ");
        scanf("%29s", surname);
        printf("SSN (xxxxxxxxxxx): ");
        scanf("%11s", ssn);
        printf("Time (hh:mmAM or hh:mmPM): ");
        scanf("%9s", timeValue);
        printf("Birthday (dd/mm/yyyy): ");
        scanf("%10s", birthday);
        printf("Gender (F or M): ");
        scanf("%2s", gender);
#if VALIDATIONS_CONTROL
        if (validateInput(name, surname, ssn, timeValue, birthday, gender)) {
#endif
            printf("All inputs are valid.\n");

            printf("\n\tYour name and surname: %s %s\n\tSSN: %s\n\tTime: %s\n\tBirthday: %s\n\tGender: %s",
                name, surname, ssn, timeValue, birthday, gender);
            printf("\nAre you sure you entered this information? (y/n): ");
            scanf(" %c", &answer); // boşluk karakteri ile birlikte %c
            if (answer == 'y') {
                sprintf(plaintext, "%s+%s+%s+%s+%s+%s+*", name, surname, ssn, timeValue, birthday, gender); // * plaintext sonunu temsil eder
#if ADMIN_DEBUG
                printf("\nPlaintext Data: %s\n", plaintext);
#endif
                strcpy(ciphertext, plaintext);
                size_t textLen = strlen(ciphertext);

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
                printf("\nEncrypted Data (Dec): ");
                printDec(ciphertext, textLen);
                printf("\nRandom key: %s\n", randomKey);
#endif
                embedMessage(imageFile, ciphertext, textLen);

                embedRandomKey(imageFile, randomKey, key_size);

                return textLen;
            }
            else {
                printf("\nRe-enter all information...\n");
            }
#if VALIDATIONS_CONTROL
        }
        else {
            printf("One or more inputs are invalid.\n");
        }
#endif
    } while (answer != 'y');

    return 0;
}
//==================  encryptData function END ===============================

//==================  stringLength function -START ===============================
unsigned short int stringLength(const char* text) {
    unsigned short int length = 0;
    while (text[length] != '\0') {
        length++;
    }
    return length;
}
//==================  stringLength function END ===============================

//==================  printHex function -START ===============================
void printHex(const char* text, const short size) {
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", (unsigned char)text[i]);
    }
}
//==================  printHex function END ===============================

//==================  printDecimal function -START ===============================
void printDec(const char* text, const short size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", (unsigned char)text[i]);
    }
}
//==================  printDecimal function END ===============================

//==================  embedMessage function -START ===============================
void embedMessage(FILE* image, const char* message, const short size) {
    fseek(image, 0, SEEK_END);
    long fileSize = ftell(image);
    long offset = fileSize - 1;

    for (size_t i = 0; i < size; ++i) {
        char ch = message[i];
        for (int j = 7; j >= 0; --j) {
            fseek(image, offset, SEEK_SET);
            uint8_t pixel;
            fread(&pixel, sizeof(uint8_t), 1, image);
            pixel = (pixel & 0xFE) | ((ch >> j) & 1);
            fseek(image, offset, SEEK_SET);
            fwrite(&pixel, sizeof(uint8_t), 1, image);
            offset--;
        }
    }
    printf("\nMessage successfully embed! ");
}
//==================  embedMessage function END ===============================

//==================  extractMessage function -START ===============================
void extractMessage(FILE* image, const short size, const char* key) {
    char extractedMessage[MESSAGE_SIZE];
    memset(extractedMessage, 0, MESSAGE_SIZE);
    fseek(image, 0, SEEK_END);
    long fileSize = ftell(image);
    long offset = fileSize - 1;
    int index = 0;
    char ch = 0;

    while (1) {
        for (int j = 7; j >= 0; --j) {
            fseek(image, offset, SEEK_SET);
            uint8_t pixel;
            fread(&pixel, sizeof(uint8_t), 1, image);
            ch = (ch << 1) | (pixel & 1);
            offset--;

            if (++index % 8 == 0) {
                if (ch == '\0') {
#if ADMIN_DEBUG
                    printf("\nExtracted Message: %s\n", extractedMessage);
                    printf("\nExtracted Message Data (Hex): ");
                    printHex(extractedMessage, size);
#endif
                    vernamDecrypt(extractedMessage, size, key, 11);
#if ADMIN_DEBUG
                    printf("\nDecrypted Message: %s\n", extractedMessage);
#endif
                    printf("\nDecrypted and Extracted Message:\n\n");
                    printSeparatedData(extractedMessage);
                    return;
                }
                extractedMessage[(index / 8) - 1] = ch;
                ch = 0;
            }
        }
    }
}
//==================  extractMessage function END ===============================

//==================  embedRandomKey function -START ===============================
void embedRandomKey(FILE* image, const char* data, const int length) {
    fseek(image, 0, SEEK_END);
    long fileSize = ftell(image);
    long offset = fileSize - length;

    for (int i = 0; i < length; i++) {
        fseek(image, offset + i, SEEK_SET);
        fwrite(&data[i], sizeof(char), 1, image);
    }
}
//==================  embedRandomKey function END ===============================

//==================  extractRandomKey function -START ===============================
void extractRandomKey(FILE* image, char* extractedData, const int length) {
    fseek(image, 0, SEEK_END);
    long fileSize = ftell(image);
    long offset = fileSize - length;

    for (int i = 0; i < length; i++) {
        fseek(image, offset + i, SEEK_SET);
        fread(&extractedData[i], sizeof(char), 1, image);
    }
    extractedData[length] = '\0';
}
//==================  extractRandomKey function END ===============================

//==================  printSeparatedData function -START ===============================
void printSeparatedData(const char* text) {
    unsigned short int i = 0, j = 0;
    char temp[MAX_FIELDS][20];

    // Tüm elemanları sıfırla
    for (int m = 0; m < MAX_FIELDS; m++) {
        memset(temp[m], 0, 20);
    }

    for (size_t k = 0; k < stringLength(text); k++) {
        if (text[k] != '+') {
            if (i < 19) { // Dizinin sınırlarını aşmamak için kontrol
                temp[j][i++] = text[k];
            }
        }
        else {
            temp[j][i] = '\0';
            j++;
            i = 0;
            if (j >= MAX_FIELDS) { // Dizinin sınırlarını aşmamak için kontrol
                break;
            }
        }
    }

    temp[j][i] = '\0'; // Son alanın sonunu belirlemek için

    printf("\nName: %s\nSurname: %s\nSSN: %s\nTime: %s\nBirthday: %s\nGender: %s\n",
        temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);
}

//==================  printSeparatedData function END ===============================

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
        key[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    key[length] = '\0';

#if ADMIN_DEBUG
    printf("\nGenerated random key: %s\n", key);
#endif

    return key;
}
//==================  generateRandomKey function END ===============================

//==================  vernamEncrypt function -START ===============================
void vernamEncrypt(char* text, const char* key, const short size, const short keyLen) {

    for (size_t i = 0; i < size; ++i) {

#if ADMIN_DEBUG
        printf("\nBefore decimal: %d, hexadecimal: %X, text: %c\n", text[i], text[i], text[i]);
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
        printf("After decimal: %d, hexadecimal: %X, text: %c\n", text[i], text[i], text[i]);
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

//==================  Validation function -START ===============================
int validateInput(const char* name, const char* surname, const char* ssn, const char* timeValue, const char* birthday, const char* gender) {
    if (strlen(name) > 39) {
        printf("Error: Name exceeds maximum length.\n");
        return 0;
    }
    if (strlen(surname) > 29) {
        printf("Error: Surname exceeds maximum length.\n");
        return 0;
    }
    if (!isValidSSN(ssn)) {
        printf("Error: Invalid SSN format.\n");
        return 0;
    }
    if (!isValidTime(timeValue)) {
        printf("Error: Invalid time format.\n");
        return 0;
    }
    if (!isValidBirthday(birthday)) {
        printf("Error: Invalid birthday format.\n");
        return 0;
    }
    if (!isValidGender(gender)) {
        printf("Error: Invalid gender format.\n");
        return 0;
    }
    return 1;
}

int isValidSSN(const char* ssn) {
    for (int i = 0; i < 11; i++) {
        if (!isdigit(ssn[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidTime(const char* time) {
    int len = strlen(time);
    if (len != 7) {
        return 0;
    }
    if (!isdigit(time[0]) || !isdigit(time[1]) || time[2] != ':' || !isdigit(time[3]) || !isdigit(time[4])) {
        return 0;
    }
    if (time[5] != 'A' && time[5] != 'P') {
        return 0;
    }
    if (time[6] != 'M') {
        return 0;
    }
    return 1;
}

int isValidBirthday(const char* birthday) {
    if (strlen(birthday) != 10) {
        return 0;
    }
    if (!isdigit(birthday[0]) || !isdigit(birthday[1]) || birthday[2] != '/' ||
        !isdigit(birthday[3]) || !isdigit(birthday[4]) || birthday[5] != '/' ||
        !isdigit(birthday[6]) || !isdigit(birthday[7]) || !isdigit(birthday[8]) || !isdigit(birthday[9])) {
        return 0;
    }
    return 1;
}

int isValidGender(const char* gender) {
    if (strlen(gender) != 1) {
        return 0;
    }
    if (gender[0] != 'F' && gender[0] != 'M') {
        return 0;
    }
    return 1;
}
//==================  Validation function -END ===============================