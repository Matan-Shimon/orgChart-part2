//
// Created by matan on 09/05/2022.
//


#include "iostream"
#include<iterator>
#include<vector>
#include "Node.hpp"
#include "queue"
#include "stack"

using namespace std;

namespace ariel {
    class OrgChart{
    private:
        Node* root;
    public:
        OrgChart();
        ~OrgChart();

        OrgChart& add_root(string const & head_manager_name);
        OrgChart& add_sub(string const & manager_name, string const & worker_name);
        Node* get_manager(string const & worker_name) const;
        Node* get_worker(string const & worker_name) const;
        Node* get_root();
        friend ostream & operator<< (ostream& output, const OrgChart& orgChart);

        class Iterator{
        private:
            Node* curr_node;
            vector<Node*> order;
            vector<vector<Node*>> order_by_levels;
            int iter_size;
        public:
            enum flags{by_level_order, by_reverse_level_order, by_pre_order, end};
            Iterator(Node* ptr = nullptr, const int & flag = Iterator::flags::by_level_order){
                this->curr_node = ptr;
                this->iter_size = 0;
                if (flag == 0) { // level order
                    level_order();
                }
                else {
                    if (flag == 1) { // reverse order
                        reverse_level_order();
                    }
                    else {
                        if (flag == 2) { // pre order
                            pre_order();
                        }
                        else { // end
                            end_iter();
                        }
                    }
                }
            }
            Node* get_curr_node() {
                return this->curr_node;
            }
            Iterator level_order(){
                // BFS
                queue<Node*> queue;
                queue.push(this->curr_node);
                int child_index = 0;
                int num_in_level = 1;
                int num_of_childs = queue.front()->get_childs().size();
                vector<Node*> temp;
                while (!queue.empty()) {
                    // for regular level order
                    this->order.push_back(queue.front());
                    // for seeing the order by levels, will use that for reverse level order
                    temp.push_back(queue.front());
                    if (child_index+1 == num_in_level) {
                        this->order_by_levels.push_back(temp);
                        temp.clear();
                        child_index = 0;
                        num_in_level = num_of_childs;
                        num_of_childs = 0;
                    }
                    else {
                        child_index++;
                    }

                    vector<Node*> childs = queue.front()->get_childs();
                    for (unsigned int i = 0; i < childs.size(); ++i) {
                        queue.push(childs.at(i));
                        num_of_childs += childs.at(i)->get_childs().size();
                    }
                    queue.pop();
                }
                this->order.push_back(nullptr);
                return *this;
            }
            Iterator reverse_level_order(){
                // REVERSE BFS
                Iterator level_iter = level_order();
                this->order = vector<Node*>();
                for (int i = level_iter.order_by_levels.size()-1; i >= 0; i--) {
                    for (unsigned int j = 0; j < level_iter.order_by_levels.at(unsigned (i)).size(); ++j) {
                        this->order.push_back(level_iter.order_by_levels.at(unsigned (i)).at(j));
                    }
                }
                this->curr_node = this->order.front();
                this->order.push_back(nullptr);
                return *this;
            }
            Iterator pre_order(){
                // DFS
                cout << "\n";
                pre_order_rec();
                cout << "\n";
                this->curr_node = this->order.front();
                this->order.push_back(nullptr);
                return *this;
            }
            void pre_order_rec(){
                this->order.push_back(this->curr_node);
                int childs_num = this->order.back()->get_childs().size();
                unsigned int index = this->order.size()-1;
                for (unsigned int i = 0; i < childs_num; ++i) {
                    this->curr_node = this->order.at(index)->get_childs().at(i);
                    pre_order_rec();
                }
            }
            Iterator end_iter() {
                // the end of any iterator
                return *this;
            }
            vector<vector<Node*>> get_order_by_levels() {
                return this->order_by_levels;
            }
            Iterator operator++(){
                if (!this->order.empty()) {
                    this->order.erase(this->order.begin());
                    this->curr_node = this->order.front();
                }
                return *this;
            }
            Iterator operator++(int){
                Iterator iter_copy = *this;
                ++*this;
                return iter_copy;
            }
            bool operator!=(Iterator other_iter) const {
                return this->curr_node != other_iter.curr_node;
            }
            bool operator==(Iterator other_iter) const {
                return !(*this != other_iter);
            }
            string & operator*() const {
                return this->curr_node->get_name();
            }
            string * operator->() const {
                return &(this->curr_node->get_name());
            }
        };

        Iterator begin_level_order() const;
        static Iterator end_level_order();
        Iterator begin_reverse_order() const;
        static Iterator reverse_order();
        Iterator begin_preorder() const;
        static Iterator end_preorder();
        Iterator begin() const;
        static Iterator end();
    };
}