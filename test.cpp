//
// Created by shenk on 25.11.23.
//

#include <gtest/gtest.h>
#include <random>

#include "tree.h"

auto generateRandomVector(std::size_t size) {

    std::random_device device;
    std::mt19937 engine(device());

    std::vector<int> numbers(2 * size, 0);
    std::iota(numbers.begin(), numbers.end(), 0);
    std::shuffle(numbers.begin(), numbers.end(), engine);

    for (int i=0; i<size; i++) {
        std::uniform_int_distribution<std::size_t> distribution(0, numbers.size());
        numbers.erase(std::next(numbers.begin(), distribution(engine)));
    }

    return numbers;
}

class BinarySearchTreeTest: public testing::Test {

public:
    void SetUp() override {
        for (const auto &value: m_treeValues) {
            m_tree.insert(value);
        }
        std::cout << m_tree << std::endl;
    }

protected:
    BinarySearchTree<int> m_tree;
    std::vector<int> m_treeValues = generateRandomVector(1000);
};

TEST_F(BinarySearchTreeTest, FindReturnNodewithValue) {
    for (const auto &value: m_treeValues) {
        auto node = m_tree.find(value);
        ASSERT_EQ(*node->value(), value);
    }
}

TEST_F(BinarySearchTreeTest, HeightDiffLessOrEqOne) {
    for (const auto &value: m_treeValues) {
        auto node = m_tree.find(value);
        ASSERT_TRUE(std::abs(node->heightDiff()) <= 1);
    }
}

template <typename ValueT, typename CallableT>
void forEveryInTree(const std::shared_ptr<TreeNode<ValueT>> &root, const CallableT &func) {
    if (root) {
        func(root);
        forEveryInTree(root->left(), func);
        forEveryInTree(root->right(), func);
    }
}

TEST_F(BinarySearchTreeTest, LeftSubTreeIsLessAndRightIsBigger) {
    for (const auto &value: m_treeValues) {
        auto node = m_tree.find(value);
        forEveryInTree(node->left(), [value](const auto& node) { ASSERT_TRUE(*node->value() < value); });
        forEveryInTree(node->right(), [value](const auto& node) { ASSERT_TRUE(*node->value() > value); });
        ASSERT_TRUE(std::abs(node->heightDiff()) <= 1);
    }
}