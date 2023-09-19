#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 30

struct WordFrequency {
    char word[MAX_WORD_LEN + 1];
    int frequency;
};

int compareWordFrequency(const void *a, const void *b) {
    return ((struct WordFrequency *)b)->frequency - ((struct WordFrequency *)a)->frequency;
}

int main() {
    char filename[] = "textfile.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    struct WordFrequency *wordFrequencies = NULL;
    int capacity = 1000;
    int size = 0;
    wordFrequencies = (struct WordFrequency *)malloc(sizeof(struct WordFrequency) * capacity);
    if (wordFrequencies == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    char word[MAX_WORD_LEN + 1];
    while (fscanf(file, "%s", word) != EOF) {
        int len = strlen(word);
        int j = 0;
        for (int i = 0; i < len; i++) {
            if (isalpha(word[i])) {
                word[j++] = tolower(word[i]);
            }
        }
        word[j] = '\0';
        if (strlen(word) == 0) {
            continue;
        }
        int found = 0;
        for (int i = 0; i < size; i++) {
            if (strcmp(wordFrequencies[i].word, word) == 0) {
                wordFrequencies[i].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (size == capacity) {
                capacity *= 2;
                wordFrequencies = (struct WordFrequency *)realloc(wordFrequencies, sizeof(struct WordFrequency) * capacity);

                if (wordFrequencies == NULL) {
                    printf("Memory allocation failed.\n");
                    return 1;
                }
            }
            strcpy(wordFrequencies[size].word, word);
            wordFrequencies[size].frequency = 1;
            size++;
        }
    }
    fclose(file);
    qsort(wordFrequencies, size, sizeof(struct WordFrequency), compareWordFrequency);
    int maxFrequency = wordFrequencies[0].frequency;
    printf("Words with the highest frequency (%d times):\n", maxFrequency);
    for (int i = 0; i < size && wordFrequencies[i].frequency == maxFrequency; i++) {
        printf("%s\n", wordFrequencies[i].word);
    }
    free(wordFrequencies);
    return 0;
}
