//
// Created by matan on 16/05/2022.
//
#include "Node.hpp"

Node::Node(){
    this->parent = nullptr;
    this->childs = vector<Node*>();
}
Node::Node(const string & name) : name(name){
    this->parent = nullptr;
    this->childs = vector<Node*>();
}
string& Node::get_name(){
    return this->name;
}
Node* Node::get_parent(){
    return this->parent;
}
string Node::get_parent_name(){
    if (this->parent == nullptr) {
        return "Head manager don't have a boss above";
    }
    return this->parent->get_name();
}
vector<Node*> Node::get_childs(){
    return this->childs;
}
void Node::set_name(string name){
    this->name = move(name);
}
void Node::set_parent(Node* parent){
    this->parent = parent;
}
void Node::add_child(Node* child){
    this->childs.push_back(child);
}
bool Node::operator==(Node* other_node){
    return this->name == other_node->name;
}
bool Node::operator!=(Node* other_node){
    return !(this == other_node);
}