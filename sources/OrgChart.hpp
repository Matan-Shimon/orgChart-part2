//
// Created by matan on 09/05/2022.
//


#include "iostream"
#include<vector>
#include "Node.hpp"
#include "queue"

using namespace std;

namespace ariel {
    class OrgChart{
    private:
        Node* root;
    public:
        // constructors
        OrgChart();
        OrgChart(OrgChart& chart) = default; // for tidy
        OrgChart(OrgChart&& chart) = default; // for tidy
        // destructor
        ~OrgChart();
        // basic functions
        OrgChart& add_root(string const & head_manager_name);
        OrgChart& add_sub(string const & manager_name, string const & worker_name);
        static void check_name_validation(string const & name);
        Node* get_manager(string const & worker_name) const;
        Node* get_worker(string const & worker_name) const;
        Node* get_root();
        vector<vector<Node*>> get_order_by_levels() const; // (for printing and destructor)
        // cout (<<) overload
        friend ostream & operator<< (ostream& output, const OrgChart& orgChart);
        OrgChart& operator= (OrgChart const & chart) = default; // for tidy
        OrgChart& operator= (OrgChart && chart) = default; // for tidy
        // Inner Iterator class
        class Iterator{
        private:
            Node* curr_node;
            vector<Node*> order;
            vector<vector<Node*>> order_by_levels; // will be relevant for reverse level order calculation
        public:
            // enum for knowing which type of iterator we need to calculate
            enum flags{by_level_order, by_reverse_level_order, by_pre_order, end};
            // constructor
            Iterator(Node* ptr = nullptr, const int & flag = Iterator::flags::by_level_order){
                this->curr_node = ptr;
                if (flag == by_level_order) { // level order
                    level_order();
                }
                else {
                    if (flag == by_reverse_level_order) { // reverse order
                        reverse_level_order();
                    }
                    else {
                        if (flag == by_pre_order) { // pre order
                            pre_order();
                        }
                        else { // end
                            end_iter();
                        }
                    }
                }
            }
            // returns the Iterator curr node
            Node* get_curr_node() {
                return this->curr_node;
            }
            vector<Node*> get_iter_order() {
                return this->order;
            }
            // calculating the level order that the iterator need to compute
            Iterator level_order(){
                // BFS
                this->order = vector<Node*>();
                queue<Node*> queue;
                queue.push(this->curr_node);
                while (!queue.empty()) {
                    // for regular level order
                    this->order.push_back(queue.front());
                    // for regular level order
                    vector<Node*> childs = queue.front()->get_childs();
                    for (unsigned int i = 0; i < childs.size(); ++i) {
                        queue.push(childs.at(i));
                    }
                    queue.pop();
                }
                this->order.push_back(nullptr);
                return *this;
            }
            // calculating the reverse level order that the iterator need to compute
            Iterator reverse_level_order(){
                // REVERSE BFS
                vector<Node*> vec_for_rev;
                vec_for_rev.push_back(this->curr_node);
                int num_of_nodes = vec_for_rev.size();
                for (unsigned int i = 0; i < num_of_nodes; ++i) {
                    int num_of_childs = vec_for_rev.at(i)->get_childs().size();
                    for (int j = num_of_childs-1; j >= 0; --j) {
                        vec_for_rev.push_back(vec_for_rev.at(i)->get_childs().at(unsigned (j)));
                    }
                    num_of_nodes = vec_for_rev.size();
                }
                for (unsigned int i = 0; i < vec_for_rev.size(); ++i) {
                    this->order.push_back(vec_for_rev.at(unsigned (vec_for_rev.size()-1-i)));
                }
                this->curr_node = this->order.at(0);
                this->order.push_back(nullptr);
                return *this;
            }
            // calculating the pre order that the iterator need to compute
            Iterator pre_order(){
                // DFS
                pre_order_rec(); // recursive function to compute the pre order
                this->curr_node = this->order.front();
                this->order.push_back(nullptr);
                return *this;
            }
            void pre_order_rec(){
                this->order.push_back(this->curr_node);
                int childs_num = this->order.back()->get_childs().size();
                unsigned int index = this->order.size()-1;
                // going to each child
                for (unsigned int i = 0; i < childs_num; ++i) {
                    this->curr_node = this->order.at(index)->get_childs().at(i);
                    // calling again the recursive function with the child
                    pre_order_rec();
                }
            }
            // the end of any iterator
            Iterator end_iter() {
                return *this;
            }
            // getting the order by levels
            vector<vector<Node*>> get_order_by_levels() {
                return this->order_by_levels;
            }
            /*
             * overload ++ operator and by that incrementing the iterator
             */
            Iterator operator++(){
                if (!this->order.empty()) {
                    this->order.erase(this->order.begin());
                    this->curr_node = this->order.front();
                }
                return *this;
            }
            /*
             * overload ++(int)
             */
            Iterator operator++(int){
                Iterator iter_copy = *this;
                ++*this;
                return iter_copy;
            }
            /*
             * overload != operator
             */
            bool operator!=(Iterator const & other_iter) const {
                return this->curr_node != other_iter.curr_node;
            }
            /*
             * overload == operator
             */
            bool operator==(Iterator const & other_iter) const {
                return !(*this != other_iter);
            }
            /*
             * overload * operator, by getting the name of the iterator curr node each time we
             * will do *iter.
             */
            string & operator*() const {
                return this->curr_node->get_name();
            }
            /*
             * overload -> operator, by getting the address of the iterator curr node value (name)
             */
            string * operator->() const {
                return &(this->curr_node->get_name());
            }
        };
        // iterator options
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