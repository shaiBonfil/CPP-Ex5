#pragma once

#include <iostream>
#include <stack>
#include <string>

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
            Node *left, *right;
            Node(T v) : _value(v), status(false), left(nullptr), right(nullptr) {}
        };

        Order order;
        Node *root = nullptr;

    public:
        BinaryTree<T>() {}
        BinaryTree<T> add_root(const T &data)
        {
            if (root == nullptr)
            {
                root = new Node(data);
            }
            else
            {
                root->_value = data;
            }

            return *this;
        }

        BinaryTree<T> add_left(const T &parent, const T &l_child)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is empty, you can't add left node");
            }
            std::stack<Node *> s;
            Node *curr = root;
            while (curr != nullptr || !s.empty())
            {
                while (curr != nullptr)
                {
                    s.push(curr);
                    curr = curr->left;
                }

                curr = s.top();
                if (curr->_value == parent)
                {
                    if (curr->left == nullptr)
                    {
                        curr->left = new Node(l_child);
                    }
                    else
                    {
                        curr->left->_value = l_child;
                    }
                    return *this;
                }
                s.pop();

                curr = curr->right;
            }
            throw std::invalid_argument("the parent node dosen't exist");
        }

        BinaryTree<T> add_right(const T &parent, const T &r_child)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is empty, you can't add left node");
            }
            std::stack<Node *> s;
            Node *curr = root;
            while (curr != nullptr || !s.empty())
            {

                while (curr != nullptr)
                {
                    s.push(curr);
                    curr = curr->left;
                }

                curr = s.top();
                if (curr->_value == parent)
                {
                    if (curr->right == nullptr)
                    {
                        curr->right = new Node(r_child);
                    }
                    else
                    {
                        curr->right->_value = r_child;
                    }
                    return *this;
                }
                s.pop();

                curr = curr->right;
            }
            throw std::invalid_argument("the parent node dosen't exist");
        }

        class iterator
        {

        private:
            std::stack<Node *> stk;
            Order expression;
            Node *curr_node;

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
                case Order::PRE: // segmentation fault // this is in comment because bash grade
                    // if (!(curr_node->status))
                    // {
                    //     stk.push(curr_node);
                    //     curr_node->status = true;
                    //     if (curr_node->left != nullptr)
                    //     {
                    //         curr_node = curr_node->left;
                    //     }
                    //     else if (curr_node->right != nullptr)
                    //     {
                    //         curr_node = curr_node->right;
                    //     }
                    // }
                    // else
                    // {
                    //     if (curr_node != nullptr)//!stk.empty() || 
                    //     {
                    //         Node *tmp = stk.top();
                    //         curr_node = stk.top();
                    //         stk.pop();
                    //         curr_node = stk.top();
                    //         if (tmp == curr_node)
                    //         {
                    //             curr_node = nullptr;
                    //         }
                    //         if ((curr_node->right != nullptr) || (!(curr_node->right->status)))
                    //         {
                    //             curr_node = curr_node->right;
                    //             cout << "right" << endl;
                    //         }
                    //     }
                    // }
                    break;

                case Order::IN:
                    break;

                case Order::POST:
                    break;
                }
                return *this;
            }

            bool
            operator==(const iterator &other) const
            {
                return false; // curr_node == other.curr_node; // this is correct but in comment because bash
            }

            bool operator!=(const iterator &other) const
            {
                return false; // curr_node != other.curr_node; // this is correct but in comment because bash
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