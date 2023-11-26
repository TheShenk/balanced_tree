//
// Created by shenk on 25.11.23.
//

#ifndef BALANCED_TREE_TREE_H
#define BALANCED_TREE_TREE_H

#include <ostream>
#include <memory>
#include <optional>

template <typename ValueT>
class TreeNode: public std::enable_shared_from_this<TreeNode<ValueT>> {

    int m_height = 0;
    std::optional<ValueT> m_value;
    std::shared_ptr<TreeNode> m_left;
    std::shared_ptr<TreeNode> m_right;

    // based on https://habr.com/ru/articles/150732/
    // based on https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%92%D0%9B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
    auto rotateLeft() {
        auto node = m_right;
        m_right = node->m_left;
        node->m_left = this->shared_from_this();
        updateHeight();
        node->updateHeight();
        return node;
    }

    auto rotateRight() {
        auto node = m_left;
        m_left = node->m_right;
        node->m_right = this->shared_from_this();
        updateHeight();
        node->updateHeight();
        return node;
    }

    void updateHeight() {
        int heightLeft = m_left ? m_left->m_height : 0;
        int heightRight = m_right ? m_right->m_height : 0;
        m_height = std::max(heightLeft, heightRight) + 1;
    }

    auto balanced() {
        updateHeight();
        auto diff = heightDiff();
        if (diff == 2) {
            if (m_right->heightDiff() < 0) {
                m_right = m_right->rotateRight();
            }
            return rotateLeft();
        }
        if (diff == -2) {
            if (m_left->heightDiff() > 0) {
                m_left = m_left->rotateLeft();
            }
            return rotateRight();
        }
        return this->shared_from_this();
    }

public:

    const auto &value() const {
        return m_value;
    }

    const auto &left() const {
        return m_left;
    }

    const auto &right() const {
        return m_right;
    }

    auto find(const ValueT &value) const {
        if (m_value == value || (!m_left && !m_right)) return this->shared_from_this();
        if (value < m_value) return m_left->find(value);
        return m_right->find(value);
    }

    auto insert(const ValueT &value) {

        if (!m_value) {
            m_value = value;
            m_height = 1;
            return this->shared_from_this();
        }
        if (value < m_value) {
            if (!m_left) {
                m_left = std::make_shared<TreeNode>();
            }
            m_left = m_left->insert(value);
        } else if (value > m_value) {
            if (!m_right) {
                m_right = std::make_shared<TreeNode>();
            }
            m_right = m_right->insert(value);
        }
        return balanced();
    }

    int heightDiff() const {
        int heightLeft = m_left ? m_left->m_height : 0;
        int heightRight = m_right ? m_right->m_height : 0;
        return heightRight - heightLeft;
    }

    // based on https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    void print(std::ostream &os, const std::string &prefix = "", bool last = true) const {
        if (m_value) {
            os << prefix;
            os << (last ? "└──" : "├──");

            os << *m_value << std::endl;

            std::string nextPrefix = prefix + (last ? "\t" : "|\t");
            if (m_right) {
                m_right->print(os, nextPrefix, !m_left);
            }
            if (m_left) {
                m_left->print(os,  nextPrefix, true);
            }
        }
    }
};

template <typename ValueT>
class BinarySearchTree {
    std::shared_ptr<TreeNode<ValueT>> m_root;

public:

    BinarySearchTree(): m_root(std::make_shared<TreeNode<ValueT>>()) {}

    auto find(const ValueT &value) const {
        return m_root->find(value);
    }

    void insert(const ValueT &value) {
        m_root = m_root->insert(value);
    }

    void print(std::ostream &os) const {
        m_root->print(os);
    }

    const auto &root() {
        return m_root;
    }

};

template <typename ValueT>
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<ValueT> &tree) {
    tree.print(os);
    return os;
}

#endif //BALANCED_TREE_TREE_H
