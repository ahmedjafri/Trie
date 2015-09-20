/* Ahmed Jafri
 * Assignment 5
 * March 3, 2014
 * T9.h
 *
 * This file has the main entry to the program and handles the file input as well as controlling the
 * operations on the trie. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie.h"

#define BUFFER_LENGTH 1024
#define NO_OCTOTHORPE -1

// read the user input into a given buffer; return NULL if Ctrl+D
char* readInput(char * inBuffer);

// open the file for reading and return the file handle.
FILE* getFileHandle(const char* inFilename);

int main(int argc, char *argv[])
{
    TrieNode * head = (TrieNode*)malloc(sizeof(TrieNode));

    // an old buffer to hold the old word
    char * buffer = (char*)malloc(BUFFER_LENGTH * sizeof(char) );
    
    // a character buffer to hold the characters read in by the user; THIS IS THE RAW DATA. IT SHOULD BE CLEANED.
	char * newBuffer = (char*)malloc(BUFFER_LENGTH * sizeof(char) );

    initTrie(head);
    
    FILE * fileHandle = getFileHandle(argv[1]);
	populateTrie(head, fileHandle);

    printf("Enter \"exit\" to quit. \n");
    printf("Enter Key Sequence (or \"#\" for next word):\n");
    printf("> ");
    
    // keep a location of the octothorpe location to traverse the linked list within the trie
    int octothorpeLocation;
    
    TrieNode* node;
    
    // use a constant character array to compare with to test for "exit"
    const char * exitString = "exit";
    
	while(readInput(newBuffer) && strcmp (exitString,newBuffer) != 0)
	{
        octothorpeLocation = NO_OCTOTHORPE;
        
        newBuffer = trimWhitespace(newBuffer);
        
        // if the string starts with an octothorpe then iterate through the linked list by appending '#' to the character buffer
        if(newBuffer[0] != '#')
        {
            strcpy(buffer, newBuffer);
            node = lookupWord(head, buffer, &octothorpeLocation);
        }
        else
        {
            buffer[strlen(buffer)] = '#';
            node = lookupWord(head, buffer, &octothorpeLocation);
        }
        

        
        if(node == NULL)
        {
            printf("\tNot found in current dictionary. \n");
        }
        else
        {
            if(octothorpeLocation == NO_OCTOTHORPE)
            {
                printf("\t'%s'\n",node->word);

            }
            else
            {
                
                int i;
                
                // loop through linked list
                for(i = octothorpeLocation; i < strlen(buffer) && node != NULL; i++)
                {
                    node = findNode(node, OCTOTHORPE);
                }
                
                if(node == NULL)
                {
                    printf("\tThere are no more T9onyms\n");

                }
                else
                {
                    printf("\t'%s'\n",node->word);
                }
            }

        }
        
        
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        printf("> ");
	}

    // free up all the memory before the process exits
    cleanupTrie(head);
    free(head);
	free(buffer);
    free(newBuffer);
    fclose(fileHandle);
	return 0;
}

char* readInput(char * inBuffer)
{
	char *result = fgets(inBuffer, BUFFER_LENGTH, stdin);

    // deal with CTRL+D input
	if(result == NULL)
	{
		return NULL;
	}

	clearNewline(result);

	return result;
}

FILE* getFileHandle(const char* inFilename)
{
	FILE *fileHandle = fopen(inFilename,"r");

	// make sure the file exists and has read permissions
	if(fileHandle == NULL)
	{
		fprintf(stderr, "Error opening file:%s \n",inFilename);
		fclose(fileHandle);
		exit(EXIT_FAILURE);
	}

	return fileHandle;
}