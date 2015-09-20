/* Ahmed Jafri
 * Assignment 5
 * March 3, 2014
 * Trie.c
 *
 * This implementation file contains the body of the trie modification methods contained in the header.
 *
 */

#include "Trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_LINE_LENGTH 100 //longest word

// keep a size count of the number of words in the trie
static long size = 0;

// get the corresponding digit from the given character
int getDigit(const char inCharacter);
void addNode(const char * inWord, TrieNode * currentNode, int index);
TrieNode* addChild(TrieNode * node, int inNumber);
TrieNode* initNode(TrieNode * node);
void printTrie(TrieNode* currentNode);
void freeTrie(TrieNode * node);
TrieNode* findByPrefix(TrieNode * prefix, int iteration);


void initTrie(TrieNode * inHead)
{
    inHead->children = NULL;
    inHead->number = 0;
    inHead->numberOfChildren = 0;
    inHead->parent = inHead;
    inHead->word = malloc(sizeof(char));
    inHead->word[0] = 'h';
}

void addWord(TrieNode * inHead, const char * inWord)
{
    //printf("Adding word: %s...\n",inWord);
	addNode(inWord,inHead,0);
    //printTrie(&head);
	size++;
}

void printTrie(TrieNode* currentNode)
{
    if(currentNode == NULL)
        return;
    
    printf("parent: %s\t#ofchildren: %d\tnumber: %d\tword: %s",
           currentNode->parent->word,currentNode->numberOfChildren,currentNode->number,currentNode->word);
    printf("\n");
    
    int i;
    for(i = 0; i < currentNode->numberOfChildren; i++)
    {
        TrieNode* child = &currentNode->children[i];
        printTrie(child);
    }

}

TrieNode* initNode(TrieNode * node)
{
	node->number = 0;
    node->word = malloc(sizeof(char));
    node->children = NULL;
    node->numberOfChildren = 0;
    return node;
}

void setWord(TrieNode *node, const char* inWord)
{
    node->word = (char*)realloc(node->word, sizeof(char) * strlen(inWord));
    strncpy(node->word, inWord, strlen(inWord));
}

//
void addNode(const char * inWord, TrieNode * currentNode, int index)
{
	// base case. this is the end of the word.
	if( index >= strlen(inWord) )
	{
        // if the node word is a number then set the node word to the inWord
        if(currentNode->word[0] < '9' && currentNode->word[0] > '0')
        {
            setWord(currentNode, inWord);
            return;
        }
        else
        {
            //either word is already set or reached an octothorpe node
            if(currentNode->numberOfChildren == 0)
            {
                TrieNode *childNode = addChild(currentNode,OCTOTHORPE);
                setWord(childNode,inWord);
                return;
            }
            else
            {
                TrieNode * octothorpeNode = findNode(currentNode, OCTOTHORPE);
                
                if(octothorpeNode == NULL)
                {
                    // no octothrope in children
                    TrieNode *childNode = addChild(currentNode,OCTOTHORPE);
                    setWord(childNode,inWord);
                    return;
                }
                else
                {
                    // traverse deeper in the octothorpe linked list
                    addNode(inWord, octothorpeNode, index);
                    return;
                }
            }
        }
        
	}

	int digit = getDigit(inWord[index]);
	TrieNode *childNode = addChild(currentNode,digit);
	addNode(inWord,childNode,++index);
}


TrieNode* addChild(TrieNode * node, int inNumber)
{
	// look through existing children to see if it already exists
	if(node->children != NULL)
	{
		int i;
		for(i = 0; i < node->numberOfChildren; i++)
		{
			TrieNode* child = &node->children[i];

			if(child->number == inNumber)
				return child;
		}
	}

	if(node->children == NULL)
	{
		// allocate enough space for one node
		node->children = (TrieNode*)calloc(1,sizeof(TrieNode));
		node->numberOfChildren = 1;
	}
	else
	{
		node->numberOfChildren++;
		// reallocate enough space for more pointers
		node->children = (TrieNode*)realloc(node->children, node->numberOfChildren*sizeof(TrieNode));
        
        int i;
        for(i = 0; i < node->numberOfChildren-1; i++)
        {
            TrieNode* child = &node->children[i];
            child->parent = node;
        }
	}

    TrieNode* newChild = &node->children[node->numberOfChildren-1];
	TrieNode* newNode = initNode(newChild);
	newNode->parent = node;
    newNode->number = inNumber;
    (*newNode->word) = (char)inNumber + '0';
	return newNode;
}

void populateTrie(TrieNode * inHead, FILE * inFileHandle)
{
	char * buffer = (char*)malloc( FILE_LINE_LENGTH * sizeof(char) );

	// loop over all the lines in the file
	while( fgets(buffer, FILE_LINE_LENGTH, inFileHandle) ) 
	{
		clearNewline(buffer);
		strtolower(buffer);
		addWord(inHead, buffer);
	}

	free(buffer);
}

void clearNewline(char * inBuffer)
{
	unsigned long length = strlen(inBuffer);

	if(inBuffer[length - 1] == '\n')
	{
		inBuffer[length - 1] = '\0'; //replace any newlines with a termination character
	}
}

// the character is assumed to always be lowercase
int getDigit(const char inCharacter)
{
	if(inCharacter > 'z' || inCharacter < 'a')
	{
		// not a character
		return -1;
	}

	if(inCharacter == 'a' || inCharacter == 'b' || inCharacter == 'c')
		return 2;
	else if(inCharacter == 'd' || inCharacter == 'e' || inCharacter == 'f')
		return 3;
	else if(inCharacter == 'g' || inCharacter == 'h' || inCharacter == 'i')
		return 4;
	else if(inCharacter == 'j' || inCharacter == 'k' || inCharacter == 'l')
		return 5;
	else if(inCharacter == 'm' || inCharacter == 'n' || inCharacter == 'o')
		return 6;
	else if(inCharacter == 'p' || inCharacter == 'q' || inCharacter == 'r' || inCharacter == 's')
		return 7;
	else if(inCharacter == 't' || inCharacter == 'u' || inCharacter == 'v')
		return 8;
	else if(inCharacter == 'w' || inCharacter == 'x' || inCharacter == 'y' || inCharacter == 'z')
		return 9;
	else 
		return 1;
}

TrieNode* findNode(TrieNode * node, int number)
{
    TrieNode* returnNode = NULL;
    
    int i;
    for(i = 0; i < node->numberOfChildren; i++)
    {
        TrieNode* child = &node->children[i];
        
        if(child->number == number)
            returnNode = child;
    }
    
	return returnNode;
}

TrieNode* lookupWord(TrieNode * inHead, char* inNumberSequence, int *outOctothorpeLocation)
{
    TrieNode *returnNode = inHead;
    int number;
        
    int i;
    for(i = 0; i < strlen(inNumberSequence); i++)
    {
        // convert character to integer
        number = inNumberSequence[i] - '0';
        
        if(inNumberSequence[i] == '#')
        {
            *outOctothorpeLocation = i;
            // exit the loop if we reach an octothorpe
            break;
        }
        
        returnNode = findNode(returnNode, number);
        
        if(returnNode == NULL )
        {
            return NULL;
        }
    }
    
    if(returnNode->numberOfChildren > 0 && *returnNode->word > '0' && *returnNode->word < '9')
    {
        returnNode = findByPrefix(returnNode, 0);
    }
    
    // protect the case where the return node doesn't have a word
    if( (*returnNode->word > '0' && *returnNode->word < '9') )
    {
        return NULL;
    }
    
    return returnNode;
}

TrieNode* findByPrefix(TrieNode * prefix, int iteration)
{
    if(prefix->numberOfChildren == 0)
        return prefix;
    
    TrieNode* returnNode = findNode(prefix, prefix->children->number);
    
    return findByPrefix(returnNode, 0);
}

char* trimWhitespace(char *inString)
{
    int i,j;
    for (i = 0; i < strlen(inString); i++) {
        //shift over everything if blank found
        if(inString[i] == ' ')
        {
            for (j = i; j < strlen(inString); j++) {
                inString[j] = inString[j+1];
            }

        }
    }
    
    return inString;
}

void cleanupTrie(TrieNode * inHead)
{
    freeTrie(inHead);
}

void freeTrie(TrieNode * node)
{
    if(node == NULL)
        return;
    
    int i;
    for(i = 0; i < node->numberOfChildren; i++)
    {
        TrieNode* child = &node->children[i];
        freeTrie(child);
    }
    
    // free the node
    if(node->numberOfChildren > 0)
        free(node->children);
    
    free(node->word);
}


// takes a pointer to a character array and converts each character in that array to lower case.
void strtolower(char * inString)
{
	int i;

	for(i = 0; inString[i]; i++)
	{
  		inString[i] = tolower(inString[i]);
	}
}