/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 5 - Binary Search Tree
    28 October 2013

*****************************************************/

#include "BSTree.h"

using namespace std;

bool BSTree::IsEmpty() const
{
    return (root==NULL);
}

BSTree::BSTree ( void )
{
    root = NULL;
}

// Public Delete
BSTree::~BSTree ()
{
    _Destroy(root);
}

unsigned BSTree::Depth ( void ) const
{
    if ( IsEmpty() ) return 0;
    else return _Depth(root);
}

// Public Find
Record BSTree::Find (const KeyType& key) const
{
    return _Find(key, root);
}

// Public Insert
// Takes care of establishing root or calling member function.
void BSTree::Insert( const Record& rec)
{
    if (root != NULL)   // Tree has already been established.
        _Insert(rec, root);
    else                // Root node has not been created - current node is new root.
        root = new node(rec);
}

void BSTree::InOrderTraversal ( void (*operate) (const Record&))
{
    if ( !IsEmpty() )
        _InOrderTraversal( operate, root);
}

void BSTree::PreOrderTraversal ( void (*operate) (const Record&))
{
    if ( !IsEmpty() )
        _PreOrderTraversal(operate, root);
}

void BSTree::PostOrderTraversal ( void (*operate) (const Record&))
{
    if ( !IsEmpty() )
        _PostOrderTraversal(operate, root);
}

/** Private Functions **/
/*********************************************/

// Private Delete
// Traverses tree, recursively deleting left, then right, then parent leaves.
void BSTree::_Destroy (node* current)
{
    if (current != NULL)
    {
        _Destroy(current->left_child);
        _Destroy(current->right_child);
        delete current;
    }
}

// Recursively traverse the tree until key is found, return NULL if not found.
Record BSTree::_Find(const KeyType& key, node* current ) const
{
    if (current == NULL)
        return Record("KNF", "KEY NOT FOUND");
    else
    {
        if (current->data.Key() == key)             // Found
            return current->data;
        else if (key < current->data.Key())         // Continue right
            return _Find(key, current->left_child);
        else    //key >= current                    // Continue left
            return _Find(key, current->right_child);
    }
}

// Private Insert
// Recursively traverses tree and places record.
void BSTree::_Insert( const Record& rec, node* current)
{
    // Find out which direction we need to traverse to get to the current
    // node's proper position.

    if (rec >= current->data)               // Go to the right.
    {
        if (current->right_child != NULL)   // Continue to the right if possible
            _Insert(rec, current->right_child);
        else                                // Correct spot has been found.
            current->right_child = new node(rec);
    }

    else // rec < current->data. Go to the left.
    {
        if (current->left_child != NULL)
            _Insert(rec, current->left_child);
        else
            current->left_child = new node(rec);
    }
}

void BSTree::_InOrderTraversal ( void (*operate) (const Record&), node* current)
{
    if (current->left_child)
        _InOrderTraversal(operate, current->left_child);

    operate (root->data);

    if (current->right_child)
        _InOrderTraversal(operate, current->right_child);
}

void BSTree::_PreOrderTraversal ( void(*operate) (const Record&), node* current)
{
    operate (current->data);

    if (current->left_child)
        _PreOrderTraversal(operate, current->left_child);
    if (current->right_child)
        _PreOrderTraversal(operate, current->right_child);
}

void BSTree::_PostOrderTraversal( void (*operate) (const Record&), node* current)
{
    if (current->left_child)
        _PostOrderTraversal(operate, current->left_child);
    if (current->right_child)
        _PostOrderTraversal(operate, current->right_child);

    operate(current->data);
}

unsigned BSTree::_Depth(node* current) const
{
    if (current == NULL)
        return 0;
    else
    {
        int left_depth = _Depth(current->left_child);
        int right_depth = _Depth(current->right_child);
        return ( (left_depth > right_depth) ? left_depth + 1 : right_depth + 1 );
    }
}

// Extra Credit.
void BSTree::Delete (const KeyType& key)
{
    if ( !IsEmpty() )
    {
        // Complicated Stuff.
    }
}
