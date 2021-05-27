#pragma once

#include <iostream>
#include <stack>
#include <queue>
#include <map>
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
            Node *left, *right, *parent;
            Node(T v) : _value(v), left(nullptr), right(nullptr), parent(nullptr) {}
            ~Node() {}
        };

        std::map<T, Node *> nodes;
        Order order;
        Node *root = nullptr;

    public:
        BinaryTree<T>() {}
        BinaryTree<T> add_root(const T &data)
        {
            if (root == nullptr)
            {
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
            std::queue<Node *> q;

        public:
            void preorder_fill(Node *root)
            {
                if (root != nullptr)
                {
                    q.push(root);
                    preorder_fill(root->left);
                    preorder_fill(root->right);
                }
            }

            void inorder_fill(Node *root)
            {
                if (root != nullptr)
                {
                    inorder_fill(root->left);
                    q.push(root);
                    inorder_fill(root->right);
                }
            }

            void postorder_fill(Node *root)
            {
                if (root != nullptr)
                {
                    postorder_fill(root->left);
                    postorder_fill(root->right);
                    q.push(root);
                }
            }

            iterator(Order order, Node *ptr = nullptr) : expression(order), curr_node(ptr)
            {
                switch (expression)
                {
                case Order::PRE:
                    preorder_fill(curr_node);
                    break;

                case Order::IN:
                    inorder_fill(curr_node);
                    break;

                case Order::POST:
                    postorder_fill(curr_node);
                    break;
                }
                q.push(nullptr);
                curr_node = q.front();
            }

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
                curr_node = q.front();
                q.pop();

                return *this;
            }

            // bool operator==(const iterator &other) const
            // {
            //     return curr_node->_value = other.curr_node->_value;
            // }

            bool operator!=(const iterator &other) const
            {
                return !q.empty();
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