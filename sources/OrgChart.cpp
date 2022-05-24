//
// Created by matan on 09/05/2022.
//

#include "OrgChart.hpp"
using namespace ariel;
/*
 * default constructor that will only create a new (default) Node while creating a new chart
 */
OrgChart::OrgChart(){
    this->root = new Node();
}
/*
 *  Destructor
    the destructor must delete the chart from the "inside out", the most "inside" part is
    the lowest level of the chart, that's why I'm deleting first the lowest level, and continue
    to delete untill the top level.
 */
OrgChart::~OrgChart(){
    vector<vector<Node*>> order_by_levels = get_order_by_levels();
    for (unsigned int i = 0; i < order_by_levels.size(); ++i) {
        for (unsigned int j = 0; j < order_by_levels.at(order_by_levels.size()-1-i).size(); ++j) {
            delete order_by_levels.at(order_by_levels.size()-1-i).at(j);
        }
    }
}
/*
 * Adding a root node, this function gets a string and changes the root name
 */
OrgChart& OrgChart::add_root(string const & head_manager){
    check_name_validation(head_manager);
    this->root->set_name(head_manager);
    return *this;
}
/*
 * This function gets two strings and adding a subordinate to the first string worker (if he exists)
 */
OrgChart& OrgChart::add_sub(string const & manager_name, string const & worker_name){
    check_name_validation(worker_name);
    Node* manager_node = get_worker(manager_name);
    Node* worker_node = new Node(worker_name);
    manager_node->add_child(worker_node);
    worker_node->set_parent(manager_node);
    return *this;
}
/*
 * This function checks whether a name is valid or not.
 * If the name is valid, the function won't throw an error
 */
void OrgChart::check_name_validation(string const & name){
    if (name.empty()) {
        throw invalid_argument("Invalid name!");
    }
    for (unsigned int i = 0; i < name.size(); ++i) {
        char ch = name.at(i);
        if (ch < '!' || ch > '~') {
            if (ch != ' ') {
                throw invalid_argument("Invalid name!");
            }
        }
    }
}
/*
 * This function gets a string name and returns his manager
 */
Node* OrgChart::get_manager(string const & worker_name) const{
    Node* worker_node = get_worker(worker_name);
    Node* manager_node = worker_node->get_parent();
    if (manager_node == nullptr) {
        throw invalid_argument(worker_name+" has no manager above");
    }
    return manager_node;
}
/*
 * This function gets a string, and returns the worker with that name (if he exists)
 */
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
/*
 * This function returns the chart root
 */
Node* OrgChart::get_root(){
    return this->root;
}
/*
 * This function returns the chart order by levels (for printing and destructor)
 */
vector<vector<Node*>> OrgChart::get_order_by_levels() const{
    queue<Node*> queue;
    vector<vector<Node*>> order_by_levels = vector<vector<Node*>>();
    queue.push(this->root);
    int child_index = 0; // to know when the level is finished
    int num_in_level = 1; // to know the num of nodes in the level
    int num_of_childs = 0; // to know the next level num of nodes
    vector<Node*> level; // for entering the nodes in the level
    while (!queue.empty()) {
        // for seeing the order by levels, I will use that for reverse level order calculation
        level.push_back(queue.front());
        num_of_childs += queue.front()->get_childs().size();
        // the level has been ended
        if (child_index+1 == num_in_level) {
            order_by_levels.push_back(level);
            level.clear();
            child_index = 0;
            num_in_level = num_of_childs;
            num_of_childs = 0;
        }
        else { // the level has not ended yet
            child_index++;
        }
        // for regular level order
        vector<Node*> childs = queue.front()->get_childs();
        for (unsigned int i = 0; i < childs.size(); ++i) {
            queue.push(childs.at(i));
        }
        queue.pop();
    }
    return order_by_levels;
}
/*
 * This function overloads the << (cout) operator
 * By presenting each level (from top to bottom) nodes, there parents, and subordinates
 */
ostream & ariel::operator<< (ostream& output, const OrgChart& orgChart) {
    vector<vector<Node*>> order_by_levels = orgChart.get_order_by_levels();
    for (unsigned int i = 0; i < order_by_levels.size(); ++i) {
        output << "Level "+ to_string(i+1)+": ";
        output << "\n";
        for (unsigned int j = 0; j < order_by_levels.at(i).size(); ++j) {
            output << "Worker name: "+order_by_levels.at(i).at(j)->get_name();
            output << ", boss: "+order_by_levels.at(i).at(j)->get_parent_name();
            output << ", subordinates: ";
            vector<Node*> childs = order_by_levels.at(i).at(j)->get_childs();
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
/*
 * This function returns an Iterator that will work in level order
 */
OrgChart::Iterator OrgChart::begin_level_order() const{
    OrgChart::Iterator level_order(this->root, Iterator::flags::by_level_order);
    return level_order;
}
/*
 * This function returns an Iterator that will be the end of level order
 */
OrgChart::Iterator OrgChart::end_level_order() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator end_order(nullptr, Iterator::flags::end);
    return end_order;
}
/*
 * This function returns an Iterator that will work in reverse level order
 */
OrgChart::Iterator OrgChart::begin_reverse_order() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator reverse_level_order(this->root, Iterator::flags::by_reverse_level_order);
    return reverse_level_order;
}
/*
 * This function returns an Iterator that will be the end of reverse level order
 */
OrgChart::Iterator OrgChart::reverse_order() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator end_order(nullptr, Iterator::flags::end);
    return end_order;
}
/*
 * This function returns an Iterator that will work in begin pre order
 */
OrgChart::Iterator OrgChart::begin_preorder() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator pre_order(this->root, Iterator::flags::by_pre_order);
    return pre_order;
}
/*
 * This function returns an Iterator that will be the end of pre order
 */
OrgChart::Iterator OrgChart::end_preorder() const{
    if (this->root->get_name() == "None") {
        throw invalid_argument("chart is empty!");
    }
    OrgChart::Iterator end_order(nullptr, Iterator::flags::end);
    return end_order;
}
/*
 * This function returns an Iterator that will work in level order
 */
OrgChart::Iterator OrgChart::begin() const{
    return begin_level_order();
}
/*
 * This function returns an Iterator that will be the end of level order
 */
OrgChart::Iterator OrgChart::end() const{
    return end_level_order();
}