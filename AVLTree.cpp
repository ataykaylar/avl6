/**
* Title: AVL Trees
* Author: Atay Kaylat
* ID: 21703284
* Assignment: 4
* Description: Implementation of the header
*/


#include "AVLTree.h"

AVLTree::AVLTree()
{
    root = NULL;
}

void AVLTree::printStatistics(ostream &file)
{
    printWordCount(file);
    printHeight(file);
    printMostFrequent(file);
    printLeastFrequent(file);
    printStandartDeviation(file);
}


void AVLTree::printWordCount(ostream &file) 
{
    int wordCount = 0;
    printWordCountHelper(wordCount, root);
    file << "Total Word Count: "<<wordCount << endl;
}

void AVLTree::printWordCountHelper(int &count, TreeNode *nodePtr) 
{
    if (nodePtr != NULL)
    {
        count++;
        printWordCountHelper(count, nodePtr->leftChildPtr);
        printWordCountHelper(count, nodePtr->rightChildPtr);
    }
}

int AVLTree::returnWordCount()
{
    int wordCount = 0;
    printWordCountHelper(wordCount, root);
    return wordCount;
}

void AVLTree::printHeight(ostream &file)
{
  file<<"Tree Height: "<<height(root)<<endl;
}

void AVLTree::printStandartDeviation(ostream &file)
{
    
    float sum = 0.0;
    float mean, standardDeviation = 0.0;
    stringstream temp;
    
    printStandartDeviationHelper(root, sum);
    
    mean = sum / returnWordCount();
    printStandartDeviationHelper2(root, mean, standardDeviation);
    float sd=  sqrt(standardDeviation / returnWordCount());
    temp << sd;
    string sdString = temp.str();
    file << "Standard Deviation is  "<< sdString << "."<<endl;
}

void AVLTree::printStandartDeviationHelper2(TreeNode *nodePtr, float &mean, float &sdHelp)
{
    if (nodePtr != NULL)
    {
        
        sdHelp =sdHelp+ pow(nodePtr->count - mean, 2);
        printStandartDeviationHelper2(nodePtr->leftChildPtr, mean, sdHelp);
        printStandartDeviationHelper2(nodePtr->rightChildPtr, mean, sdHelp);
    }

}

void AVLTree::printStandartDeviationHelper(TreeNode *nodePtr, float &freqCount)
{
    if (nodePtr != NULL)
    {
        freqCount = freqCount + nodePtr->count;
        printStandartDeviationHelper(nodePtr->leftChildPtr, freqCount);
        printStandartDeviationHelper(nodePtr->rightChildPtr, freqCount);
    }
}

void AVLTree::printMostFrequent(ostream &file) const
{
    string mostWord = "";
    int mostWordNumber = 0;
    stringstream temp;
    printMostFrequentHelper(mostWord, mostWordNumber, root);
    temp << mostWordNumber;
    string mostWordNumberString = temp.str();
    file << "Most frequent word is \"" << mostWord << "\". It is been used " << mostWordNumberString << " time(s)." << endl;
}

void AVLTree::printMostFrequentHelper(string &mostWord, int &mostWordNumber, TreeNode *nodePtr) const
{
    if (nodePtr != NULL)
    {

        printMostFrequentHelper(mostWord, mostWordNumber, nodePtr->leftChildPtr);

        if (nodePtr->count > mostWordNumber)
        {
            mostWordNumber = nodePtr->count;
            mostWord = nodePtr->item;
        }
        printMostFrequentHelper(mostWord, mostWordNumber, nodePtr->rightChildPtr);
    }
}

void AVLTree::printLeastFrequent(ostream &file) const
{
    string leastWord = "";
    int leastWordNumber;
    stringstream temp;
    printLeastFrequentHelper(leastWord, leastWordNumber, root);
    temp << leastWordNumber;
    string leastWordNumberString = temp.str();
    file << "Least frequent word is \"" << leastWord << "\". It is been used " << leastWordNumberString << " time(s)." << endl;
}

void AVLTree::printLeastFrequentHelper(string &leastWord, int &leastWordNumber, TreeNode *nodePtr) const
{
    if (nodePtr != NULL)
    {
        printLeastFrequentHelper(leastWord, leastWordNumber, nodePtr->leftChildPtr);
        if (nodePtr->count < leastWordNumber)
        {
            leastWordNumber = nodePtr->count;
            leastWord = nodePtr->item;
        }
        printLeastFrequentHelper(leastWord, leastWordNumber, nodePtr->rightChildPtr);
    }
}

void AVLTree::generateTree(ifstream &input)
{
    stringstream tempString;
    string newWord;
    string newWord2;
    while (input >> newWord)
    {
        for (int i = 0; i < newWord.size(); i++)
        {
            if (ispunct(newWord[i]))
            {
                newWord[i] = ' ';
            }
            newWord[i] = tolower(newWord[i]);
        }

        tempString << newWord << endl;
    }
    while (tempString >> newWord2)
    {
        root = addWord(root, newWord2);
    }
}

TreeNode *AVLTree::returnRoot() const
{
    return root;
}

TreeNode *AVLTree::addWord(TreeNode *node, string item)
{
    if (node == NULL)
    {
        node = new TreeNode(item, NULL, NULL);
    }

    if (item.compare(node->item) > 0)
    {
        node->rightChildPtr = addWord(node->rightChildPtr, item);
        if (height(node->rightChildPtr) - height(node->leftChildPtr) == 2)
        {

            if (item.compare(node->rightChildPtr->item) > 0)
            {

                node = leftRotate(node);
            }
            else
            {

                node = doubleLeftRotate(node);
            }
        }
    }
    if (item.compare(node->item) < 0)
    {
        node->leftChildPtr = addWord(node->leftChildPtr, item);
        if (height(node->leftChildPtr) - height(node->rightChildPtr) == 2)
        {
            if (item.compare(node->leftChildPtr->item) < 0)
            {
                node = rightRotate(node);
            }
            else
            {
                node = doubleRightRotate(node);
            }
        }
    }
    if (item.compare(node->item) == 0)
    {
        node->count++;
    }

    node->height = max(height(node->leftChildPtr), height(node->rightChildPtr)) + 1;
    return node;
}

void AVLTree::printWordFrequencies(ostream &file) const
{
    //printMostFrequent(file);
    //printLeastFrequent(file);

    printWordFrequenciesHelper(file, root);
}

void AVLTree::printWordFrequenciesHelper(ostream &file, TreeNode *nodePtr) const
{
    if (nodePtr != NULL)
    {
        printWordFrequenciesHelper(file, nodePtr->leftChildPtr);
        file << nodePtr->item << " :" << nodePtr->count << endl;
        printWordFrequenciesHelper(file, nodePtr->rightChildPtr);
    }
}

TreeNode *AVLTree::rightRotate(TreeNode *&t)
{
    if (t->leftChildPtr != NULL)
    {
        TreeNode *u = t->leftChildPtr;
        t->leftChildPtr = u->rightChildPtr;
        u->rightChildPtr = t;
        t->height = max(height(t->leftChildPtr), height(t->rightChildPtr)) + 1;
        u->height = max(height(u->leftChildPtr), t->height) + 1;
        return u;
    }
    return t;
}

TreeNode *AVLTree::leftRotate(TreeNode *&t)
{
    if (t->rightChildPtr != NULL)
    {
        TreeNode *u = t->rightChildPtr;
        t->rightChildPtr = u->leftChildPtr;
        u->leftChildPtr = t;
        t->height = max(height(t->leftChildPtr), height(t->rightChildPtr)) + 1;
        u->height = max(height(t->rightChildPtr), t->height) + 1;
        return u;
    }
    return t;
}

TreeNode *AVLTree::doubleLeftRotate(TreeNode *&t)
{
    t->rightChildPtr = rightRotate(t->rightChildPtr);
    return leftRotate(t);
}

TreeNode *AVLTree::doubleRightRotate(TreeNode *&t)
{
    t->leftChildPtr = leftRotate(t->leftChildPtr);
    return rightRotate(t);
}

int AVLTree::max(int a, int b) const
{
    return (a > b) ? a : b;
}

int AVLTree::height(TreeNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int AVLTree::getBalance(TreeNode *N)
{
    if (N == NULL)
        return 0;

    return height(N->leftChildPtr) - height(N->rightChildPtr);
}

ostream &operator<<(ostream &out, AVLTree &tree) //operator overloading that print the contents of the tree
{
    return tree.print(out);
}

ostream &AVLTree::print(ostream &out) //helper function that passes root to printHelper
{
    return printHelper(out, root);
}

ostream &AVLTree::printHelper(ostream &out, TreeNode *rootPtr) //algorithm traverses evey node and prints the contents of the nodes
{
    if (rootPtr != NULL)
    {
        printHelper(out, rootPtr->leftChildPtr);
        out << rootPtr->item << endl;
        printHelper(out, rootPtr->rightChildPtr);
    }
    return out;
}

void AVLTree::writeFile(ostream &file)
{
    writeFileHelper(file, root);
}

void AVLTree::writeFileHelper(ostream &file, TreeNode *nodePtr) //function, writes the data into a new file
{
    if (nodePtr != NULL)
    {
        writeFileHelper(file, nodePtr->leftChildPtr);
        file << nodePtr->item << endl;
        writeFileHelper(file, nodePtr->rightChildPtr);
    }
}

AVLTree::~AVLTree() //calls destructor helper function and passes in root
{
    destroyTree(root);
}

void AVLTree::destroyTree(TreeNode *&treePtr) //deallocates the heap space
{

    if (treePtr != NULL)
    {
        destroyTree(treePtr->leftChildPtr);
        destroyTree(treePtr->rightChildPtr);
        delete treePtr;
        treePtr = NULL;
    }
}
