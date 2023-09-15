#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"

using namespace boost::property_tree;

TEST(property_tree, 读取配置信息) {
    ptree pt;
    xml_parser::read_xml("conf.xml", pt);

    std::cout << pt.get<std::string>("conf.theme") << std::endl;
    std::cout << pt.get<int>("conf.clock_style") << std::endl;
    std::cout << pt.get<long>("conf.gui") << std::endl;
    std::cout << pt.get("conf.no_prop", 1000) << std::endl;

    for (auto &x : pt.get_child("conf.urls")) {
        std::cout << x.second.data() << ", ";
    }
    std::cout << std::endl;
}

TEST(property_tree, 写入配置信息) {
    ptree pt;
    xml_parser::read_xml("conf.xml", pt);

    pt.put("conf.theme", "Matrix Reloaded");
    pt.put("conf.clock_style", 12);
    pt.put("conf.gui", 0);
    pt.put("conf.urls.url", "http://www.url4.org");

    xml_parser::write_xml(std::cout, pt);
}

TEST(property_tree, 更多用法) {
    
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
