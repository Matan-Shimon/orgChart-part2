//
// Created by matan on 09/05/2022.
//
#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "sources/OrgChart.hpp"
using namespace ariel;
using namespace std;

// this test will check if the demo will present good answers
TEST_CASE("Base test 1") {
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")
            .add_sub("CEO", "CFO")
            .add_sub("CEO", "COO")
            .add_sub("CTO", "VP_SW")
            .add_sub("COO", "VP_BI");

    // Checking for basic operations, such as get manager
    CHECK_THROWS(organization.get_manager("CEO"));
    CHECK_EQ(organization.get_manager("CTO")->get_name() == "CEO", true);
    CHECK_EQ(organization.get_manager("CFO")->get_name() == "CEO", true);
    CHECK_EQ(organization.get_manager("COO")->get_name() == "CEO", true);
    CHECK_EQ(organization.get_manager("VP_SW")->get_name() == "CTO", true);
    CHECK_EQ(organization.get_manager("VP_BI")->get_name() == "COO", true);

    cout << organization << endl; // checking the output is good

    vector<string> names = {"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
    unsigned int index = 0;
    // checking the level order
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(*it == names.at(index), true);
        index++;
    }
    names = {"VP_SW", "VP_BI", "CTO", "CFO", "COO", "CEO"};
    index = 0;
    // checking the reverse level order
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(*it == names.at(index), true);
        index++;
    }
    names = {"CEO", "CTO", "VP_SW", "CFO", "COO", "VP_BI"};
    index = 0;
    // checking the pre order
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        CHECK_EQ(*it == names.at(index), true);
        index++;
    }

    vector<int> sizes = {3, 3, 3, 3, 5, 5};
    index = 0;
    // checking the iterator size in the level order
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(it->size() == sizes.at(index), true);
        index++;
    }
}
// this test will check a little more complex occasion
TEST_CASE("Base test 2") {
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
            .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
            .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
            .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
            .add_sub("COO", "VP_BI")
            .add_sub("CEO","CGO");      // Now the VP_BI is subordinate to the COO

            // checking for basic functions
            CHECK_THROWS(organization.get_manager("CEO")); // The "CEO" has no manager above
            CHECK_EQ(organization.get_manager("CTO")->get_name() == "CEO", true);
            CHECK_EQ(organization.get_manager("CFO")->get_name() == "CEO", true);
            CHECK_EQ(organization.get_manager("COO")->get_name() == "CEO", true);
            CHECK_EQ(organization.get_manager("VP_SW")->get_name() == "CTO", true);
            CHECK_EQ(organization.get_manager("VP_BI")->get_name() == "COO", true);
            // there is no worker named "Something"
            CHECK_THROWS(organization.get_manager("Something"));
            CHECK_EQ(organization.get_manager("CGO")->get_name() == "CEO", true);
            // there is no worker named "UFO"
            CHECK_THROWS(organization.get_manager("UFO"));
            CHECK_EQ(organization.get_root()->get_name() == "CEO", true);
            organization.add_root("MAFKAL");
            CHECK_NE(organization.get_root()->get_name() == "CEO", true);
            CHECK_EQ(organization.get_root()->get_name() == "MAFKAL", true);
            // there is no worker named "MATAN"
            CHECK_THROWS(organization.add_sub("MATAN","CEO"));
            CHECK_THROWS(organization.add_sub("MATAN","YOSI"));
}

TEST_CASE("Base test 3") {
    OrgChart chart;
    // validating that we can add a lot of root (by that, we will onl change their name) with no problem
    chart.add_root("Matan")
    .add_root("Matan")
    .add_root("Matan")
    .add_root("Matan")
    .add_root("Matan");

    for (int i = 0; i < 100; ++i) {
        chart.add_root("Shimon");
    }

    // check the first root name has been deleted
    CHECK_THROWS(chart.add_sub("Matan", "Yossi"));
    // checking for same multiple names
    CHECK_NOTHROW(chart.add_sub("Shimon", "Yossi"));
    CHECK_NOTHROW(chart.add_sub("Shimon", "Yossi"));
    CHECK_NOTHROW(chart.add_sub("Yossi", "Yossi"));

    // check for invalid characters
    CHECK_THROWS(chart.add_root(""));
    CHECK_THROWS(chart.add_sub("Shimon",""));

    CHECK_THROWS(chart.add_root(" "));
    CHECK_THROWS(chart.add_sub("Shimon"," "));

    CHECK_THROWS(chart.add_root("   "));
    CHECK_THROWS(chart.add_sub("Shimon","   "));

    CHECK_THROWS(chart.add_root("\n"));
    CHECK_THROWS(chart.add_sub("Shimon","\n"));

    CHECK_THROWS(chart.add_root("\t"));
    CHECK_THROWS(chart.add_sub("Shimon","\t"));

    CHECK_THROWS(chart.add_root("shi\rmon"));
    CHECK_THROWS(chart.add_sub("Shimon","yarin\r"));

    CHECK_THROWS(chart.add_root("\nshi\rmon"));
    CHECK_THROWS(chart.add_sub("Shimon","\nyarin\r"));

    CHECK_THROWS(chart.add_root("shi\rmon\t"));
    CHECK_THROWS(chart.add_sub("Shimon","y\trin\r"));
}