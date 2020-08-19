/**
* Title: AVL Trees
* Author: Atay Kaylat
* ID: 21703284
* Assignment: 4
* Description: Main function
*/


#include "AVLTree.h"
#include <fstream>

int main(int argc, char **argv)
{
    AVLTree t1;
    ifstream newFile;
    ofstream outputFile;
    ofstream outputFile2;
    newFile.open(argv[1]);
    outputFile.open("wordFreqs");
    outputFile2.open("statistics");
    t1.generateTree(newFile);
    t1.printWordFrequencies(outputFile);
    t1.printStatistics(outputFile2);
    
    return 0;
}