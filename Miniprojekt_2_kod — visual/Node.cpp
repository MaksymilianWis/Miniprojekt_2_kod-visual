#include "Node.hpp"

Node::Node() : key_(0), value_(0), empty_(1) {};
Node::Node(int key, int value) : key_(key), value_(value), empty_(0) {};

void Node::OverwriteNodeValue(int value) {
    // nie wolno zmieniac danych bez dodania klucza
    if (empty_ == true) {
        std::cout << "ERROR Cannot change value when key is not set\n";
        return;
    }

    value_ = value;
}

void Node::OverwriteNodeKey(int key) {
    // nie wolno zmieniac danych bez dodania klucza
    if (empty_ == true) {
        std::cout << "ERROR Cannot change key when value is not set\n";
        return;
    }
    key_ = key;
}

void Node::OverwriteNodeKeyValue(int key, int value) {
    key_ = key;
    value_ = value;
    empty_ = false;
}

void Node::clearNode() {
    empty_ = true;
}

bool Node::isEmpty() {
    return empty_;
}

int Node::getValue() {
    return value_;
}