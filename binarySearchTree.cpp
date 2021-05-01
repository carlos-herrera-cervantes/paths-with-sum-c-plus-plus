#include <iostream>
#include <string>
#include <locale>
#include <unordered_map>
#include "treeNode.cpp"

using namespace std;

class BinarySearchTree
{

  Node *root;
  int length;

  /**
  * Prints the elements
  * @param node Node object class
  * @returns Void
  */
  void inorder(Node *node)
  {
    if (!node)
      return;

    cout << node->data << ": ";

    if (node->left)
      cout << "L" << node->left->data << " ";
    if (node->rigth)
      cout << "R" << node->rigth->data << " ";

    cout << endl;

    inorder(node->left);
    inorder(node->rigth);
  }

  /** Inserts a new node
  * @param node Node object class
  * @param value Number value
  * @returns Node object class
  */
  Node *insert(Node *node, int value)
  {
    if (!node)
    {
      node = new Node();
      node->data = value;
      node->left = node->rigth = NULL;
    }
    else if (value < node->data)
    {
      node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
      node->rigth = insert(node->rigth, value);
    }

    return node;
  }

  /**
   * Increment a key in the map
   * @param hashTable Map object class
   * @param key
   * @param delta Value for key
   */
  void incrementHash(unordered_map<int, int> *hashTable, int key, int delta)
  {
    auto iterator = hashTable->find(key);
    int newCount;

    if (iterator == hashTable->end())
    {
      newCount = delta;
    }
    else
    {
      newCount = hashTable->at(key) + delta;
    }

    if (newCount == 0)
    {
      hashTable->erase(iterator);
    }
    else
    {
      hashTable->emplace(key, newCount);
    }
  }

  /**
   * Counts the paths to perform a sum with values of the nodes
   * @param node Node object class
   * @param targetSum Quantity to reach
   * @param runningSum Accumulator
   * @param pathCount Map to store the paths
   * @returns Number of paths to get the sum
   */
  int countPathsWithSum(Node* node, int targetSum, int runningSum, unordered_map<int, int> *pathCount)
  {
    if (!node) return 0;

    runningSum += node->data;
    int sum = runningSum - targetSum;
    auto iterator = pathCount->find(sum);
    int totalPaths;

    iterator == pathCount->end() ? totalPaths = 0 : totalPaths = pathCount->at(sum);

    if (runningSum == targetSum) totalPaths++;

    incrementHash(pathCount, runningSum, 1);
    totalPaths += countPathsWithSum(node->left, targetSum, runningSum, pathCount);
    totalPaths += countPathsWithSum(node->rigth, targetSum, runningSum, pathCount);
    incrementHash(pathCount, runningSum, -1);

    return totalPaths;
  }

  public:

    BinarySearchTree()
    {
      root = NULL;
      length = 0;
    }

    /**
    * Prints the elements to the console
    * @returns Void
    */
    void print()
    {
      inorder(root);
      cout << endl;
    }

    /**
    * Inserts a new value
    * @param data Number value
    * @returns Void
    */
    void insert(int data)
    {
      root = insert(root, data);
      length++;
    }

    /**
     * Execute the process to count the paths to perform a sum with values of the nodes
     * @param targetSum Quantity to reach
     * @returns Number of paths to get the sum
     */
    int countPaths(int targetSum)
    {
      unordered_map<int, int> object;
      return countPathsWithSum(root, targetSum, 0, &object);
    }
};