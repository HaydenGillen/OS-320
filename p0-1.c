#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int charCount[26];
    memset(charCount, 0, sizeof(charCount));
    
    FILE* text = fopen(argv[1], "r");
    
    if (text == NULL) {
        printf("Error opening %s.\n", argv[1]);
        return 1;
    }

    int c;
    while ((c = fgetc(text)) != EOF) {
        if (c >= 'a' && c <= 'z') {
            charCount[c - 'a']++;
        } else if (c >= 'A' && c <= 'Z') {
            charCount[c - 'A']++;
        }
    }
    

    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, charCount[i]);
    }

    return 0;
}