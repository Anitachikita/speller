// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_number = hash(word);
    node *cursor = table[hash_number];

    while(cursor != NULL)
    {
        if(strcasecmp(cursor -> word, word) == 0) // means it's the same
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long  sum = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Can not open.\n");
        return false;
    }

    // scan the file, read strings
    char strings [LENGTH + 1];
    //locate mamory for the string
    while (fscanf(file, "%s", strings) != EOF)
    {
        //locate mamory for the string
        node *temp = malloc(sizeof(node));
        if (temp ==NULL)
        {
            unload();
            return false;
        }
        // function strcpy()
        strcpy(temp -> word, strings);
        temp->next = NULL;

        int hash_number = hash(strings);
        if(table[hash_number] == NULL)
        {
            temp -> next = NULL;
        }
        else
        {
            temp -> next = table[hash_number];
        }
        table[hash_number] = temp;
        word_count ++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        if (cursor == NULL && i == N-1)
        {
            return true;
        }
    }
    return false;
}
