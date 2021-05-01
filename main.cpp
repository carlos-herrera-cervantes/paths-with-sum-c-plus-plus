#include <iostream>
#include "binarySearchTree.cpp"

using namespace std;

int main()
{
    BinarySearchTree binaryTree;

    binaryTree.insert(10);
    binaryTree.insert(5);
    binaryTree.insert(3);
    binaryTree.insert(1);
    binaryTree.insert(7);
    binaryTree.insert(12);

    int target = 22;
    binaryTree.print();

    int paths = binaryTree.countPaths(target);
    cout << "The number of paths to get " << target << " are: " << paths;

    return 0;
}