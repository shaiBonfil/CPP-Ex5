#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <stdexcept>

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
            Node *left, *right;
            Node(T v) : _value(v), left(nullptr), right(nullptr) {}
        };

        Order order;
        Node *root = nullptr;

    public:
        BinaryTree<T>() : order(Order::IN) {}
        ~BinaryTree<T>() {}

        void deep_copy(Node *&new_node, Node *&origin_node)
        {
            if (origin_node == nullptr)
            {
                new_node = nullptr;
            }
            else
            {
                new_node = new Node(origin_node->_value);
                deep_copy(new_node->left, origin_node->left);
                deep_copy(new_node->right, origin_node->right);
            }
        }

        BinaryTree<T>(BinaryTree<T> &other) : order(other.order)
        { //copy constractor
            if (other.root == nullptr)
            {
                root = nullptr;
            }
            else
            {
                deep_copy(this->root, other.root);
            }
        }

        BinaryTree<T> &operator=(BinaryTree<T> other)
        {
            if (this == &other)
            {
                return *this;
            }
            delete (this->root);
            root = new Node(other.root->_value);
            deep_copy(this->root, other.root);
            return *this;
        }

        BinaryTree<T>(BinaryTree<T> &&other) noexcept
        { //move constractor
            root = other.root;
            other.root = nullptr;
            order = other.order;
        }
        BinaryTree<T> &operator=(BinaryTree<T> &&other) noexcept
        { //move
            delete root;
            root = other.root;
            other.root = nullptr;
            return *this;
        }

        BinaryTree<T> &add_root(const T &val)
        {
            if (root == nullptr)
            {
                root = new Node(val);
            }
            else
            {
                root->_value = val;
            }
            return *this;
        }

        BinaryTree<T> &add_left(const T &p_node, const T &l_child)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is empty, you can't add left node");
            }
            std::queue<Node *> to_add;
            Node *curr_node = root;
            while (!to_add.empty() || curr_node != nullptr)
            {
                while (curr_node != nullptr)
                {
                    to_add.push(curr_node);
                    curr_node = curr_node->left;
                }
                curr_node = to_add.front();
                to_add.pop();
                if (curr_node->_value == p_node)
                {
                    if (curr_node->left == nullptr)
                    {
                        curr_node->left = new Node(l_child);
                    }
                    else
                    {
                        curr_node->left->_value = l_child;
                    }
                    return *this;
                }
                curr_node = curr_node->right;
            }
            throw std::invalid_argument("the parent node dosen't exist");
        }

        BinaryTree<T> &add_right(const T &p_node, const T &r_child)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("the tree is empty, you can't add left node");
            }
            std::queue<Node *> to_add;
            Node *curr_node = root;
            while (!to_add.empty() || curr_node != nullptr)
            {
                while (curr_node != nullptr)
                {
                    to_add.push(curr_node);
                    curr_node = curr_node->left;
                }
                curr_node = to_add.front();
                to_add.pop();
                if (curr_node->_value == p_node)
                {
                    if (curr_node->right == nullptr)
                    {
                        curr_node->right = new Node(r_child);
                    }
                    else
                    {
                        curr_node->right->_value = r_child;
                    }
                    return *this;
                }
                curr_node = curr_node->right;
            }
            throw std::invalid_argument("the parent node dosen't exist");
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

            iterator operator++(int)
            {
                curr_node = q.front();
                q.pop();

                return *this;
            }

            bool operator==(const iterator &other) const
            {
                return curr_node == other.curr_node;
            }

            bool operator!=(const iterator &other) const
            {
                return q.empty();
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
            return os;
        }
    };
}