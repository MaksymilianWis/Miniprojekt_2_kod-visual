#include <iostream>

struct Node
{
    Node();
    Node(int key, int value);

private:
    bool empty_;
    int key_;
    int value_;

public:
    void OverwriteNodeValue(int value);
    void OverwriteNodeData(int key);
    void OverwriteNodeData(int key, int value);
    void clearNode();

    bool isEmpty();

    int getValue();
};