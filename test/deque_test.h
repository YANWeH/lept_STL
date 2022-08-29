/*************************************************************************
	> File Name: deque_test.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Sun 14 Aug 2022 07:28:17 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_DEQUE_TEST_H__
#define LEPTSTL_DEQUE_TEST_H__ 

#include <deque>

#include "../leptSTL/deque.h"
#include "lept_test.h"

namespace leptstl 
{
    namespace test 
    {
        namespace deque_test 
        {
            void deque_test()
			{
			  	cout << "[===============================================================]" << std::endl;
			  	cout << "[----------------- Run container test : deque ------------------]" << std::endl;
			  	cout << "[-------------------------- API test ---------------------------]" << std::endl;
			  	int a[] = { 1,2,3,4,5 };
			  	leptstl::deque<int> d1;
			  	leptstl::deque<int> d2(5);
			  	leptstl::deque<int> d3(5, 1);
			  	leptstl::deque<int> d4(a, a + 5);
			  	leptstl::deque<int> d5(d2);
			  	leptstl::deque<int> d6(std::move(d2));
			  	leptstl::deque<int> d7;
			  	d7 = d3;
			  	leptstl::deque<int> d8;
			  	d8 = std::move(d3);
			  	leptstl::deque<int> d9{ 1,2,3,4,5,6,7,8,9 };
			  	leptstl::deque<int> d10;
			  	d10 = { 1,2,3,4,5,6,7,8,9 };
			
			  	FUN_AFTER(d1, d1.assign(5, 1));
			  	FUN_AFTER(d1, d1.assign(8, 8));
			  	FUN_AFTER(d1, d1.assign(a, a + 5));
			  	FUN_AFTER(d1, d1.assign({ 1,2,3,4,5 }));
			  	FUN_AFTER(d1, d1.insert(d1.end(), 6));
			  	FUN_AFTER(d1, d1.insert(d1.end() - 1, 2, 7));
			  	FUN_AFTER(d1, d1.insert(d1.begin(), a, a + 5));
			  	FUN_AFTER(d1, d1.erase(d1.begin()));
			  	FUN_AFTER(d1, d1.erase(d1.begin(), d1.begin() + 4));
			  	FUN_AFTER(d1, d1.emplace_back(8));
			  	FUN_AFTER(d1, d1.emplace_front(8));
			  	FUN_AFTER(d1, d1.emplace(d1.begin() + 1, 9));
			  	FUN_AFTER(d1, d1.push_front(1));
			  	FUN_AFTER(d1, d1.push_back(2));
			  	FUN_AFTER(d1, d1.pop_back());
			  	FUN_AFTER(d1, d1.pop_front());
			  	FUN_AFTER(d1, d1.shrink_to_fit());
			  	FUN_AFTER(d1, d1.resize(5));
			  	FUN_AFTER(d1, d1.resize(8, 8));
			  	FUN_AFTER(d1, d1.clear());
			  	FUN_AFTER(d1, d1.shrink_to_fit());
			  	FUN_AFTER(d1, d1.swap(d4));
			  	FUN_VALUE(*(d1.begin()));
			  	FUN_VALUE(*(d1.end() - 1));
			  	FUN_VALUE(*(d1.rbegin()));
			  	FUN_VALUE(*(d1.rend() - 1));
			  	FUN_VALUE(d1.front());
			  	FUN_VALUE(d1.back());
			  	FUN_VALUE(d1.at(1));
			  	FUN_VALUE(d1[2]);
			  	cout << std::boolalpha;
			  	FUN_VALUE(d1.empty());
			  	cout << std::noboolalpha;
			  	FUN_VALUE(d1.size());
			  	FUN_VALUE(d1.max_size());
			  	/*PASSED;
			#if PERFORMANCE_TEST_ON
			  cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
			  cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
			  cout << "|     push_front      |";
			#if LARGER_TEST_DATA_ON
			  CON_TEST_P1(deque<int>, push_front, rand(), LEN1 _LL, LEN2 _LL, LEN3 _LL);
			#else
			  CON_TEST_P1(deque<int>, push_front, rand(), LEN1 _L, LEN2 _L, LEN3 _L);
			#endif
			  cout << std::endl;
			  cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
			  cout << "|     push_back       |";
			#if LARGER_TEST_DATA_ON
			  CON_TEST_P1(deque<int>, push_back, rand(), LEN1 _LL, LEN2 _LL, LEN3 _LL);
			#else
			  CON_TEST_P1(deque<int>, push_back, rand(), LEN1 _L, LEN2 _L, LEN3 _L);
			#endif
			  cout << std::endl;
			  cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
			  PASSED;
			#endif
			  cout << "[----------------- End container test : deque ------------------]" << std::endl;*/
			}

        }   /*namespace deque_test */

    }   /* namespace test */
    
}   /* namespace leptstl */


#endif  /* LEPTSTL_DEQUE_TEST_H__ */

