#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<int, int> bt;
    bt.insert(std::make_pair(5,5));
    bt.insert(std::make_pair(7,7));
    bt.insert(std::make_pair(6,6));
    bt.insert(std::make_pair(8,8));
    bt.insert(std::make_pair(2,2));
    bt.insert(std::make_pair(4,4));
    bt.insert(std::make_pair(3,3));
    bt.insert(std::make_pair(1,1));

    bt.print();


    bt.remove(2);
    bt.print();
    bt.remove(1);
    bt.print();
    bt.remove(5);
    bt.print();
    bt.remove(4);
    bt.print();
    bt.remove(5);
    bt.print();
    bt.remove(6);
    bt.print();
    bt.remove(7);
    bt.print();
    bt.remove(8);
    bt.print();

    return 0;
    // cout << "Binary Search Tree contents:" << endl;
    // BinarySearchTree<int, int>::iterator it = bt.begin();
    // // cout << "Hello" << endl;
    // // bt.print();
    // for(BinarySearchTree<int, int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find(4) != bt.end()) {
    //     cout << "Found 4" << endl;
    // }
    // else {
    //     cout << "Did not find 4" << endl;
    // }
    // cout << "Erasing 4" << endl;
    // bt.remove('4');
    // bt.print();

    // AVL Tree Tests
    AVLTree<int,int> at;
    at.insert(std::make_pair(6,6));
    at.insert(std::make_pair(3,3));
    at.insert(std::make_pair(1,1));
    at.insert(std::make_pair(4,4));
    at.insert(std::make_pair(7,7));
    at.insert(std::make_pair(9,9));
    at.insert(std::make_pair(8,8));
    at.insert(std::make_pair(10,10));


    at.remove(7);
    at.print();

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    return 0;
}
