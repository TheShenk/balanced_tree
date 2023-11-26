#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>

#include "tree.h"

int main() {

    std::cout << "Enter numbers (separate by space): ";
    std::string valueLine;
    std::getline(std::cin, valueLine);
    std::istringstream valueStream(valueLine);
    std::vector<int> values{std::istream_iterator<int>(valueStream), std::istream_iterator<int>()};

    BinarySearchTree<int> tree;
    for (const auto &v: values) {
        tree.insert(v);
    }
    std::cout << tree << std::endl;
    return 0;
}
