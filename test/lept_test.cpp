/*************************************************************************
	> File Name: lept_test.cpp
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Thu 28 Jul 2022 04:16:34 AM EDT
 ************************************************************************/

#include "lept_test.h"
#include "Lib/color.h"
#include<iostream>
using std::cout;

#include "vector_test.h"
#include "algorithm_performance_test.h"
#include "algorithm_test.h"
#include "list_test.h"
#include "deque_test.h"
#include "string_test.h"
#include "unordered_set_test.h"

int main()
{
    using namespace leptstl::test;
    //cout.sync_with_stdio(false);

    RUN_ALL_ALGORITHM_TESTS();
    vector_test::vector_test();
    algorithm_performance_test::algorithm_performance_test();
    list_test::list_test();
    deque_test::deque_test();
    string_test::string_test();
    unordered_set_test::unordered_set_test();
    unordered_set_test::unordered_multiset_test();

    return 0;
}

