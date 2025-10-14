#include <iostream>
#include <string>
using namespace std;

class InventoryNode {
private:
    string item;
    int numberOfItems;
    InventoryNode* nextNodeRef;

public:
    //constructor given
    InventoryNode() {
        this->item = "head";
        this->numberOfItems = -1;
        this->nextNodeRef = nullptr;
    }

    //constructor given
    InventoryNode(string itemInit, int numberOfItemsInit) {
        this->item = itemInit;
        this->numberOfItems = numberOfItemsInit;
        this->nextNodeRef = nullptr;
    }

    // constructor given
    InventoryNode(string itemInit, int numberOfItemsInit, InventoryNode nextLoc) {
        this->item = itemInit;
        this->numberOfItems = numberOfItemsInit;
        this->nextNodeRef = &nextLoc;
    }

    // InsertAtFront() inserts node at front of linked list (after head node)
    void InsertAtFront(InventoryNode* headNode, InventoryNode* newNode) {
        newNode->nextNodeRef = headNode->nextNodeRef;
        headNode->nextNodeRef = newNode;
    }

    //get next node ; given
    InventoryNode* GetNext() {
        return this->nextNodeRef;
    }

    //print node data ; given
    void PrintNodeData() {
        cout << this->numberOfItems << " " << this->item << endl;
    }
};
