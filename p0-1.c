#include <stdio.h>
#include <string.h>

typedef struct {
    char c;
    int alphaCount[26]; 
} charInfo;

void countCharacters(FILE* text, charInfo* info);

int main(int argc, char *argv[]) {
    charInfo info;
    memset(info.alphaCount, 0, sizeof(info.alphaCount));
    
    FILE* text = fopen(argv[1], "r");
    if (text == NULL) {
        printf("Error opening %s.\n", argv[1]);
        return 1;
    }

    countCharacters(text, &info);

    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'A' + i, info.alphaCount[i]);
    }

    return 0;
}

void countCharacters(FILE* text, charInfo* info){
    while ((info->c = fgetc(text)) != EOF) {
        if (info->c >= 'a' && info->c <= 'z') {
            info->alphaCount[info->c - 'a']++;
        } else if (info->c >= 'A' && info->c <= 'Z') {
            info->alphaCount[info->c - 'A']++;
        }
    }
}