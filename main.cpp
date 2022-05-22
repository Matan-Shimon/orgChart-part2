#include <iostream>
#include "sources/OrgChart.hpp"
using namespace std;
using namespace ariel;

int main() {
    int num = 0;
    cout << "Hello there and welcome to Matan's organization chart!" << endl;
    OrgChart orgChart;
    string head_manager_name;
    string manager_name;
    string sub_name;
    while (num != -1) {
        cout << "Please choose action:" << endl;
        cout << "1: set organization root" << endl;
        cout << "2: add subordinate" << endl;
        cout << "3: present level order" << endl;
        cout << "4: present reverse level order" << endl;
        cout << "5: present pre order" << endl;
        cout << "6: print the organization chart" << endl;
        cout << "-1: exit" << endl;
        cin >> num;
        switch (num) {
            case 1:
                cout << "Please enter a name to the new head manager: ";
                cin >> head_manager_name;
                cout << endl;
                orgChart.add_root(head_manager_name);
                break;
            case 2:
                cout << "Please enter the new worker name: ";
                cin >> sub_name;
                cout << endl;
                cout << "Please enter the manager name: ";
                cin >> manager_name;
                cout << endl;
                orgChart.add_sub(manager_name, sub_name);
                break;
            case 3:
                cout << "Organization workers by level order:" << endl;
                for (auto iter = orgChart.begin_level_order(); iter != orgChart.end_level_order(); ++iter) {
                    cout << (*iter) << " ";
                }
                cout <<  endl;
                break;
            case 4:
                cout << "Organization workers by reverse level order:" << endl;
                for (auto iter = orgChart.begin_reverse_order(); iter != orgChart.reverse_order(); ++iter) {
                    cout << (*iter) << " ";
                }
                cout <<  endl;
                break;
            case 5:
                cout << "Organization workers by pre order:" << endl;
                for (auto iter = orgChart.begin_preorder(); iter != orgChart.end_preorder(); ++iter) {
                    cout << (*iter) << " ";
                }
                cout <<  endl;
                break;
            case 6:
                cout << "Organization chart:\n\n";
                cout << orgChart << endl;
                break;
            case -1:
                cout << "Thank's for using Matan's organization chart.\nHave a great day!" << endl;
                break;
            default:
                cout << "Please choose -1 or 1 to 6" << endl;
                break;
        }
    }
    return 0;
}
