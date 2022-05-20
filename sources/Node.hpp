//
// Created by matan on 16/05/2022.
//
#pragma once
#include "iostream"
#include "vector"

using namespace std;

class Node {
private:

    Node* parent;
    vector<Node*> childs;
    string name = "";
    int tag = 0;
public:
    Node();
    Node(const string & name);
    string& get_name();
    Node* get_parent();
    vector<Node*> get_childs();
    void set_name(string name);
    void set_parent(Node* parent);
    void add_child(Node* child);
    bool operator==(Node* other_node);
    bool operator!=(Node* other_node);
};
