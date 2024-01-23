# TÜRKÇE
# Encryption-and-Decryption-of-Data-Embedded-in-Visual-Content

Detaylı bilgi için ekteki `Cryptography Project Report` raporunu inceleyiniz.

## Geliştiriciler İçin:

### Ana Fonksiyon (`main`)

- Kullanıcıya resim dosya adını ve ekleme veya çıkarma işlem türünü girmesine izin verir.
- `encryptData` fonksiyonu, kullanıcının kişisel bilgilerini çıkarır, şifreler ve bunu resmin içine gömer.
- `extractMessage` fonksiyonu, resimden şifreli veriyi çıkarır, şifresini çözer ve kullanıcıya gösterir.

### Veri Şifreleme ve Şifre Çözme Fonksiyonları (`vernamEncrypt`, `vernamDecrypt`)

- `vernamEncrypt` fonksiyonu metni Vernam şifreleme algoritması kullanarak şifreler.
- `vernamDecrypt` fonksiyonu şifreli metni çözer.

### Resim İşleme Fonksiyonları (`embedMessage`, `extractMessage`, `embedRandomKey`, `extractRandomKey`)

- `embedMessage` fonksiyonu şifreli metni resmin içine gömer.
- `extractMessage` fonksiyonu resimden şifreli metni çıkarır ve çözer.
- `embedRandomKey` ve `extractRandomKey` fonksiyonları rastgele anahtarı resme gömer ve çıkarır.

### Diğer Yardımcı Fonksiyonlar (`printHex`, `stringLength`, `printSeparatedData`, `generateRandomKey`)

- `printHex` fonksiyonu veriyi onaltılık formatta yazdırır.
- `stringLength` fonksiyonu bir dizinin uzunluğunu hesaplar.
- `printSeparatedData` fonksiyonu ekrana ayrılmış veriyi yazdırır.
- `generateRandomKey` fonksiyonu belirli bir uzunluktaki rastgele bir anahtar üretir.

### ADMIN_DEBUG Özellikleri:

1. **vernamEncrypt ve vernamDecrypt Fonksiyonları**
   - **Özellik:** Bu fonksiyonlar Verbatim şifreleme algoritması kullanarak veriyi şifreler veya şifre çözer.
   - **Geliştirici Özelliği:** `ADMIN_DEBUG` kullanarak şifreleme veya şifre çözme sürecinin ayrıntılarını `printf` ifadeleriyle detaylı bir şekilde izleyebilirsiniz. Bu, şifreleme ve şifre çözmenin doğruluğunu kontrol etmek için faydalı olabilir.

2. **embedMessage ve extractMessage Fonksiyonları**
   - **Özellik:** Bu fonksiyonlar şifreli metni resme gömer veya resimden çıkarır.
   - **Geliştirici Özelliği:** `ADMIN_DEBUG` kullanarak `printf` ifadeleriyle şifrelenen ve çıkarılan mesajı onaltılık formatta görüntüleyebilirsiniz. Bu, mesajın doğruluğunu kontrol etmek için faydalı olabilir.

3. **embedRandomKey ve extractRandomKey Fonksiyonları**
   - **Özellik:** Bu fonksiyonlar rastgele anahtarın resme gömülmesine veya çıkarılmasına izin verir.
   - **Geliştirici Özelliği:** `ADMIN_DEBUG` kullanarak gömülen veya çıkarılan rastgele anahtarın değerlerini görüntüleyebilirsiniz. Bu, rastgele anahtarın doğru bir şekilde işlendiğini doğrulamak için faydalı olabilir.

4. **Diğer Yardımcı Fonksiyonlar**
   - **Özellik:** `printHex`, `stringLength`, `printSeparatedData`, `generateRandomKey` gibi fonksiyonlar yardımcı işlemleri gerçekleştirir.
   - **Geliştirici Özelliği:** Belirli adımların veya verilerin iç durumunu `ADMIN_DEBUG` kullanarak `printf` ifadeleriyle gösterir. Bu şekilde, herhangi bir adımın beklenmeyen bir durumda olup olmadığını anlamak ve kodun çalışma sürecini anlamak daha kolay hale gelebilir.

   Bu `ADMIN_DEBUG` özelliği, geliştiricilere kodun izlenmesi, hata ayıklama ve fonksiyonların doğrulanması sürecinde yardımcı olmak için kullanılabilir. Ancak, normal kullanıcı ortamında, genellikle böyle detaylı çıktılar kapatılır, çünkü ek çıktılar performansı etkileyebilir ve güvenlik riski oluşturabilir.


# ENGLISH
# Encryption-and-Decryption-of-Data-Embedded-in-Visual-Content

Please review the attached report titled `Cryptography Project Report` for detailed information.

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
