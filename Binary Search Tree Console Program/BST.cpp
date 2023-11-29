// Copyright 2023 Brian Bongermino

#include<iostream>
#include<string>
#include<sstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::replace;


// Initial Struct for the BST
struct btsCore {
    int values;
    btsCore* left;
    btsCore* right;
};

// function to allow for new nodes to be created and
// for the default state for the left and right nodes to
// be null
btsCore* newNode(int values) {
    btsCore* newNode = new btsCore();
    newNode->values = values;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


// Function to insert node. The first is a check if the root is empty
// if it is then the initial node entered by the user becomes the root.
// Afterwards every node inserted after goes through a check to see
// if it will either be a left branch or a right branch.
// if a dubplicate value is detected then it wont insert anything and
// will inform the user.
btsCore* insertNode(btsCore* rootNode, int values) {
    if (rootNode == nullptr) {
        rootNode = newNode(values);
        cout << "Node " << values << " was successfully inserted." << endl;
    } else if (values < rootNode->values) {
        rootNode->left = insertNode(rootNode->left, values);
    } else if (values > rootNode->values) {
        rootNode->right = insertNode(rootNode->right, values);
    } else {
        cout << "Node " << values << " is a duplicate node. "
        "Cannot insert Node " << values << " again."  << endl;
    }
    return rootNode;
}


// finds the minimum node by just checking the left node until
// it runs into a null value
btsCore* findMin(btsCore* node) {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}


// finds the minimum node by just checking the right node until
// it runs into a null value
btsCore* findMax(btsCore* node) {
    while (node != nullptr && node->right != nullptr) {
        node = node->right;
    }
    return node;
}

/* Search function that'll move through every branch until it finds a null value
    once a null value is found it'll inform the user that it doesn't exist
    if a null value is never found then it will simply inform the user the path
    taken to get to the final branch. IE if the branch is 
                        5  
                            \
                                8
                               /     \
                              7        9
    it will save the output as 5 -> 8 > 9 assuming the user is searching 9.
*/

btsCore* searchBTS(btsCore* rootnode, int search, string& searchPath) {  // NOLINT
        if (rootnode == nullptr) {
        searchPath += "search key not found";
        return nullptr;
    }

    searchPath += to_string(rootnode->values);

    while (rootnode->values != search) {
        if (search < rootnode->values) {
            searchPath += " -> ";
            // check for the right branch (legacy code)
            /*if (rootnode->left == nullptr)
                return searchBTS(rootnode->right, search, searchPath);*/
            return searchBTS(rootnode->left, search, searchPath);
    } else if (search > rootnode->values) {
        searchPath += " -> ";
        /*if (rootnode->right == nullptr)
                    // check for the right branch
            return searchBTS(rootnode->left, search, searchPath);*/
        return searchBTS(rootnode->right, search, searchPath);
    } else {
        return rootnode;
    }
    }

    return nullptr;
}

/*  function to delete nodes in the binary tree. It'll take in two values, that being the rootnote
    and the value set to be deleted. First it'll check if there is actually a root node. Second, it'll go through
    each brach and find where the node needs to be deleted and if the tree has children or not. 
*/
btsCore* deleteNode(btsCore* rootnode, int del) {
    if (rootnode == nullptr)
        return rootnode;

    if (del < rootnode->values) {
        rootnode->left = deleteNode(rootnode->left, del);
    } else if (del > rootnode->values) {
        rootnode->right = deleteNode(rootnode->right, del);
    } else {
        // check for one child or no child and deletes the node
        if (rootnode->left == nullptr) {
            btsCore* temp = rootnode->right;
            delete rootnode;
            return temp;
        } else if (rootnode->right == nullptr) {
            btsCore* temp = rootnode->left;
            delete rootnode;
            return temp;
        } else {
            // get the minimum sucessor
            btsCore* temp = findMin(rootnode->right);

            // copy it to values
            rootnode->values = temp->values;

            // delete the inorder sucessor
            rootnode->right = deleteNode(rootnode->right, temp->values);
        }
    }
    return rootnode;
}

// just a basic function to display whats in the tree
void displayBTS(btsCore* rootNode) {
    if (rootNode == nullptr)
        return;

    displayBTS(rootNode->left);

    string bstOut;

    // cout << rootNode->values << ", ";
    bstOut += to_string(rootNode->values) + ", ";

    cout << bstOut;

    displayBTS(rootNode->right);
}

int main() {
    // default state of the tree
    btsCore* tree = nullptr;

    int values = 0, options = -1;
    string searchPath = "";
    string test;
    string multValOut;
    std::istringstream firstTestIDK;


    // original code for multiple entries. Was replaced with option 6 in the menu
    // do loop to allow the user to input as many values as they need
    /* cout << "To begin please enter a value for the Binary Search Tree" << endl;
    do {
        cout << "Please enter a value to insert" << endl;
        cin >> values;
        tree = insertNode(tree, values);
        // cout << "Node" << values << "was inserted" << endl;

        cout << "Would you like to insert another value? "
        "Please enter 'Y' to continue or 'N' to stop" << endl;
        cin >> cont;
    } while (cont == 'Y' || cont == 'y'); */
    btsCore* minNode = nullptr;
    btsCore* maxNode = nullptr;

    // while loop to allow the user to interact with a menu system
    // that will perform multiple functions.
    // these being insert, delete, search, fidining the minimum,
    // finding the maximum, or stopping the program.
    while (options != 0) {
        cout << "BTS Nodes are: ";
        displayBTS(tree);
        cout << endl;
        cout << "You have the option to delete, "
        "insert, and search for a node, find the minimum and maximum node, or insert multiple nodes." << endl;
        cout << "[1] for Insert" << endl;
        cout << "[2] for Delete" << endl;
        cout << "[3] for Search" << endl;
        cout << "[4] to find the minimum" << endl;
        cout << "[5] to find the maximum" << endl;
        cout << "[6] to enter multiple values" << endl;
        cout << "[0] to stop the program" << endl;
        cin >> options;
        if (options < 0 || options > 6) {
            cout << "Please insert another value" << endl;
        }
        // switch case that allows for options to enable different interactions
        switch (options) {
            case 0:
                break;
            case 1:
                cout << "Please enter a value to insert:" << endl;
                cin >> values;
                tree = insertNode(tree, values);
                break;

            case 2:
                cout << "Please enter a value to delete:" << endl;
                cin >> values;
                tree = deleteNode(tree, values);
                break;

            case 3:
                cout << "Please enter a value to search:" << endl;
                cin >> values;
                searchPath = "";
                searchBTS(tree, values, searchPath);
                cout << searchPath << endl;
                break;

            case 4:
                minNode = findMin(tree);
                if (findMin(tree) != nullptr) {
                    cout << "The Min node is: " << endl;
                    cout << "Node: " << minNode->values << endl;
                }
                break;

            case 5:
                maxNode = findMax(tree);
                if (maxNode != nullptr) {
                    cout << "The Max node is: " << endl;
                    cout << "Node: " << maxNode->values << endl;
                }
                break;

            case 6:
                cout << "Please enter multiple values to insert into the tree:" << endl;
                cin.ignore();
                getline(cin, test);
                firstTestIDK.str(test);
                firstTestIDK.clear();
                while (firstTestIDK >> values) {
                    tree = insertNode(tree, values);
                    multValOut += to_string(values) + ", ";
                }
                cout << "Inserting " << multValOut <<
                "with the following order of: " << endl;
                displayBTS(tree);
                cout << endl;
                multValOut.clear();
                break;

            default:
                cout << "Please enter 1, 2, 3, 4, or 5." << endl;
                cout << "If you want to stop the program please enter 0" << endl;
                break;
        }
    }
    return 0;
}
