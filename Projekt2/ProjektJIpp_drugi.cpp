#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


#pragma warning (disable: 4996)

#define MAX_LINE_LEN 100000
#define INITIAL_MAX_WORDS 1000

int max_words = INITIAL_MAX_WORDS;
// Globalnie zadeklarowana tablica dla słów rozdzielanych z pliku
char** words = NULL;
int num_words = 0;
void read_words(FILE* file)
{
    
    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, file) != NULL)
    {
        // Rozndzielanie linii na słowa
        char* word = strtok(line, " \t\n");
        while (word != NULL)
        {
            //Alokowanie pamieci dla words
            if (num_words >= max_words)
            {
                // Zwiększanie rozmiaru tablicy
                max_words *= 2;
                words = (char**)realloc(words, max_words * sizeof(char*));
                if (words == NULL)
                {
                    fprintf(stderr, "Error: failed to allocate memory\n");
                    exit(1);
                }
            }
            // Alokowanie pamięci dla słowa
            words[num_words] = (char*)malloc((strlen(word) + 1) * sizeof(char));
            if (words[num_words] == NULL)
            {
                fprintf(stderr, "Error: failed to allocate memory\n");
                exit(1);
            }
            // Kopiowanie słowa do tablicy
            strcpy(words[num_words], word);
            num_words++;
            word = strtok(NULL, " \t\n");
        }
    }
}


char alphabet[] = { 'A', 'a', 'Ą', 'ą', 'B', 'b', 'C', 'c', 'Ć', 'ć', 'D', 'd', 'E', 'e', 'Ę', 'ę', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'Ł', 'ł', 'M', 'm', 'N', 'n', 'Ń', 'ń', 'O', 'o', 'Ó', 'ó', 'P', 'p', 'R', 'r', 'S', 's', 'Ś', 'ś', 'T', 't', 'U', 'u' ,'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', 'Ź', 'ź', 'Ż', 'ż'};

int my_strcmp(char* str1, char* str2)
{
    int i = 0;
    while (str1[i] && str2[i])
    {
        //znajdz index każdego chara w tablicy alfabet
        int index1 = -1, index2 = -1;
        for (int j = 0; j < sizeof(alphabet); j++)
        {
            if (alphabet[j] == str1[i])
            {
                index1 = j;
                break;
            }
        }
        for (int j = 0; j < sizeof(alphabet); j++)
        {
            if (alphabet[j] == str2[i])
            {
                index2 = j;
                break;
            }
        }
        // porownaj indexy
        if (index1 != -1 && index2 != -1)
        {
            if (index1 < index2)
            {
                return -1;
            }
            else if (index1 > index2)
            {
                return 1;
            }
        }
       
        i++;
    }
    // jeżeli oba stringi są równe do tego momentu ale jeden z nich jest dłuższy to zwróć -1 lub 1
    if (str1[i] == '\0' && str2[i] != '\0')
    {
        return -1;
    }
    else if (str1[i] != '\0' && str2[i] == '\0')
    {
        return 1;
    }
    // jeżeli oba stringi są równe
    return 0;
}



void quicksort(int left, int right)
{
    if (left < right)
    {
        int pivot = left;
        char* pivot_word = words[pivot];
        int i = left + 1;
        int j = right;

        while (i <= j)
        {
            while (i <= right && my_strcmp(words[i], pivot_word) <= 0)
            {
                i++;
            }
            while (j > left && my_strcmp(words[j], pivot_word) > 0) 
            {
                j--;
            }
            if (i < j)
            {
                // Zamiana words[i] z words[j]
                char* temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
        //Zamiana words[pivot] z words[j]
        char* temp = words[pivot];
        words[pivot] = words[j];
        words[j] = temp;

        quicksort(left, j - 1);
        quicksort(j + 1, right);
    }
}


void remove_punctuation(FILE* input_file, FILE* output_file)

{
    int c;
    // Prztwarzanie pliku wejściowego
    while ((c = fgetc(input_file)) != EOF) {
        if ((isalpha(c) && c <= 0x02AF) || isspace(c) || c == '\n' || c == '\r') {
            // Zostają tylko polskie i łacińskie znaki oraz spacje
            fputc(c, output_file);
        }
        else if (ispunct(c)) { // Zamiana znakow interpunkcyjnych na spacje
            fputc(' ', output_file);
        }
        else {
            // Nie rób nic
        }
    }
}

int main() {
    FILE* input_file, * output_file;

    // Set locale dla polskich znaków
    setlocale(LC_ALL, ".1250");

    // Otwiera plik wejsciowy i wyjsciowy
    input_file = fopen("input.txt", "r");
    output_file = fopen("output.txt", "w");

    // Usuwa interpunkcje
    remove_punctuation(input_file, output_file);
    // Zamyka pliki
    fclose(input_file);
    fclose(output_file);

    // Otwiera plik wyjsciowy w trybie czytania
    output_file = fopen("output.txt", "r");

    // Alokuje pamięć dla tablicy słów
    words = (char**)malloc(max_words * sizeof(char*));
    if (words == NULL) {
        fprintf(stderr, "Error: Nie można zaalokować pamięci na tablice words.\n");
        exit(1);
    }
    // Czyta słowa z pliku do tablicy
    read_words(output_file);

    // Sortuje tablice
    quicksort(0, num_words - 1);
    // Wypisuje posortowaną tablice słów
    for (int i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }
    // Zwalnia pamieć
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    free(words);

    printf("\nProgram zakonczony pomyslnie\n\n");
    return 0;
}