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
    string name = "None";
public:
    // constructors
    Node();
    Node(const string & name);
    // simple functions
    string& get_name();
    Node* get_parent();
    string get_parent_name();
    vector<Node*> get_childs();
    void set_name(string name);
    void set_parent(Node* parent);
    void add_child(Node* child);
};
