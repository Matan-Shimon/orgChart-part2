//
// Created by matan on 09/05/2022.
//
#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "sources/OrgChart.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("Base test 1") {
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
            .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
            .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
            .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
            .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO

    CHECK_THROWS(organization.get_manager("CEO"));
    CHECK_EQ(organization.get_manager("CTO") == "CEO", true);
    CHECK_EQ(organization.get_manager("CFO") == "CEO", true);
    CHECK_EQ(organization.get_manager("COO") == "CEO", true);
    CHECK_EQ(organization.get_manager("VP_SW") == "CTO", true);
    CHECK_EQ(organization.get_manager("VP_BI") == "COO", true);
    CHECK_THROWS(organization.get_manager("Something"));

    cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
       CEO
       |--------|--------|
       CTO      CFO      COO
       |                 |
       VP_SW             VP_BI
 */
    vector<string> names = {"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
    unsigned int index = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(*it == names.at(index), true);
        index++;
    } // prints: CEO CTO CFO COO VP_SW VP_BI
    names = {"VP_SW", "VP_BI", "CTO", "CFO", "COO", "CEO"};
    index = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(*it == names.at(index), true);
        index++;
    } // prints: VP_SW VP_BI CTO CFO COO CEO
    names = {"CEO", "CTO", "VP_SW", "CFO", "COO", "VP_BI"};
    index = 0;
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        CHECK_EQ(*it == names.at(index), true);
        index++;
    }  // prints: CEO CTO VP_SW CFO COO VP_BI

//  for (int element: tree_of_ints) {  // this should work like level order
//    cout << element << " " ;
//  } // prints: CEO CTO CFO COO VP_SW VP_BI

    // demonstrate the arrow operator:
    vector<int> sizes = {3, 3, 3, 3, 5, 5};
    index = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(it->size() == sizes.at(index), true);
        index++;
    } // prints: 3 3 3 3 5 5
}

TEST_CASE("Base test 2") {
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
            .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
            .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
            .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
            .add_sub("COO", "VP_BI")
            .add_sub("CEO","CGO");      // Now the VP_BI is subordinate to the COO

            CHECK_THROWS(organization.get_manager("CEO"));
            CHECK_EQ(organization.get_manager("CTO") == "CEO", true);
            CHECK_EQ(organization.get_manager("CFO") == "CEO", true);
            CHECK_EQ(organization.get_manager("COO") == "CEO", true);
            CHECK_EQ(organization.get_manager("VP_SW") == "CTO", true);
            CHECK_EQ(organization.get_manager("VP_BI") == "COO", true);
            CHECK_THROWS(organization.get_manager("Something"));
            CHECK_EQ(organization.get_manager("CGO") == "CEO", true);
            CHECK_THROWS(organization.get_manager("UFO"));
            CHECK_EQ(organization.get_root() == "CEO", true);
            organization.add_root("MAFKAL");
            CHECK_NE(organization.get_root() == "CEO", true);
            CHECK_EQ(organization.get_root() == "MAFKAL", true);

            CHECK_THROWS(organization.add_sub("MATAN","CEO"));
            CHECK_THROWS(organization.add_sub("MATAN","YOSI"));
}