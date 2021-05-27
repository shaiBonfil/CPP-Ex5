#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "doctest.h"
#include "BinaryTree.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Binary tree of type int")
{
    BinaryTree<int> bt;
    CHECK_THROWS(bt.add_left(1, 8)); // the tree dosen't has a root
    CHECK_NOTHROW(bt.add_root(4));
    CHECK_NOTHROW(bt.add_left(4, 2));
    CHECK_NOTHROW(bt.add_right(4, 6));
    CHECK_NOTHROW(bt.add_left(2, 1));
    CHECK_NOTHROW(bt.add_right(2, 3));
    CHECK_NOTHROW(bt.add_left(6, 5));
    CHECK_NOTHROW(bt.add_right(6, 7));
    CHECK_NOTHROW(bt.add_root(10));     // change 4 to 10
    CHECK_NOTHROW(bt.add_right(6, 21)); // change 7 to 21
    CHECK_THROWS(bt.add_left(100, 7));  // 100 dosen't exist in the tree

    vector<int> pre1 = {10, 2, 1, 3, 6, 5, 21};
    vector<int> in1 = {1, 2, 3, 10, 5, 6, 21};
    vector<int> post1 = {1, 3, 2, 5, 21, 6, 10};

    vector<int>::iterator pre_it1 = pre1.begin();
    vector<int>::iterator pre_it1_end = pre1.end();
    auto pre_my_it1 = bt.begin_preorder();
    auto pre_my_it1_end = bt.end_preorder();

    for (; (pre_it1 != pre_it1_end) && (pre_my_it1 != pre_my_it1_end); ++pre_it1, ++pre_my_it1)
    {
        CHECK((*pre_my_it1) == (*pre_it1));
    }

    vector<int>::iterator in_it1 = in1.begin();
    vector<int>::iterator in_it1_end = in1.end();
    auto in_my_it1 = bt.begin_inorder();
    auto in_my_it1_end = bt.end_inorder();

    for (; (in_it1 != in_it1_end) && (in_my_it1 != in_my_it1_end); ++in_it1, ++in_my_it1)
    {
        CHECK((*in_my_it1) == (*in_it1));
    }

    vector<int>::iterator post_it1 = post1.begin();
    vector<int>::iterator post_it1_end = post1.end();
    auto post_my_it1 = bt.begin_postorder();
    auto post_my_it1_end = bt.end_postorder();

    for (; (post_it1 != post_it1_end) && (post_my_it1 != post_my_it1_end); ++post_it1, ++post_my_it1)
    {
        CHECK((*post_my_it1) == (*post_it1));
    }
}
//     // now I change the tree again and then traverse with the iterators
//     CHECK_NOTHROW(bt.add_right(2, 9)); // change 3 to 9
//     CHECK_NOTHROW(bt.add_left(6, 45)); // change 5 to 45
//     CHECK_THROWS(bt.add_left(100, 7)); // 100 dosen't exist in the tree

//     vector<int> pre2 = {10, 2, 1, 9, 6, 45, 21};
//     vector<int> in2 = {1, 2, 9, 10, 45, 6, 21};
//     vector<int> post2 = {1, 9, 2, 45, 21, 6, 10};

//     vector<int>::iterator pre_it2 = pre2.begin();
//     vector<int>::iterator pre_it2_end = pre2.end();
//     auto pre_my_it2 = bt.begin_preorder();
//     auto pre_my_it2_end = bt.end_preorder();

//     for (; (pre_it2 != pre_it2_end) && (pre_my_it2 != pre_my_it2_end); ++pre_it2, ++pre_my_it2)
//     {
//         CHECK((*pre_my_it2) == (*pre_it2));
//     }

//     vector<int>::iterator in_it2 = in2.begin();
//     vector<int>::iterator in_it2_end = in2.end();
//     auto in_my_it2 = bt.begin_inorder();
//     auto in_my_it2_end = bt.end_inorder();

//     for (; (in_it2 != in_it2_end) && (in_my_it2 != in_my_it2_end); ++in_it2, ++in_my_it2)
//     {
//         CHECK((*in_my_it2) == (*in_it2));
//     }

//     vector<int>::iterator post_it2 = post2.begin();
//     vector<int>::iterator post_it2_end = post2.end();
//     auto post_my_it2 = bt.begin_postorder();
//     auto post_my_it2_end = bt.end_postorder();

//     for (; (post_it2 != post_it2_end) && (post_my_it2 != post_my_it2_end); ++post_it2, ++post_my_it2)
//     {
//         CHECK((*post_my_it2) == (*post_it2));
//     }
// }

// TEST_CASE("Binary tree of type string")
// {
//     BinaryTree<string> bt;
//     CHECK_THROWS(bt.add_left("throw", "error"));    // the tree dosen't has a root
//     CHECK_NOTHROW(bt.add_root("root"));
//     CHECK_NOTHROW(bt.add_left("root", "is"));
//     CHECK_NOTHROW(bt.add_right("root", "in"));
//     CHECK_NOTHROW(bt.add_left("is", "shai"));
//     CHECK_NOTHROW(bt.add_right("is", "test"));
//     CHECK_NOTHROW(bt.add_left("in", "cpp"));
//     CHECK_NOTHROW(bt.add_right("in", "ex5"));
//     CHECK_NOTHROW(bt.add_root("this"));             // change "root" to "this"
//     CHECK_NOTHROW(bt.add_left("in", "c++"));        // change "cpp" to "c++"
//     CHECK_THROWS(bt.add_left("another", "error"));  // "another" dosen't exist in the tree

//     vector<string> pre3 = {"this", "is", "shai", "test", "in", "c++", "ex5"};
//     vector<string> in3 = {"shai", "is", "test", "this", "c++", "in", "ex5"};
//     vector<string> post3 = {"shai", "test", "is", "c++", "ex5", "in", "this"};

//     vector<string>::iterator pre_it3 = pre3.begin();
//     vector<string>::iterator pre_it3_end = pre3.end();
//     auto pre_my_it3 = bt.begin_preorder();
//     auto pre_my_it3_end = bt.end_preorder();

//     for (; (pre_it3 != pre_it3_end) && (pre_my_it3 != pre_my_it3_end); ++pre_it3, ++pre_my_it3)
//     {
//         CHECK((*pre_my_it3) == (*pre_it3));
//     }

//     vector<string>::iterator in_it3 = in3.begin();
//     vector<string>::iterator in_it3_end = in3.end();
//     auto in_my_it3 = bt.begin_inorder();
//     auto in_my_it3_end = bt.end_inorder();

//     for (; (in_it3 != in_it3_end) && (in_my_it3 != in_my_it3_end); ++in_it3, ++in_my_it3)
//     {
//         CHECK((*in_my_it3) == (*in_it3));
//     }

//     vector<string>::iterator post_it3 = post3.begin();
//     vector<string>::iterator post_it3_end = post3.end();
//     auto post_my_it3 = bt.begin_postorder();
//     auto post_my_it3_end = bt.end_postorder();

//     for (; (post_it3 != post_it3_end) && (post_my_it3 != post_my_it3_end); ++post_it3, ++post_my_it3)
//     {
//         CHECK((*post_my_it3) == (*post_it3));
//     }

//     // now I change the tree again and then traverse with the iterators
//     CHECK_NOTHROW(bt.add_right("this", "with"));   // change "in" to "with"
//     CHECK_NOTHROW(bt.add_left("with", "changes")); // change "c++" to "changes"
//     CHECK_THROWS(bt.add_left("another", "error")); // "another" dosen't exist in the tree

//     vector<string> pre4 = {"this", "is", "shai", "test", "with", "changes", "ex5"};
//     vector<string> in4 = {"shai", "is", "test", "this", "changes", "with", "ex5"};
//     vector<string> post4 = {"shai", "test", "is", "changes", "ex5", "with", "this"};

//     vector<string>::iterator pre_it4 = pre4.begin();
//     vector<string>::iterator pre_it4_end = pre4.end();
//     auto pre_my_it4 = bt.begin_preorder();
//     auto pre_my_it4_end = bt.end_preorder();

//     for (; (pre_it4 != pre_it4_end) && (pre_my_it4 != pre_my_it4_end); ++pre_it4, ++pre_my_it4)
//     {
//         CHECK((*pre_my_it4) == (*pre_it4));
//     }

//     vector<string>::iterator in_it4 = in4.begin();
//     vector<string>::iterator in_it4_end = in4.end();
//     auto in_my_it4 = bt.begin_inorder();
//     auto in_my_it4_end = bt.end_inorder();

//     for (; (in_it4 != in_it4_end) && (in_my_it4 != in_my_it4_end); ++in_it4, ++in_my_it4)
//     {
//         CHECK((*in_my_it4) == (*in_it4));
//     }

//     vector<string>::iterator post_it4 = post4.begin();
//     vector<string>::iterator post_it4_end = post4.end();
//     auto post_my_it4 = bt.begin_postorder();
//     auto post_my_it4_end = bt.end_postorder();

//     for (; (post_it4 != post_it4_end) && (post_my_it4 != post_my_it4_end); ++post_it4, ++post_my_it4)
//     {
//         CHECK((*post_my_it4) == (*post_it4));
//     }
// }