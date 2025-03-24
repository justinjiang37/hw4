#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;

// global var to keep track of all leaf depth
int uniDepth = -500;

// You may add any prototypes of helper functions here
// helper function, need node, current depth, and universal depth
bool equalPathsUtil(Node * curr, int depth) {
    // handle null ptr case
    if (curr == nullptr) {
        return true;
    }

    // if leaf node, check if same with other elaf deapth
    if (curr->left == nullptr && curr->right == nullptr) {
        // check if its the first time uniDepth is updated
        if (uniDepth < 0) {
            uniDepth = depth;
        }
        return uniDepth == depth;
    }

    // not leaf node, increase depth and check left and right sub tree
    return equalPathsUtil(curr->left, depth + 1) && equalPathsUtil(curr->right, depth + 1);
}


bool equalPaths(Node * root)
{
    // Add your code below
    // base case -> if null, return true
    if (root == nullptr) {
        return true;
    }

    uniDepth = -500;
    // track depth with each call
    // if leaf node -> check with a var for universal depth
    // depth at root is 0 and give dummy var to indicate first depth recording
    return equalPathsUtil(root, 0);
}

