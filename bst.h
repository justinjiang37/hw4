#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

using namespace std;
/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;

        // inOrder helper functions
        Node<Key, Value>* findMostLeft(Node<Key, Value>* current);
        Node<Key, Value>* findFirstLeftPointer(Node<Key, Value>* current);
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void insertHelper(Node<Key, Value>* current, 
                                    const std::pair<const Key, Value> &keyValuePair);
    void clearHelper(Node<Key, Value>* current);
    Node<Key, Value>* getSmallestNodeHelper(Node<Key, Value>* current) const;
    Node<Key, Value>* internalFindHelper(Node<Key, Value>* current, const Key& key) const;
    bool isBalancedHelper(Node<Key, Value>* current) const;
    static int getHeight(Node<Key, Value>* current);
    static Node<Key, Value>* findMostRight(Node<Key, Value>* current);
    static Node<Key, Value>* findFirstRightPointer(Node<Key, Value>* current);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if (current_ != nullptr) {
        // get from current_ -> essentially finding the successor
        if (current_->getRight() == nullptr) {
            // no right tree -> get parent to find first left pointer
            current_ = findFirstLeftPointer(current_);
        } else {
            // there is a right tree
            current_ = findMostLeft(current_->getRight());
        }
    }
    return *this;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::iterator::findMostLeft(Node<Key, Value>* current) {
    if (current == nullptr) {
        return nullptr;
    }

    if (current -> getLeft() != nullptr) {
        return findMostLeft(current->getLeft());
    } else {
        return current;
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::iterator::findFirstLeftPointer(Node<Key, Value>* current) {
    if (current == nullptr) { 
        return nullptr;
    }

    Node<Key, Value>* p = current->getParent();
    if (p == nullptr) {
      // at root
      return nullptr;
    }
    
    if (current == p->getLeft()) {
      // is a left child
      return p;
    } else {
        return findFirstLeftPointer(p);
    }
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // cout << "inserting" << endl;
    // TODO
    // cout << keyValuePair.first << endl;
    Node<Key, Value>* current = root_;
    Node<Key, Value>* parent = nullptr;

    if (root_ == nullptr) {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }

    while (current != nullptr) {
        // cout << "current node: " << current->getKey() << " " << current->getValue() << endl;
        parent = current;
        if (keyValuePair.first == current->getKey()) {
            // duplicate, replace value
            current->setValue(keyValuePair.second);
            return;
        }
        else if (keyValuePair.first > current->getKey()) {
            // go right
            current = current->getRight();
        }
        else {
            // cout << "HERE" << endl;
            // go left
            current = current->getLeft();
        } 
    }

    // cout << "Parent node: " << parent->getKey() << " " << parent->getValue() << endl;
    // cout << (current==nullptr) << endl;

    if (keyValuePair.first > parent->getKey()) {
        // cout << "HERE1" << endl;
        // set right
        Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
        parent->setRight(temp);
    }
    else if (keyValuePair.first < parent->getKey()) {
        // set left
        Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
        parent->setLeft(temp);
        // cout << "Parent node: " << parent->getKey() << " " << parent->getValue() << endl;
        // cout << "Parent left: " << parent->getLeft()->getKey() << " " << parent->getLeft()->getValue() << endl;
        // cout << "HERE2" << endl;
    } 
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // cout << "removing" << endl;
    // TODO
    // first find the node
    Node<Key, Value>* removeNode = internalFind(key);

    if (removeNode == nullptr) {
        return;
    }

    // cout << "removeNode: " << removeNode->getKey() << " " << removeNode->getValue() << endl;

    Node<Key, Value>* parent = removeNode -> getParent();
    // if no children
    if (removeNode -> getRight() == nullptr && removeNode -> getLeft() == nullptr) {
        if (parent == nullptr) {
            // remove node is the root
            root_= nullptr;
            // delete removeNode;
            return;
        }
        if (removeNode == parent->getLeft()) {
            parent->setLeft(nullptr);
        } else if (removeNode == parent->getRight()) {
            parent->setRight(nullptr);
        }
    }
    // cout << "Parent: " << parent->getKey() << " " << parent->getValue() << endl;
    // cout << "removeNode: " << removeNode->getKey() << " " << removeNode->getValue() << endl;
    // cout << "removeNode Right: " << removeNode->getRight()->getKey() << " " << removeNode->getRight()->getValue() << endl;
    // cout << "Parent: " << parent->getKey() << " " << parent->getValue() << endl;
    // cout << "Parent Right: " << parent->getRight()->getKey() << " " << parent->getRight()->getValue() << endl;
    // if removeNode only has right child
    else if (removeNode -> getRight() != nullptr && removeNode -> getLeft() == nullptr) {
        if (parent == nullptr) {
            // remove node is parent
            root_ = removeNode->getRight();
            removeNode->getRight()->setParent(nullptr);
        }
        else if (removeNode == parent->getRight()) {
            parent -> setRight(removeNode->getRight());
            removeNode->getRight()->setParent(parent);
        }
        else {
            parent -> setLeft(removeNode->getRight());
            removeNode->getRight()->setParent(parent);
        }
    }
    // if removeNode only has left child
    else if (removeNode -> getRight() == nullptr && removeNode -> getLeft() != nullptr) {
        if (parent == nullptr) {
            // remove node is parent
            root_ = removeNode->getLeft();
            removeNode->getLeft()->setParent(nullptr);
        }
        else if (removeNode == parent->getRight()) {
            parent -> setRight(removeNode->getLeft());
            removeNode->getLeft()->setParent(parent);
        }
        else {
            parent->setLeft(removeNode->getLeft());
            removeNode->getLeft()->setParent(parent);
        }
    } 
    // 2 children -> swap with predecessor
    else {
      Node<Key, Value>* pred = predecessor(removeNode);
      // cout << "Predecessor: " << pred->getKey() << " " << pred->getValue() << endl;
      nodeSwap(pred, removeNode);

      parent = removeNode->getParent();
      // if leaf node
      if (removeNode -> getRight() == nullptr && removeNode -> getLeft() == nullptr) {
          if (parent == nullptr) {
              // remove node is the root
              root_= nullptr;
              // delete removeNode;
              // return;
          }
          if (removeNode == parent->getLeft()) {
              parent->setLeft(nullptr);
          } else if (removeNode == parent->getRight()) {
              parent->setRight(nullptr);
          }
      }
      else {
      // only possible other case if remove node has left subtree
        if (parent == nullptr) {
            // remove node is parent
            root_ = removeNode->getLeft();
            removeNode->getLeft()->setParent(nullptr);
        }
        else if (removeNode == parent->getRight()) {
            parent -> setRight(removeNode->getLeft());
            removeNode->getLeft()->setParent(parent);
        }
        else {
            parent->setLeft(removeNode->getLeft());
            removeNode->getLeft()->setParent(parent);
        }
    }
  }

  delete removeNode;
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current -> getLeft() != nullptr) {
        // recurse to right most node of left subtree
        return findMostRight(current->getLeft());
    } else {
        return findFirstRightPointer(current->getParent());
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findMostRight(Node<Key, Value>* current) {
  if (current == nullptr) {
    return nullptr;
  }

  if (current->getRight()!=nullptr) {
      return findMostRight(current->getRight());
  } else {
      return current;
  }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findFirstRightPointer(Node<Key, Value>* current) {
    if (current == nullptr) {
      return nullptr;
    }

    Node<Key, Value>* p = current->getParent();
    if (p == nullptr) {
      // at root
      return nullptr;
    }
    if (current == p->getRight()) {
        // is a right child
        return p;
    } else {
        return findFirstRightPointer(p);
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearHelper(root_);
    root_ = nullptr;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* current) {
    // delete left and right then itself -> post order deletion
    if (current == nullptr) {
        return;
    }
    clearHelper(current -> getLeft());
    clearHelper(current -> getRight());
    delete current;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    return getSmallestNodeHelper(root_);
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNodeHelper(Node<Key, Value>* current) const {
    if (current == nullptr) {
        return nullptr;
    }
    if (current -> getLeft() == nullptr) {
        return current;
    } else {
        return getSmallestNodeHelper(current->getLeft());
    }
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    return internalFindHelper(root_, key);
}

// DEFINE
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFindHelper(Node<Key, Value>* current, const Key& key) const {
    // if no node with key
    if (current == nullptr) {
        return nullptr;
    }
    // if the current node key is key, then return
    else if (current->getKey() == key) {
        return current;
    } 
    // if key is greater than current node key
    else if (key >= current->getKey()) {
        return internalFindHelper(current -> getRight(), key);
    } 
    // key is less than current
    else {
        return internalFindHelper(current -> getLeft(), key);
    }
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return isBalancedHelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* current) const {
    // recursively check each height at each level
    if (current == nullptr) {
        // if points to null, false
        return true;
    }

    // get left height
    int leftHeight = getHeight(current->getLeft());
    // get right height
    int rightHeight = getHeight(current->getRight());

    // check if balanced
    if (abs(leftHeight - rightHeight) > 1) {
        // if at any point is false, the && below will return false on root
        return false;
    } else {
        // recurse left and right
        return (isBalancedHelper(current -> getLeft()) && 
        isBalancedHelper(current -> getRight()));
    }


}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value>* current) {
    if (current == nullptr) {
        return 0;
    }
    int left = getHeight(current->getLeft());
    int right = getHeight(current->getRight());
    // find max
    if (left > right) {
        return left + 1;
    } else {
        return right + 1;
    }
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
