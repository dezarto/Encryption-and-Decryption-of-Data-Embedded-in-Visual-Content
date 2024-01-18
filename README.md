# Encryption-and-Decryption-of-Data-Embedded-in-Visual-Content

Please review the attached report titled 'Cryptography Project Report' for detailed information.

## For developers:

### Main Function (`main`)

- It allows the user to enter the image file name and operation type to add or remove embedded data.
- `encryptData` function extracts personal information from the user, encrypts it and stores it embedded in the image.
- `extractMessage` function extracts the encrypted data from the image, decrypts it, and displays it to the user.

### Data Encryption and Decryption Functions (`vernamEncrypt`, `vernamDecrypt`)

- `vernamEncrypt` function encrypts the text using the Vernam encryption algorithm.
- `vernamDecrypt` function decrypts the encrypted text.

### Image Processing Functions (`embedMessage`, `extractMessage`, `embedRandomKey`, `extractRandomKey`)

- `embedMessage` function embeds the encrypted text into the image.
- `extractMessage` function extracts and decrypts the ciphertext from the image.
- `embedRandomKey` and `extractRandomKey` functions embed and extract the random key from the image.

### Other Helper Functions (`printHex`, `stringLength`, `printSeparatedData`, `generateRandomKey`)

- The `printHex` function prints data in hexadecimal format.
- `stringLength` function calculates the length of a string.
- `printSeparatedData` function prints separated data to the screen.
- `generateRandomKey` function generates a random key of a given length.

### ADMIN_DEBUG Features:

1. **vernamEncrypt and vernamDecrypt Functions**
   - **Feature:** These functions encrypt or decrypt data using the Verbatim encryption algorithm.
   - **Developer Feature:** Using `ADMIN_DEBUG`, you can monitor the stages of the encryption or decryption process in detail. `printf` statements show the value of each character before and after encryption. This can be useful to check the correctness of encryption and decryption.

2. **embedMessage and extractMessage Functions**
   - **Feature:** These functions embed or extract ciphertext from the image.
   - **Developer Feature:** Using `ADMIN_DEBUG`, you can display the message embedded and extracted by `printf` statements in hexadecimal format. This can be useful to check the correctness of the displayed values of the message.

3. **embedRandomKey and extractRandomKey Functions**
   - **Feature:** These functions allow the random key to be embedded in or extracted from the image.
   - **Developer Feature:** Using `ADMIN_DEBUG`, you can view the values of the embedded or extracted random key. This can be useful to verify that the random key was processed correctly.

4. **Other Auxiliary Functions**
   - **Feature:** Functions like `printHex`, `stringLength`, `printSeparatedData`, `generateRandomKey` perform auxiliary operations.
   - **Developer Feature:** `Printf` statements have been added that indicate the internal state of certain steps or data using `ADMIN_DEBUG`. In this way, it can be easier to understand if any step is in an unexpected state and to understand the running process of the code.

   This `ADMIN_DEBUG` feature can be used to help developers in the process of tracing code, debugging, and validating functions. However, in the normal user environment, such detailed output is usually disabled, as extra output can affect performance and pose a security risk.
