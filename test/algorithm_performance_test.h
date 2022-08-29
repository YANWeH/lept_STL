/*************************************************************************
	> File Name: algorithm_performance_test.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Wed 10 Aug 2022 02:28:48 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_ALGORITHM_PERFORMANCE_TEST_H__
#define LEPTSTL_ALGORITHM_PERFORMANCE_TEST_H__ 

/* 仅针对sort，binary_serch做性能测试*/
#include <algorithm>

#include "../leptSTL/algorithm.h"
#include "lept_test.h"

namespace leptstl 
{
    namespace test 
    {
        namespace algorithm_performance_test 
        {
            /*函数性能测试宏定义 */
#define FUN_TEST1(mode, fun, count) do {                        \
    std::string fun_name = #fun;                                \
    srand((int)time(0));                                        \
    char buf[10];                                               \
    clock_t start, end;                                         \
    int* arr = new int[count];                                  \
    for(size_t i = 0; i < count; ++i) *(arr + i) = rand();      \
    start = clock();                                            \
    mode::fun(arr, arr + count);                                \
    end = clock();                                              \
    int n = static_cast<int>(                                   \
            static_cast<double>(end - start)                    \
            / CLOCKS_PER_SEC * 1000);                           \
    std::snprintf(buf, sizeof(buf), "%d", n);                   \
    std::string t = buf;                                        \
    t += "ms    |";                                             \
    cout << std::setw(WIDE) << t;                               \
    delete []arr;                                               \
} while(0)

#define FUN_TEST2(mode, fun, count) do {                        \
    std::string fun_name = #fun;                                \
    srand((int)time(0));                                        \
    char buf[10];                                               \
    clock_t start, end;                                         \
    int* arr = new int[count];                                  \
    for(size_t i = 0; i < count; ++i) *(arr + i) = rand();      \
    start = clock();                                            \
    for(size_t i = 0; i < count; ++i)                           \
        mode::fun(arr, arr + count, rand());                    \
    end = clock();                                              \
    int n = static_cast<int>(                                   \
            static_cast<double>(end - start)                    \
            / CLOCKS_PER_SEC * 1000);                           \
    std::snprintf(buf, sizeof(buf), "%d", n);                   \
    std::string t = buf;                                        \
    t += "ms    |";                                             \
    cout << std::setw(WIDE) << t;                               \
    delete []arr;                                               \
} while(0)
            
            void binary_search_test()
            {
                cout << "[--------------- function : binary_search ---------------]" << std::endl;
                cout << "| orders of magnitude |";
                TEST_SCALE(LEN1, LEN2, LEN3, WIDE);
                cout << "|         std         |";
                FUN_TEST2(std, binary_search, LEN1);
                FUN_TEST2(std, binary_search, LEN2);
                FUN_TEST2(std, binary_search, LEN3);
                cout << std::endl;
                cout << "|       leptstl       |";
                FUN_TEST2(leptstl, binary_search, LEN1);
                FUN_TEST2(leptstl, binary_search, LEN2);
                FUN_TEST2(leptstl, binary_search, LEN3);
                cout << std::endl;
            }
            
            void sort_test()
            {
                cout << "[--------------- function : sort ------------------------]" << std::endl;
                cout << "| orders of magnitude |";
                TEST_SCALE(LEN1, LEN2, LEN3, WIDE);
                cout << "|         std         |";
                FUN_TEST1(std, sort, LEN1);
                FUN_TEST1(std, sort, LEN2);
                FUN_TEST1(std, sort, LEN3);
                cout << std::endl;
                cout << "|       leptstl       |";
                FUN_TEST1(leptstl, sort, LEN1);
                FUN_TEST1(leptstl, sort, LEN2);
                FUN_TEST1(leptstl, sort, LEN3);
                cout << std::endl;
            }

            void algorithm_performance_test()
            {
#if PERFORMANCE_TEST_ON 
                cout << "[============================================================]" << "\n";
                cout << "[---------------Run algorithm performance test---------------]" << "\n";
                sort_test();
                binary_search_test();
                cout << "[---------------End algorithm performance test---------------]" << "\n";
                cout << "[============================================================]" << "\n";
#endif /* PERFORMANCE_TEST_ON */
            }

        }   /* algorithm_performance_test */

    }   /* namespace test */
    
}   /* namespace leptstl */


#endif  /* LEPTSTL_ALGORITHM_PERFORMANCE_TEST_H__ */

