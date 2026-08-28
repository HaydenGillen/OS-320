#include <stdio.h>
#include <string.h>

#define NUM_LETTERS 26
#define MAX_GRAPH_WIDTH 50

typedef struct {
    char c;
    int alphaCount[NUM_LETTERS]; 
} charInfo;

void countCharacters(FILE* text, charInfo* info);
int findMax(int* arr, int size);

int main(int argc, char *argv[]) {
    charInfo info;
    memset(info.alphaCount, 0, sizeof(info.alphaCount));
    
    FILE* text = fopen(argv[1], "r");
    if (text == NULL) {
        printf("Error opening %s.\n", argv[1]);
        return 1;
    }

    countCharacters(text, &info);

    int maxCharCount = findMax(info.alphaCount, NUM_LETTERS);
    float charPerBar = maxCharCount / (float)MAX_GRAPH_WIDTH;
    printf("%f\n", charPerBar);

    for (int i = 0; i < NUM_LETTERS; i++) {
        printf("%c: %7d", 'A' + i, info.alphaCount[i]);
        for (int j = 0; j < (int)(info.alphaCount[i] / charPerBar); j++){
            printf("|");
        }
        printf("\n");
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

int findMax(int* arr,int size){
    int max = 0;
    for (int i = 0; i < size; i++){
        if (arr[i] > max){
            max = arr[i];
        } 
    }
    return max;
}