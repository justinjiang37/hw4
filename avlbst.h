#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    virtual void removeFix(AVLNode<Key,Value>* n, int diff);
    virtual void rotateRight(AVLNode<Key,Value>* g);
    virtual void rotateLeft(AVLNode<Key,Value>* g);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // if empty -> set n as root, b(n) = 0
    if (this->root_ == nullptr) {
      this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
      static_cast<AVLNode<Key, Value>*>(this->root_)->setBalance(0);
      return;
    }

    // walk to a leaf, p, and inserting new node as its child, set balance to 0, look at parent
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (new_item.first == current->getKey()) {
        current->setValue(new_item.second);
        return;
      }
      else if (new_item.first > current->getKey()) {
        // go right
        current = current->getRight();
      }
      else {
        // go left
        current = current->getLeft();
      }    
    }

    AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
    // insert new child
    if (new_item.first > parent->getKey()) {
      // AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
      temp->setBalance(0);
      parent->setRight(temp);
    }
    else if (new_item.first < parent->getKey()) {
      // AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
      temp->setBalance(0);
      parent->setLeft(temp);
    }

    // if b(p) was -1, then = 0
    // if b(p) was 1, then = 0
    if (parent->getBalance() == -1 || parent->getBalance() == 1) {
      parent->setBalance(0);
    }
    // if was 0, call insertFix
    else if (parent->getBalance() == 0) {
      // if add new node to the left of parent
      if (temp == parent->getLeft()) {
        parent->updateBalance(-1);
      }
      else {
        parent->updateBalance(1);
      }
      // cout << static_cast<int>(parent->getBalance()) << endl;
      insertFix(parent, temp);
    }
    
    // cout << "HERERERE" << endl;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n) {
  if (p == nullptr || p->getParent() == nullptr) {
    return;
  }

  AVLNode<Key, Value>* g = p->getParent();
  // cout << g->getKey() << endl;
  // cout << p->getKey() << endl;
  // cout << n->getKey() << endl;

  // Assuming p is the left child of g
  if (g->getLeft() == p) {
    g->updateBalance(-1);
    // cout << static_cast<int>(g->getBalance()) << endl;
    if (g->getBalance() == 0) {
      return;
    }
    else if (g->getBalance() == -1) {
      insertFix(g, p);
    }
    else if (g->getBalance() == -2) {
      // if zig-zig
      if (p->getLeft() == n) {
        // cout << "here" << endl;
        rotateRight(g);
        p->setBalance(0);
        g->setBalance(0);
      }
      // if zig-zag
      else if (p->getRight() == n) {
        rotateLeft(p);
        rotateRight(g);
        if (n->getBalance() == -1) {
          p->setBalance(0);
          g->setBalance(1);
          n->setBalance(0);
        }
        else if (n->getBalance() == 0) {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else if (n->getBalance() == 1) {
          p->setBalance(-1);
          g->setBalance(0);
          n->setBalance(0);
        }
      }
    } 
  }
  else if (g->getRight() == p) {

    g->updateBalance(1);
    // cout << "HI" << endl;
    if (g->getBalance() == 0) {
      return;
    }
    else if (g->getBalance() == 1) {
      insertFix(g, p);
    }
    else if (g->getBalance() == 2) {
      // if zig-zig
      if (p->getRight() == n) {
        // cout << "here" << endl;
        rotateLeft(g);
        p->setBalance(0);
        g->setBalance(0);
      }
      // if zig-zag
      else if (p->getLeft() == n) {
        // cout << "here" << endl;
        rotateRight(p);
        rotateLeft(g);
        // cout << static_cast<int>(g->getBalance()) << endl;
        // cout << static_cast<int>(p->getBalance()) << endl;
        // cout << static_cast<int>(n->getBalance()) << endl;
        if (n->getBalance() == 1) {
          p->setBalance(0);
          g->setBalance(-1);
          n->setBalance(0);
        }
        else if (n->getBalance() == 0) {
          // cout << "here" << endl;
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
          // cout << static_cast<int>(g->getBalance()) << endl;
          // cout << static_cast<int>(p->getBalance()) << endl;
          // cout << static_cast<int>(n->getBalance()) << endl;
        }
        else if (n->getBalance() == -1) {
          p->setBalance(1);
          g->setBalance(0);
          n->setBalance(0);
        }
        // cout << "here" << endl;
      }
    } 
  }
} 

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* g) {
  // cout << "in here" << endl;
  AVLNode<Key, Value>* p = g->getLeft();
  // cout << g->getKey() << endl;
  // cout << p->getKey() << endl;
  // AVLNode<Key, Value>* n = p->getLeft();

  if (g->getParent() == nullptr) {
    // update parents
    p->setParent(g->getParent());
    g->setParent(p);

    // update children
    g->setLeft(p->getRight());
    if (p->getRight() != nullptr) {
      p->getRight()->setParent(g);
    }
    p->setRight(g);

    this->root_ = p;
  }

  else {
    if (g->getParent()->getLeft() == g) {
      // update parents
      p->setParent(g->getParent());
      g->getParent()->setLeft(p);
      g->setParent(p);

      // update children
      g->setLeft(p->getRight());
      if (p->getRight() != nullptr) {
        p->getRight()->setParent(g);
      }
      p->setRight(g);
    }
    else {
      // update parents
      p->setParent(g->getParent());
      g->getParent()->setRight(p);
      g->setParent(p);

      // update children
      g->setLeft(p->getRight());
      if (p->getRight() != nullptr) {
        p->getRight()->setParent(g);
      }
      p->setRight(g);
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* g) {
  AVLNode<Key, Value>* p = g->getRight();
  // AVLNode<Key, Value>* n = p->getRight();

  // cout << g->getKey() << endl;
  // cout << p->getKey() << endl;

  if (g->getParent() == nullptr) {
    // cout << "in here" << endl;
    // update parents
    p->setParent(g->getParent());
    g->setParent(p);

    // update children
    g->setRight(p->getLeft());
    if (p->getLeft() != nullptr) {
      p->getLeft()->setParent(g);
    }
    p->setLeft(g);

    this->root_ = p;
  }

  else {
    if (g->getParent()->getRight() == g) {
      // update parents
      p->setParent(g->getParent());
      g->getParent()->setRight(p);
      g->setParent(p);

      // update children
      g->setRight(p->getLeft());
      if (p->getLeft() != nullptr) {
        p->getLeft()->setParent(g);
      }
      p->setLeft(g);
    }
    else {
      // cout << "HERERER" << endl;
      // update parents
      p->setParent(g->getParent());
      g->getParent()->setLeft(p);
      g->setParent(p);

      // update children
      g->setRight(p->getLeft());
      if (p->getLeft() != nullptr) {
        p->getLeft()->setParent(g);
      }
      p->setLeft(g);
    }
  }
}
/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    if ((this->root_) == nullptr) {
      return;
    }
    // internalFind to get the node
    AVLNode<Key, Value>* removeNode = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::internalFind(key));
    AVLNode<Key, Value>* parent;
    int diff;
    // AVLNode<Key, Value>* root = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_);

    if (removeNode == nullptr) {
      return;
    }

    // if removeNode has 2 child, swape with pred first
    // now removeNode can ONLY have 0 or 1 child
    if (removeNode->getLeft() != nullptr && removeNode->getRight() != nullptr) {
      AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::predecessor(removeNode));
      nodeSwap(pred, removeNode);
    }

    parent = removeNode->getParent();

    // update balance
    if (parent != nullptr) {
      if (removeNode == parent->getLeft()) {
        diff = 1;
        // parent->updateBalance(1);
      }
      else if (removeNode == parent->getRight()) {
        diff = -1;
        // parent->updateBalance(-1);
      }
    }

    // delete removeNode
    // if a leaf node with 0 child
    if (removeNode->getLeft() == nullptr && removeNode->getRight() == nullptr) {
      if (parent == nullptr) {
        // removeNode is root
        // cast to AVL
        (this->root_) = nullptr;
        return;
      }
      if (removeNode == parent->getLeft()) {
        parent->setLeft(nullptr);
      } 
      else if (removeNode == parent->getRight()) {
        parent->setRight(nullptr);
      }
    }
    // if it has a right child 
    else if (removeNode -> getRight() != nullptr && removeNode -> getLeft() == nullptr) {
      if (parent == nullptr) {
        // remove node is root and is a parent
        (this->root_) = removeNode->getRight();
        removeNode->getRight()->setParent(nullptr);
      }
      else if (removeNode == parent->getRight()) {
        parent->setRight(removeNode->getRight());
        removeNode->getRight()->setParent(parent);
      }
      else {
        parent->setLeft(removeNode->getRight());
        removeNode->getRight()->setParent(parent);
      }
    }
    // if only as left child
    else if (removeNode -> getRight() == nullptr && removeNode -> getLeft() != nullptr) {
      if (parent == nullptr) {
        // remove node is root and is a parent
        (this->root_) = removeNode->getLeft();
        removeNode->getLeft()->setParent(nullptr);
      }
      else if (removeNode == parent->getRight()) {
        parent->setRight(removeNode->getLeft());
        removeNode->getLeft()->setParent(parent);
      }
      else {
        parent->setLeft(removeNode->getLeft());
        removeNode->getLeft()->setParent(parent);
      }
    }
  
  delete removeNode;
  removeFix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int diff) {
  int ndiff;

  if (n == nullptr) {
    return;
  }

  AVLNode<Key, Value>* p = n->getParent();
  if (p != nullptr) {
    if (n == p->getLeft()) {
      ndiff = 1;
    }
    else {
      ndiff = -1;
    }
  }

  // Assuming diff = -1
  if (diff == -1) {
    // Case 1
    if (n->getBalance() + diff == -2) {
      AVLNode<Key, Value>* c = n->getLeft();
      if (c->getBalance() == -1) {
        // zig-zig
        rotateRight(n);
        n->setBalance(0);
        c->setBalance(0);

        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0) {
        rotateRight(n);
        n->setBalance(-1);
        c->setBalance(1);
        return;
      }
      else if (c->getBalance() == 1) {
        AVLNode<Key, Value>* g = c->getRight();
        rotateLeft(c);
        rotateRight(n);

        if (g->getBalance() == 1) {
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0) {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if (g->getBalance() == -1) {
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }

        removeFix(p, ndiff);
      }
    }
    // Case 2
    else if (n->getBalance() + diff == -1) {
      n->setBalance(-1);
      return;
    }
    else if (n->getBalance() + diff == 0) {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
  else if (diff == 1) {
    // Case 1
    if (n->getBalance() + diff == 2) {
      AVLNode<Key, Value>* c = n->getRight();
      if (c->getBalance() == 1) {
        // zig-zig
        rotateLeft(n);
        n->setBalance(0);
        c->setBalance(0);

        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0) {
        rotateLeft(n);
        n->setBalance(1);
        c->setBalance(-1);
        return;
      }
      else if (c->getBalance() == -1) {
        AVLNode<Key, Value>* g = c->getLeft();
        rotateRight(c);
        rotateLeft(n);

        if (g->getBalance() == -1) {
          n->setBalance(0);
          c->setBalance(1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0) {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if (g->getBalance() == 1) {
          n->setBalance(-1);
          c->setBalance(0);
          g->setBalance(0);
        }

        removeFix(p, ndiff);
      }
    }
    // Case 2
    else if (n->getBalance() + diff == 1) {
      n->setBalance(1);
      return;
    }
    else if (n->getBalance() + diff == 0) {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
