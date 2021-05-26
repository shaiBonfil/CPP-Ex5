#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <list>
#include <map>

enum class Order
{
    PRE,
    IN,
    POST
};

namespace ariel
{

    template <class T>
    class BinaryTree
    {
    private:
        struct Node
        {
            T _value;
            bool status;
            Node *left, *right, *parent;
            Node(T v) : _value(v), status(false), left(nullptr), right(nullptr), parent(nullptr) {}
            ~Node() {}
        };

        int size;
        std::map<T, Node *> nodes;
        Order order;
        Node *root = nullptr;

    public:
        BinaryTree<T>() : size(0) {}
        BinaryTree<T> add_root(const T &data)
        {
            if (root == nullptr)
            {
                size++;
                root = new Node(data);
                nodes[data] = root;
            }
            else
            {
                nodes[data] = root;
            }
            return *this;
        }

        BinaryTree<T> add_left(const T &p_node, const T &l_child)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is empty, you can't add left node");
            }
            if (nodes.count(p_node) == 0)
            {
                throw std::invalid_argument("the parent node dosen't exist");
            }
            if (nodes[p_node]->left == nullptr)
            {
                size++;
                nodes[p_node]->left = new Node(l_child);
                nodes[l_child] = nodes[p_node]->left;
                nodes[l_child]->parent = nodes[p_node];
            }
            else
            {
                nodes[p_node]->left->_value = l_child;
            }
            return *this;
        }

        BinaryTree<T> add_right(const T &p_node, const T &r_child)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is empty, you can't add left node");
            }
            if (nodes.count(p_node) == 0)
            {
                throw std::invalid_argument("the parent node dosen't exist");
            }
            if (nodes[p_node]->right == nullptr)
            {
                size++;
                nodes[p_node]->right = new Node(r_child);
                nodes[r_child] = nodes[p_node]->right;
                nodes[r_child]->parent = nodes[p_node];
            }
            else
            {
                nodes[p_node]->right->_value = r_child;
            }
            return *this;
        }

        class iterator
        {

        private:
            Order expression;
            Node *curr_node;
            std::list<T> l;

        public:
            iterator(Order order, Node *ptr = nullptr)
                : expression(order), curr_node(ptr) {}

            T &operator*() const
            {
                return curr_node->_value;
            }

            T *operator->() const
            {
                return &(curr_node->_value);
            }

            iterator &operator++()
            {
                switch (expression)
                {
                case Order::PRE:
                    if (!(curr_node->status))
                    {
                        l.push_back(curr_node->_value);
                        curr_node->status = true;
                        if (curr_node->left != nullptr)
                        {
                            curr_node = curr_node->left;
                        }
                        else if (curr_node->right != nullptr)
                        {
                            curr_node = curr_node->right;
                        }
                    }

                    break;

                case Order::IN:
                    if (curr_node != nullptr)
                    {
                        while (curr_node->left != nullptr)
                        {
                            curr_node = curr_node->left;
                        }
                        if (!(curr_node->status))
                        {
                            l.push_back(curr_node->_value);
                            curr_node->status = true;
                            curr_node = curr_node->parent;
                            l.push_back(curr_node->_value);
                            curr_node->status = true;
                        }
                        if (curr_node->right != nullptr)
                        {
                            curr_node = curr_node->right;
                        }
                    }
                    break;

                case Order::POST:
                    break;
                }
                return *this;
            }

            bool
            operator==(const iterator &other) const
            {
                return false;
            }

            bool operator!=(const iterator &other) const
            {
                return false;
            }
        };

        iterator begin_preorder()
        {
            return iterator(Order::PRE, root);
        }
        iterator end_preorder()
        {
            return iterator(Order::PRE, nullptr);
        }
        iterator begin_inorder()
        {
            return iterator(Order::IN, root);
        }
        iterator end_inorder()
        {
            return iterator(Order::IN, nullptr);
        }
        iterator begin_postorder()
        {
            return iterator(Order::POST, root);
        }
        iterator end_postorder()
        {
            return iterator(Order::POST, nullptr);
        }
        iterator begin()
        {
            return iterator(Order::IN, root);
        }
        iterator end()
        {
            return iterator(Order::IN, nullptr);
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &bt)
        {
            if (bt.root == nullptr)
            {
                return os;
            }
            std::stack<Node *> s;
            s.push(bt.root);

            while (!s.empty())
            {
                Node *node = s.top();
                os << node->_value << ", ";
                s.pop();
                if (node->right != nullptr)
                {
                    s.push(node->right);
                }
                if (node->left != nullptr)
                {
                    s.push(node->left);
                }
            }
            return os;
        }
    };
}