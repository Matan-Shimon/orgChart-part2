//
// Created by matan on 16/05/2022.
//
#include "Node.hpp"
/*
 * default constructor
 */
Node::Node(){
    this->parent = nullptr;
    this->childs = vector<Node*>();
}
/*
 * Constructor that gets string name
 */
Node::Node(const string & name) : name(name){
    this->parent = nullptr;
    this->childs = vector<Node*>();
}
/*
 * the function returns the node name
 */
string& Node::get_name(){
    return this->name;
}
/*
 * the function returns the parent node
 */
Node* Node::get_parent(){
    return this->parent;
}
/*
 * the function returns the parent node name
 */
string Node::get_parent_name(){
    if (this->parent == nullptr) {
        return "Head manager don't have a boss above";
    }
    return this->parent->get_name();
}
/*
 * The function returns the node childs
 */
vector<Node*> Node::get_childs(){
    return this->childs;
}
/*
 * the function gets a string and changes the node name to that string
 */
void Node::set_name(string name){
    this->name = move(name);
}
/*
 * the function gets a node and setting this node as the parent node of the curr node
 */
void Node::set_parent(Node* parent){
    this->parent = parent;
}
/*
 * the function gets a node and add this node as a child to the curr node
 */
void Node::add_child(Node* child){
    this->childs.push_back(child);
}