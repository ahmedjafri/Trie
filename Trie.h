/* Ahmed Jafri
 * Assignment 5
 * March 3, 2014
 * Trie.h 
 *
 * This header handles all of the functions relating to populating and traversing the trie. 
 *
 */

#include <stdio.h> 
#define OCTOTHORPE -1


typedef struct TrieNode TrieNode;

struct TrieNode
{
	TrieNode * 		parent;
	TrieNode *  	children;
	int 			numberOfChildren;
	int 			number;
    char *          word;
};

void initTrie(TrieNode * inHead);

// word->number sequence->traverse and add to trie
void addWord(TrieNode * inHead, const char * inWord);

// populate the tree with the given file handle
void populateTrie(TrieNode * inHead, FILE * inFileHandle);

// clean up the buffer by removing the new line character
void clearNewline(char * inBuffer);

// convert the string to lowercase
void strtolower(char * inString);

// find a word in the trie and return the node
TrieNode* lookupWord(TrieNode * inHead, char* inNumberSequence, int *outOctothorpeLocation);

// clean up the given character string to remove whitespace
char* trimWhitespace(char *inString);

// find the given child of the node otherwise return NULL
TrieNode* findNode(TrieNode * node, int number);

// free up the allocated memory in the tree
void cleanupTrie(TrieNode * inHead);
