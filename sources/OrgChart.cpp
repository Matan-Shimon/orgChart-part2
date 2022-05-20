//
// Created by matan on 09/05/2022.
//

#include "OrgChart.hpp"
using namespace ariel;

OrgChart::OrgChart(){
    this->root = new Node();
}

OrgChart& OrgChart::add_root(string head_manager){
    this->root->set_name(head_manager);
    return *this;
}

OrgChart& OrgChart::add_sub(string manager_name, string worker_name){
    bool found_manager = false;
    Node* manager_node = get_worker(manager_name);
    Node worker_node = Node(worker_name);
    manager_node->add_child(&worker_node);
    return *this;
}

Node* OrgChart::get_manager(string worker_name){
    Node* worker_node = get_worker(worker_name);
    Node* manager_node = worker_node->get_parent();
    if (manager_node->get_name() == "") {
        throw invalid_argument(worker_name+" has no manager above");
    }
    return manager_node;
}

Node* OrgChart::get_worker(string worker_name) {
    Node* worker_node;
    for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
    {
        if (*it == worker_name) {
            worker_node = it.get_curr_node();
        }
    }
    if (worker_node->get_name() == "") {
        throw invalid_argument(worker_name+" is not working at the company");
    }
    return worker_node;
}

Node* OrgChart::get_root(){
    return this->root;
}

ostream & ariel::operator<< (ostream& output, const OrgChart& orgChart){

//    for (auto it = orgChart.begin_level_order(); it != this->end_level_order(); ++it) {
//
//    }
    return output;
}

OrgChart::Iterator OrgChart::begin_level_order() const{
    OrgChart::Iterator check(this->root, 'l');
    return check;
}

OrgChart::Iterator OrgChart::end_level_order() const{
    OrgChart::Iterator check(nullptr, 'l');
    return check;
}

OrgChart::Iterator OrgChart::begin_reverse_order() const{
    OrgChart::Iterator check(this->root, 'r');
    return check;
}

OrgChart::Iterator OrgChart::reverse_order() const{
    OrgChart::Iterator check(nullptr, 'r');
    return check;
}

OrgChart::Iterator OrgChart::begin_preorder() const{
    OrgChart::Iterator check(this->root, 'b');
    return check;
}

OrgChart::Iterator OrgChart::end_preorder() const{
    OrgChart::Iterator check(nullptr, 'b');
    return check;
}

OrgChart::Iterator OrgChart::begin() const{
    return begin_level_order();
}
OrgChart::Iterator OrgChart::end() const{
    return end_level_order();
}