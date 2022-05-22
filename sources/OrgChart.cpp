//
// Created by matan on 09/05/2022.
//

#include "OrgChart.hpp"
using namespace ariel;

OrgChart::OrgChart(){
    this->root = new Node();
}

OrgChart::~OrgChart(){
    Iterator iter = begin_level_order();
    for (unsigned int i = 0; i < iter.get_order_by_levels().size(); ++i) {
        for (unsigned int j = 0; j < iter.get_order_by_levels().at(iter.get_order_by_levels().size()-1-i).size(); ++j) {
            delete iter.get_order_by_levels().at(iter.get_order_by_levels().size()-1-i).at(j);
        }
    }
}

OrgChart& OrgChart::add_root(string const & head_manager){
    this->root->set_name(head_manager);
    return *this;
}

OrgChart& OrgChart::add_sub(string const & manager_name, string const & worker_name){
    Node* manager_node = get_worker(manager_name);
    Node* worker_node = new Node(worker_name);
    manager_node->add_child(worker_node);
    worker_node->set_parent(manager_node);
    return *this;
}

Node* OrgChart::get_manager(string const & worker_name) const{
    Node* worker_node = get_worker(worker_name);
    Node* manager_node = worker_node->get_parent();
    if (manager_node == nullptr) {
        throw invalid_argument(worker_name+" has no manager above");
    }
    return manager_node;
}

Node* OrgChart::get_worker(string const & worker_name) const{
    for (auto it = this->begin_level_order(); it != end_level_order(); ++it)
    {
        if (*it == worker_name) {
            Node* worker_node = it.get_curr_node();
            return worker_node;
        }
    }
    throw invalid_argument(worker_name+" is not working at the company");
}

Node* OrgChart::get_root(){
    return this->root;
}

ostream & ariel::operator<< (ostream& output, const OrgChart& orgChart) {
    OrgChart::Iterator level_order(orgChart.root, OrgChart::Iterator::flags::by_level_order);
    for (unsigned int i = 0; i < level_order.get_order_by_levels().size(); ++i) {
        output << "Level "+ to_string(i+1)+": ";
        output << "\n";
        for (unsigned int j = 0; j < level_order.get_order_by_levels().at(i).size(); ++j) {
            output << "Worker name: "+level_order.get_order_by_levels().at(i).at(j)->get_name();
            output << ", boss: "+level_order.get_order_by_levels().at(i).at(j)->get_parent_name();
            output << ", subordinates: ";
            vector<Node*> childs = level_order.get_order_by_levels().at(i).at(j)->get_childs();
            for (unsigned int k = 0; k < childs.size(); ++k) {
                output << childs.at(k)->get_name();
                if (k != childs.size()-1) {
                    output << ", ";
                }
            }
            output << "\n";
        }
        output << "\n";
    }
    return output;
}

OrgChart::Iterator OrgChart::begin_level_order() const{
//    if (this->root->get_name() == "") {
//        throw invalid_argument("chart is empty!");
//    }
    OrgChart::Iterator level_order(this->root, Iterator::flags::by_level_order);
    return level_order;
}

OrgChart::Iterator OrgChart::end_level_order() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator end_order(nullptr, Iterator::flags::end);
    return end_order;
}

OrgChart::Iterator OrgChart::begin_reverse_order() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator reverse_level_order(this->root, Iterator::flags::by_reverse_level_order);
    return reverse_level_order;
}

OrgChart::Iterator OrgChart::reverse_order() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator end_order(nullptr, Iterator::flags::end);
    return end_order;
}

OrgChart::Iterator OrgChart::begin_preorder() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator pre_order(this->root, Iterator::flags::by_pre_order);
    return pre_order;
}

OrgChart::Iterator OrgChart::end_preorder() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator end_order(nullptr, Iterator::flags::end);
    return end_order;
}

OrgChart::Iterator OrgChart::begin() const{
    return begin_level_order();
}
OrgChart::Iterator OrgChart::end() const{
    return end_level_order();
}