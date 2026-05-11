#include <stdio.h>
#include <string.h>

int main() {
    char input[105], result[105];
    int length, i, j = 0;

    scanf("%s", input);
    length = strlen(input);

    for (i = length - 1; i >= 0; i--) {
        char currentChar = input[i]; 
        if (currentChar >= 'A' && currentChar <= 'Z') {
            result[j++] = currentChar + ('a' - 'A'); // Konversi ke huruf kecil
        } else if (currentChar >= 'a' && currentChar <= 'z') {
            result[j++] = currentChar - ('a' - 'A'); // Konversi ke huruf besar
        } else {
            result[j++] = currentChar; // Dibiarkan hurufnya
        }
    }
    result[j] = '\0'; 

    printf("%s\n", result);

    return 0;
}
