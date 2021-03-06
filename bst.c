/* BST Libary Functions */

// #includes
#include "main.h"

// Private Use Functions
static BSTNODE* _insert (HEADER* listHeader, BSTNODE* root, BSTNODE* newPackage);
static void _traverse (BSTNODE* root, void (*process) (PACKAGE* package) );
static void _traverseBFT (BSTNODE* root, void (*process) (PACKAGE* package) );
static void _destroyBST ( BSTNODE* root );
void _print (BSTNODE *root, int   level);
static BSTNODE* _delete (HEADER* listHeader, BSTNODE* root,  char* dataPtr, int* success);

/*	====================== comparePackage======================  
	Compare two package name's and return low, equal, high.
	    Pre  pack1 and pack2 are valid pointers to packages
	    Post return low (-1), equal (0), or high (+1)
*/
int  comparePackage   (PACKAGE* pack1, PACKAGE* pack2)
{
//	Local Definitions 
	int compared;

//	Statements 
	compared = strcmp(pack1->name, pack2->name);
	if ( compared < 0)
	      return -1;
	     
	if ( compared == 0)
	      return 0;

	return +1;
}	//end comparePackage

/*	================= BSTNODE_Create ===================
	This function creates a new BSTNODE to be inserted.
	   Pre    nothing
	   Post   newNode
	   Return Success (true) or Overflow (false)
*/
BSTNODE* BSTNODE_Create ( )
{
	BSTNODE* newNode;

	newNode = (BSTNODE*) malloc(sizeof(BSTNODE));
	if(!newNode)
		MEM_ERR;

	newNode->left = NULL;
	newNode->ptrPackage = NULL;
	newNode->right = NULL;

	return newNode;
} // BSTNODE_Create

/*	================= BST_Insert ===================
	This function inserts new packages into the tree.
	   Pre    listHedaer - header containing pointer to BST
	   Post   package inserted or memory overflow 
	   Return Success (true) or Overflow (false)
*/
int BST_Insert (HEADER* listHeader, PACKAGE* package)
{
	BSTNODE* newNode;

	newNode = BSTNODE_Create();
	newNode->ptrPackage = package;

	if (listHeader->treeRoot == NULL)
		listHeader->treeRoot = newNode;

	else
		_insert(listHeader, listHeader->treeRoot, newNode);
	    
	return 1;
}// BST_Insert 

/*	==================== _insert ====================
	This function uses recursion to insert the new data 
	into a leaf node in the BST tree.
	   Pre    Application has called BST_Insert, which  
	          passes root and data pointer
	   Post   Data have been inserted
	   Return pointer to [potentially] new root
*/
static BSTNODE* _insert (HEADER* listHeader, BSTNODE* root, BSTNODE* newPackage)
{
	if(!root)
		return newPackage;

	// Locate null subtree for insertion 
	if (comparePackage(root->ptrPackage, newPackage->ptrPackage) > 0)
	{
		root->left = _insert(listHeader, root->left, newPackage);
	    return root; 
	}     // new < node
	else
	{ // new data >= root data 		  
	    root->right = _insert(listHeader, root->right, newPackage);
	    return root;
	} // else new data >= root data 


	return root;
}// _insert


/*	=================== BST_Traverse =================== 
	Process tree using inorder traversal. 
	   Pre   Tree has been created (may be null) 
	         process visited package during traversal 
	   Post  Pacakge processed in LNR (inorder) sequence 
*/
void BST_Traverse (HEADER* listHeader, void (*process) (PACKAGE* package) ) 
{
	if(listHeader->treeRoot)
		_traverse (listHeader->treeRoot, process);
	return;
} // end BST_Traverse 

/*	=================== _traverse =================== 
	Inorder tree traversal. To process a node, we use 
	the function passed when traversal was called.
	   Pre   Tree has been created (may be null) 
	   Post  All nodes processed 
*/
static void _traverse (BSTNODE* root, void (*process) (PACKAGE* package)) 
{
    if (root)
	{
		_traverse (root->left, process);
		process ( root->ptrPackage );
        _traverse (root->right, process); 
    }
    return;
}// _traverse

/*  ============================= BST_Print ============================= 
	This function prints the BST tree by calling a recursive inorder 
	traversal.
		Pre:	Tree must be initialized. Null tree is OK.
				Level is node level: root == 0
		Post:	Tree has been printed.
*/
void BST_Print (HEADER* listHeader) 
{
	_print (listHeader->treeRoot, 0);
    return;
}   // AVL_PRINT 

/*  ============================= _print ============================= 
	This function uses recursion to print the tree. At each level, the 
    level number is printed along with the node contents.
    Pre		root is the root of a tree or subtree
            level is the level of the tree: tree root is 0
    Post    Tree has been printed.
*/
void _print (BSTNODE *root, int   level) 
{
 	int i;
 	
  	if ( root )
 	{
		_print ( root->right, level + 1 );
		for (i = 0; i <= level; i++ )
 			printf (" " );
		printf( "%d: %s\n", level, root->ptrPackage->name  );
		_print ( root->left, level + 1 );
 	} 

	return;
 } 

/*	=================== BST_Count ==================
	Returns number of nodes in tree.
	   Pre     tree has been created 
	   Returns tree count 
*/
int BST_Count (HEADER* listHeader)
{
	return (listHeader->count);
}// BST_Count 

/* ============================ destroyBST =======================
	Calls recursive traversal to free packages and nodes
	   PRE  : listHeader - ptr to HEADER
	   POST : frees bst
	   RETURNS : NULL
*/
BSTNODE* destroyBST ( HEADER* listHeader )
{
	if(listHeader->treeRoot)
		_destroyBST (listHeader->treeRoot);
	return NULL;
}

/* ============================ _destroyBST =======================
	Recursive traversal to free packages and nodes
	   PRE  : listHeader - ptr to HEADER
	   POST : frees package, package data, and bst nodes
	   RETURNS :
*/
static void _destroyBST ( BSTNODE* root ) 
{
	if ( root )
 	{
		_destroyBST (root->left);
		free ( root->ptrPackage->name );
		free ( root->ptrPackage->description );
		free ( root->ptrPackage->level );
		free ( root->ptrPackage->version );
		free ( root->ptrPackage );
        _destroyBST (root->right);
		free ( root );
 	} 

}


/*  =================== BST_Traverse_BFT =================== 
	Process tree using Breadth First traversal. 
	Pre   Tree has been created (may be null) 
	process visited packages during traversal 
	Post  Package processed in Breadth First sequence 
*/
 	
void BST_Traverse_BFT (HEADER* listHeader, void (*process) (PACKAGE* package)) 
{
	_traverseBFT (listHeader->treeRoot, process);
	return;
} // end BST_Traverse
	
/*  =================== _traverseBFT =================== 
	Breadth First tree traversal. To process a node, we use 
	a pointer to a process function.
	Pre   Tree has been created (may be null) 
	Post  All nodes processed 
 	
*/

static void _traverseBFT (BSTNODE* root, void (*process) (PACKAGE* package) )
{
	BSTNODE* currentNode;
	BSTNODE* tempNode;
	QUEUE* queue;

	queue = createQueue();
	if(!queue)
	{
		printf("\nMemory Overflow!\n");
		exit(201);
	}
	currentNode = root;

	while(currentNode != NULL)
	{
		process ( currentNode->ptrPackage );
		if(currentNode->left != NULL)
			enqueue(queue, currentNode->left);
		if(currentNode->right != NULL)
			enqueue(queue, currentNode->right);
		if(!emptyQueue(queue))
		{
			dequeue(queue, (void**)&tempNode);
			currentNode = tempNode;
		}
		else currentNode = NULL;
	}
	queue = destroyQueue(queue);
	return;

}// _traverseBFT

/* ================== BST_Delete ================== 
	This function deletes a node from the tree and 
	rebalances it if necessary. 
	   Pre    tree initialized--null tree is OK
	          dltKey is pointer to data structure 
	                 containing key to be deleted 
	   Post   node deleted and its space recycled 
	          -or- An error code is returned 
	   Return Success (true) or Not found (false)
*/
int BST_Delete (HEADER* listHeader, char* dltKey)
{
	int  success;
	BSTNODE* newRoot;
	
	newRoot = _delete (listHeader, listHeader->treeRoot, dltKey, &success);
	if (success){
		listHeader->treeRoot = newRoot;
	    (listHeader->count)--;
	    if (listHeader->count == 0) // Tree now empty 
			listHeader->treeRoot = NULL;
	} 
	return success;
}// BST_Delete

/*	==================== _delete ==================== 
	Deletes node from the tree (key must be unique!)
	   Pre    tree initialized--null tree is OK.
	          dataPtr contains key of node to be deleted
	   Post   node is deleted and its space recycled
	          -or- if key not found, tree is unchanged 
	   Return success is true if deleted; false if not found
	          pointer to root
*/
static BSTNODE* _delete (HEADER* listHeader, BSTNODE* root,  char* dataPtr, int* success)
{
	BSTNODE* dltPtr;
	BSTNODE* exchPtr;
	BSTNODE* newRoot;
	PACKAGE* holdPtr;

	if (!root){
	    *success = 0;
	    return NULL;
	}
	
	if (strcmp(dataPtr, root->ptrPackage->name) < 0)
	    root->left  = _delete (listHeader, root->left, dataPtr, success);
	else if (strcmp(dataPtr, root->ptrPackage->name) > 0)
	    root->right = _delete (listHeader, root->right, dataPtr, success);
	else{ // Delete node found--test for leaf node 
	    dltPtr = root;
		if (!root->left){         // No left subtree 
            //free (root->dataPtr);       // data memory
	        newRoot = root->right;
	        free (dltPtr);              // BST Node
	        *success = 1;
	        return newRoot;             // base case 
	     }
	     else
			 if (!root->right){   // Only left subtree 
	             newRoot = root->left;
	             free (dltPtr);
	             *success = 1;
	             return newRoot;         // base case 
	         }
			 else{ // Delete Node has two subtrees 
                 exchPtr = root->left;
	             // Find largest node on left subtree
	             while (exchPtr->right)
	                 exchPtr = exchPtr->right;

	              // Exchange Data 
	              holdPtr          = root->ptrPackage;
	              root->ptrPackage    = exchPtr->ptrPackage;
	              exchPtr->ptrPackage = holdPtr;
				  root->left = _delete (listHeader, root->left, exchPtr->ptrPackage->name, success);
			 }// else 
	}// node found 
	return root; 
}// _delete 