/*
15C_TEAM_PROJECT - Team 6
main.h - main header

*/

// #includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <crtdbg.h>
#include "queueADT.h"

// #defines
#define FLUSH while (getchar () != '\n')
#define MEM_ERR printf( "Not enough memory\n" ), exit(201)
#define BUCKETSIZE 3
#define INPUTFILE "test-packages.txt"
#define OUTPUTFILE "Output-packages.txt"
#define HASH_MAX 75

// Data Structures
typedef struct package {
	char *name;			// software package title � primary key
	char *version;		// version
	char *level;		// indicates license and level of support
	char *description;	// software description
} PACKAGE;

typedef struct hash {
	int buckets_used;
	PACKAGE *bucket[BUCKETSIZE];
} HASH;

typedef struct node {
	PACKAGE *ptrPackage;
	struct node *left;
	struct node *right;
} BSTNODE;

typedef struct header {
	int count;			// number of packages
	int rehashCount;
	int hashArySize;	// hash array size - should be a prime number
	int bucketSize;		// max number of buckets per hash
	int primaryBuckets;	// number of primary buckets used ie bucket 0
	HASH *hashAry;		// ptr to hash table
	BSTNODE *treeRoot;	// ptr to BST
} HEADER;

// Function Prototypes
// Driver functions
void printMenu( void );
void menuManager( HEADER* listHeader );
char getChar ( void );
HEADER* initHashBST ( void );
int insertPackage ( PACKAGE* );
HEADER* destory ( HEADER* listHeader );

void menu_AddPackage ( HEADER* listHeader );
void menu_DeletePackage ( HEADER* listHeader );
void menu_Search ( HEADER* listHeader );
void menu_ListUnsorted ( HEADER* listHeader );
void menu_ListSorted ( HEADER* listHeader );
void menu_PrintTree ( HEADER* listHeader );
void menu_WriteToFile ( HEADER* listHeader );
void menu_CalcEff ( HEADER* listHeader );

// Hash Functions
int djb2HAsh ( HEADER *listHeader, char *packageName );
void createHash ( HEADER* listHeader, int size );
int insertHash ( HEADER* listHeader, PACKAGE* package );
int deleteHash ( HEADER* listHeader, char *packageName );
PACKAGE* hashSearch ( HEADER* listHeader, char *packageName );
void listHash ( HEADER* listHeader, void (*process) (PACKAGE* package) );
void reHash ( HEADER* listHeader );
float loadFactor ( HEADER* listHeader );
HASH* destroyHash ( HEADER* listHeader );
int binarySearch (int  list[], int last, int target, int *locn);
void calcHashEff( HEADER* listHeader, float *loadFactor, int *longestBuckets, int *numberOfCollisions, int *rehashCount );

//BST Functions
BSTNODE*	BSTNODE_Create ( );
void		BST_Traverse (HEADER* listHeader, void (*process) (PACKAGE* package) );
void		BST_Traverse_BFT (HEADER* listHeader, void (*process) (PACKAGE* package));
int			BST_Insert (HEADER* listHeader, PACKAGE* package);
void		BST_Print (HEADER* listHeader);
int			comparePackage   (PACKAGE* pack1, PACKAGE* pack2);
void		listTree ( HEADER* listHeader );
void		printTree ( HEADER* listHeader );
int			BST_Count (HEADER* listHeader);
BSTNODE* destroyBST ( HEADER* listHeader );
int BST_Delete (HEADER* listHeader, char* dltKey);

// File I/O Functions
void loadData ( HEADER* listHeader );
PACKAGE*	allocatePackage( char *packageNameTemp, char *versionTemp, char* levelTemp, char *descriptionTemp);
int			parseLine (char *line, char *packageNameTemp, char *versionTemp, char *levelTemp, char *descriptionTemp);
void		writeFile ( PACKAGE* ptrPackage );
void		startWriteFile ( HEADER* listHeader );

// Screen Output Functions
void printPackage ( PACKAGE* ptrPackage );
void userPackage (char* searchName );
void printEff ( HEADER* listHeader );