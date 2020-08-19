/**
* Title: AVL Trees
* Author: Atay Kaylar
* ID: 21703284
* Assignment: 4
* Description: Header file
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

class TreeNode
{ // node in the tree
private:
    TreeNode()
    {
        item = "";
        leftChildPtr = NULL;
        rightChildPtr = NULL;
        height = 1;
        count = 0;
    }
    TreeNode(string &nodeItem, TreeNode *left, TreeNode *right)
    {
        item = nodeItem;
        leftChildPtr = left;
        rightChildPtr = right;
        height = 1;
        count = 0;
    }
    string item; // data portion
    int count;
    int height;
    TreeNode *leftChildPtr;  // pointer to left child
    TreeNode *rightChildPtr; // pointer to right child
    friend class AVLTree;
};

class AVLTree
{
public:
    AVLTree();
    ~AVLTree();
    void destroyTree(TreeNode *&treePtr);
    TreeNode*  addWord(TreeNode *node,string item);
    void generateTree(ifstream &input);
    void printHeight(ostream &file);
    void printStandartDeviation(ostream &file);
    void printStandartDeviationHelper(TreeNode* nodePtr,float &freqCount);
    void printStandartDeviationHelper2(TreeNode *nodePtr, float &mean, float &sdHelp);
    void printStatistics(ostream &file);
    void printWordCount(ostream &file);
    int returnWordCount();
    void printWordCountHelper(int &count, TreeNode* nodePtr);
    void printMostFrequent(ostream& file)const;
    void printMostFrequentHelper(string& mostWord, int &mostWordNumber, TreeNode *nodePtr)const;
    void printLeastFrequent(ostream& file)const;
    void printLeastFrequentHelper(string& leastWord, int &leastWordNumber, TreeNode *nodePtr)const;

    TreeNode* rightRotate(TreeNode *&t);
    TreeNode* leftRotate(TreeNode *&t);
    TreeNode* doubleLeftRotate(TreeNode* &t);
    TreeNode* doubleRightRotate(TreeNode* &t);
    int getBalance(TreeNode *N);
    int max(int a, int b) const;
    int height(TreeNode *N);
    void generateTree(string fileName, int n);
    void writeFile(ostream& file);
    void writeFileHelper(ostream& file, TreeNode* nodePtr);
    void printWordFrequencies(ostream& file) const;
    void printWordFrequenciesHelper(ostream& file, TreeNode* nodePtr) const;
    TreeNode* returnRoot()const;

private:
    TreeNode *root;
    ostream &print(ostream &out);
    ostream &printHelper(ostream &out, TreeNode *rootPtr);
    friend ostream &operator<<(ostream &out, AVLTree &tree);
    bool isCompleteHelper(TreeNode *rootPtr, int indx, int totalNodes);
    bool isFullHelper(TreeNode *subTreePtr);
    int totalNodes(TreeNode *rootPtr);
};
