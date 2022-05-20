//
// Created by matan on 09/05/2022.
//


#include "iostream"
#include<iterator>
#include<vector>
#include "Node.hpp"
#include "queue"

using namespace std;

namespace ariel {
    class OrgChart{
    private:
        Node* root;
    public:
        OrgChart();
        OrgChart& add_root(string head_manager_name);
        OrgChart& add_sub(string manager_name, string worker_name);
        bool in_company(string worker_name);
        Node* get_manager(string worker_name);
        Node* get_worker(string worker_name);
        Node* get_root();
        friend ostream & operator<< (ostream& output, const OrgChart& orgChart);

        class Iterator{
        private:
            Node* curr_node;
            vector<Node*> order;
            char flag;
            int iter_size;
        public:
            Iterator(Node* ptr = nullptr, char flag = 'l'){
                this->curr_node = ptr;
                this->flag = flag;
                this->iter_size = 0;
                if (flag == 'l') { // level order
                    level_order_increment();
                }
                else {
                    if (flag == 'r') { // reverse order
                        reverse_order_increment();
                    }
                    else { // pre order
                        pre_order_increment();
                    }
                }
            }
            Node* get_curr_node() {
                return this->curr_node;
            }
            Iterator& operator++(){

            }
            Iterator& level_order_increment(){
                // BFS
                queue<Node*> queue;
                queue.push(this->curr_node);
                while (!queue.empty()) {
                    this->order.push_back(queue.front());
                    vector<Node*> childs = queue.front()->get_childs();
                    for (unsigned int i = 0; i < childs.size(); ++i) {
                        queue.push(childs.at(i));
                    }
                    queue.pop();
                }

            }
            Iterator& reverse_order_increment(){
                // REVERSE BFS
            }
            Iterator& pre_order_increment(){
                // DFS
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
        Iterator end_level_order() const;
        Iterator begin_reverse_order() const;
        Iterator reverse_order() const;
        Iterator begin_preorder() const;
        Iterator end_preorder() const;
        Iterator begin() const;
        Iterator end() const;
    };
}