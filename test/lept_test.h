/*************************************************************************
	> File Name: lept_test.h
	> Author: YWH
	> Mail: 925957192@qq.com
	> Created Time: Thu 28 Jul 2022 04:25:55 AM EDT
 ************************************************************************/

#ifndef LEPTSTL_TEST_H__
#define LEPTSTL_TEST_H__ 

#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>  /* 控制cin cout 格式化 */
#include <string>
#include <sstream>  /* istringstream ostringstream 字符串流的输入输出 */
#include <vector>
#include "Lib/color.h"
using std::cout;

namespace leptstl 
{
    namespace test 
    {
#define green   finalres::io::state::manual << finalres::io::hfg::green 
#define red     finalres::io::state::manual << finalres::io::hfg::red 

        /* 封装单个测试案例*/
        class TestCase
        {
            public:
                /* 构造函数，接受一个字符串代表案例名称*/
                TestCase(const char* case_name):testcase_name(case_name) {}
                
                /*纯虚函数，用于测试案例*/
                virtual void Run() = 0;

            public:
                const char* testcase_name;  /*测试案例名称*/
                int         nTestResult;    /*测试案列结果*/
                double      nFailed;        /*案例失败数*/
                double      nPassed;        /*案例通过数*/
        };
    
        /*单元测试，将所有案例加入到vector中，依次执行测试案例*/
        class UnitTest
        {
            public:
                /* 获取一个案例*/
                static UnitTest* GetInstance();
                /*将案例依次加入vector中*/
                TestCase* RegisterTestCase(TestCase* testcase);
                void Run();

            public:
                TestCase* CurrentTestCase;      /*当前执行的测试案例*/
                double nFailed;                 /*案例失败数*/
                double nPassed;                 /*案例通过数*/

            protected:
                std::vector<TestCase*> testcases_set;    /*案例集合*/
        };

        UnitTest* UnitTest::GetInstance()
        {
            static UnitTest instance;
            return &instance;
        }

        TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
        {
            testcases_set.push_back(testcase);
            return testcase;
        }

        void UnitTest::Run()
        {
            for(auto& it:testcases_set)
            {
                TestCase* testcase = it;
                CurrentTestCase = testcase;
                testcase->nTestResult = 1;
                testcase->nFailed = 0;
                testcase->nPassed = 0;
                cout << green << "=============================================\n";
                cout << "Run TestCase:" << testcase->testcase_name << "\n";
                testcase->Run();
                if(testcase->nFailed > 0)
                    cout << red;
                cout << " " << testcase->nPassed << " / " << testcase->nFailed + testcase->nPassed 
                    << " Cases passed. ( " << testcase->nPassed / (testcase->nFailed + testcase->nPassed)*100
                    << "% )\n";
                cout << green << " End TestCase: " << testcase->testcase_name << "\n";
                if(testcase->nTestResult)
                    ++nPassed;
                else 
                    ++nFailed;
            }
            cout << "=============================================\n";
            cout << " Total TestCase : " << nPassed + nFailed << "\n";
            cout << " Total Passed : " << nPassed << "\n";
            cout << red << " Total Failed : " << nFailed << "\n";
            cout << green << " " << nPassed << " / " << nFailed + nPassed 
                << " TestCase nPassed. ( " << nPassed / (nFailed + nPassed)*100 << "% )\n";            
        }

        /**********************************************************************/
        /* 测试案例类名替换为 testcase_name_TEST */
#define TESTCASE_NAME(testcase_name) testcase_name##_TEST 

        /* 使用宏定义掩盖复杂的测试样例封装过程，把TEXT中的测试案例放入单元测试中 */
#define LEPTSTL_TEST_(testcase_name)                                \
        class TESTCASE_NAME(testcase_name) : public TestCase {      \
            public:                                                 \
                TESTCASE_NAME(testcase_name)(const char* case_name) \
                    :TestCase(case_name){};                         \
                virtual void Run();                                 \
            private:                                                \
                static TestCase* const testcase_;                   \
        };                                                          \
        TestCase* const TESTCASE_NAME(testcase_name)                \
        ::testcase_ = UnitTest::GetInstance()->RegisterTestCase(    \
                new TESTCASE_NAME(testcase_name)(#testcase_name));  \
        void TESTCASE_NAME(testcase_name)::Run() 

        /**************************************************************************/
        /*简单测试的宏定义*/

        /* 真假断言 
         * EXPECT_TRUE 
         * EXPECT_FALSE
         */
#define  EXPECT_TRUE(Condition) do {                                \
    if(Condition) {                                                 \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
        cout << green << " EXPECT_TRUE succeeded!\n";               \
    }                                                               \
    else {                                                          \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
        cout << red << " EXPECT_TRUE failed!\n";                    \
    }                                                               \
} while(0)

#define  EXPECT_FALSE(Condition) do {                               \
    if(!Condition) {                                                \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
        cout << green << " EXPECT_FALSE succeeded!\n";              \
    }                                                               \
    else {                                                          \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
        cout << red << " EXPECT_FALSE failed!\n";                   \
    }                                                               \
} while(0)
        
        /*  比较断言
         *  EXPECT_EQ   ==
         *  EXPECT_NE   !=
         *  EXPECT_LT   <
         *  EXPECT_LE   <=
         *  EXPECT_GT   >
         *  EXPECT_GE   >=
         */
#define EXPECT_EQ(expect, actual) do {                                  \
    if(expect == actual) {                                              \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_EQ succeeded!\n";                     \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_EQ failed!\n";                          \
        cout << " Expect:" << expect << "  Actual:" << actual << "\n";  \
    }                                                                   \
} while(0)

#define EXPECT_NE(expect, actual) do {                                  \
    if(expect != actual) {                                              \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_NE succeeded!\n";                     \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_NE failed!\n";                          \
        cout << " Expect:" << expect << "  Actual:" << actual << "\n";  \
    }                                                                   \
} while(0)

#define EXPECT_LT(expect, actual) do {                                  \
    if(expect < actual) {                                               \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_LT succeeded!\n";                     \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_LT failed!\n";                          \
        cout << " Expect:" << expect << "  Actual:" << actual << "\n";  \
    }                                                                   \
} while(0)

#define EXPECT_LE(expect, actual) do {                                  \
    if(expect <= actual) {                                              \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_LE succeeded!\n";                     \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_LE failed!\n";                          \
        cout << " Expect:" << expect << "  Actual:" << actual << "\n";  \
    }                                                                   \
} while(0)

#define EXPECT_GT(expect, actual) do {                                  \
    if(expect > actual) {                                               \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_GT succeeded!\n";                     \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_GT failed!\n";                          \
        cout << " Expect:" << expect << "  Actual:" << actual << "\n";  \
    }                                                                   \
} while(0)

#define EXPECT_GE(expect, actual) do {                                  \
    if(expect >= actual) {                                              \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_GE succeeded!\n";                     \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_GE failed!\n";                          \
        cout << " Expect:" << expect << "  Actual:" << actual << "\n";  \
    }                                                                   \
} while(0)

        /* 字符串比较char*
         * EXPECT_STREQ ==
         * EXPECT_STRNE !=
         * 如果想比较两个string对象用EXPECT_EQ EXPECT_NE 
         */
#define EXPECT_STREQ(s1, s2) do{                                        \
    if(s1 == NULL || s2 == NULL) {                                      \
        if(s1 == NULL && s2 == NULL){                                   \
            UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
            cout << green << " EXPECT_STREQ succeeded!\n";              \
        }                                                               \
        else {                                                          \
            UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
            UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
            cout << red << " EXPECT_STREQ failed!\n";                   \
            if(s1 == NULL) cout << " Expect:NULL\n";                    \
            else cout << " Expect:\"" << s1 << "\"\n";                  \
            if(s2 == NULL) cout << " Actual:NULL\n";                    \
            else cout << " Actual:\"" << s2 << "\"\n";                  \
        }                                                               \
    }                                                                   \
    else if(strcmp(s1, s2) == 0){                                       \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_STREQ succeeded!\n";                  \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_STREQ failed!\n";                       \
        cout << " Expect:\"" << s1 << "\"\n";                           \
        cout << " Actual:\"" << s2 << "\"\n";                           \
    }                                                                   \
} while(0)

#define EXPECT_STRNE(s1, s2) do{                                        \
    if(s1 == NULL || s2 == NULL) {                                      \
        if(s1 != NULL && s2 != NULL){                                   \
            UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
            cout << green << " EXPECT_STRNE succeeded!\n";              \
        }                                                               \
        else {                                                          \
            UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
            UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
            cout << red << " EXPECT_STRNE failed!\n";                   \
            if(s1 == NULL) cout << " Expect:NULL\n";                    \
            else cout << " Expect:\"" << s1 << "\"\n";                  \
            if(s2 == NULL) cout << " Actual:NULL\n";                    \
            else cout << " Actual:\"" << s2 << "\"\n";                  \
        }                                                               \
    }                                                                   \
    else if(strcmp(s1, s2) != 0){                                       \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;            \
        cout << green << " EXPECT_STREQ succeeded!\n";                  \
    }                                                                   \
    else {                                                              \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;      \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;            \
        cout << red << " EXPECT_STRNE failed!\n";                       \
        cout << " Expect:\"" << s1 << "\"\n";                           \
        cout << " Actual:\"" << s2 << "\"\n";                           \
    }                                                                   \
} while(0)

        /* 指针比较
         * EXPECT_PTRELEM_EQ        *p1==*p2
         * EXPECT_PTRELEM_NE        *p1!=*p2
         * EXPECT_PTRELEM_RANGE_EQ  (*p1+i)==(*p2+i)
         * EXPECT_PTRELEM_RANGE_NE  (*p1+i)!=(*p2+i)
         * 比较的是指针所指元素的值，若要比较指针地址使用EXPECT_EQ
         */
#define EXPECT_PTRELEM_EQ(p1, p2) do {                              \
    if(*p1 == *p2){                                                 \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
        cout << green << " EXPECT_PTRELEM_EQ succeeded!\n";         \
    }                                                               \
    else {                                                          \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
        cout << red << " EXPECT_PTRELEM_EQ failed!\n";              \
        cout << " Expect:" << *p1 << "  Actual:" << *p2 << "\n";    \
    }                                                               \
} while(0)

#define EXPECT_PTRELEM_NE(p1, p2) do {                              \
    if(*p1 != *p2){                                                 \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
        cout << green << " EXPECT_PTRELEM_NE succeeded!\n";         \
    }                                                               \
    else {                                                          \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
        cout << red << " EXPECT_PTRELEM_NE failed!\n";              \
        cout << " Expect:" << *p1 << "  Actual:" << *p2 << "\n";    \
    }                                                               \
} while(0)

#define EXPECT_PTRELEM_RANGE_EQ(p1, p2, len) do {                   \
    if(std::equal(p1, p1+len,p2)){                                  \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
        cout << green << " EXPECT_PTRELEM_RANGE_EQ succeeded!\n";   \
    }                                                               \
    else {                                                          \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
        cout << red << " EXPECT_PTRELEM_RANGE_EQ failed!\n";        \
    }                                                               \
} while(0)

#define EXPECT_PTRELEM_RANGE_NE(p1, p2, len) do {                   \
    if(!std::equal(p1, p1+len,p2)){                                 \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;        \
        cout << green << " EXPECT_PTRELEM_RANGE_NE succeeded!\n";   \
    }                                                               \
    else {                                                          \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;  \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;        \
        cout << red << " EXPECT_PTRELEM_RANGE_NE failed!\n";        \
    }                                                               \
} while(0)

        /* 容器比较
         * EXPECT_CON_EQ    ==
         * EXPECT_CON_NE    !=
         */
#define EXPECT_CON_EQ(c1, c2) do {                                          \
    auto first1 = std::begin(c1), last1 = std::end(c1);                     \
    auto first2 = std::begin(c2), last2 = std::end(c2);                     \
    for(; first1 != last1 && first2 != last2; ++first1, ++first2){          \
        if(*first1 != *first2) break;                                       \
    }                                                                       \
    if(first1 == last1 && first2 == last2){                                 \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;                \
        cout << green << " EXPECT_CON_EQ succeeded!\n";                     \
    }                                                                       \
    else {                                                                  \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;          \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;                \
        cout << red << " EXPECT_CON_EQ failed!\n";                          \
        cout << " Expect:" << *first1 << "  Actual:" << *first2 << "\n";    \
    }                                                                       \
} while(0)

#define EXPECT_CON_NE(c1, c2) do {                                          \
    auto first1 = std::begin(c1), last1 = std::end(c1);                     \
    auto first2 = std::begin(c2), last2 = std::end(c2);                     \
    for(; first1 != last1 && first2 != last2; ++first1, ++first2){          \
        if(*first1 != *first2) break;                                       \
    }                                                                       \
    if(first1 != last1 || first2 != last2){                                 \
        UnitTest::GetInstance()->CurrentTestCase->nPassed++;                \
        cout << green << " EXPECT_CON_NE succeeded!\n";                     \
    }                                                                       \
    else {                                                                  \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0;          \
        UnitTest::GetInstance()->CurrentTestCase->nFailed++;                \
        cout << red << " EXPECT_CON_NE failed!\n";                          \
    }                                                                       \
} while(0)

        /*********************************************************/
        /*常用的宏定义 */
#if defined (_DEBUG) || defined (DEBUG)
#define LEN1    10000
#define LEN2    100000
#define LEN3    1000000
#else 
#define LEN1    100000
#define LEN2    1000000
#define LEN3    10000000
#endif 

#define _LLL * 20
#define _LL  * 10
#define  _L  * 5
#define _M 
#define _S   / 5
#define _SS  / 10
#define _SSS / 20

#define WIDE   14

/* 输出通过提示*/
#define PASSED cout << "[ PASSED ]\n"

/* 遍历并输出容器*/
#define COUT(container) do {                            \
    std::string con_name = #container;                  \
    cout << " " << con_name << " :";                    \
    for(auto it : container)                            \
        cout << " " << it;                              \
    cout << "\n";                                       \
} while(0)

#define STR_COUT(str) do{                               \
    std::string str_name = #str;                        \
    cout << " " << str_name << " :" << str << "\n";     \
} while(0)

/* 输出容器调用函数后的结果 */
#define FUN_AFTER(con, fun) do {                        \
    std::string fun_name = #fun;                        \
    cout << " After " << fun_name << " :\n";            \
    fun;                                                \
    COUT(con);                                          \
} while(0)

#define STR_FUN_AFTER(str, fun) do {                    \
    std::string fun_name = #fun;                        \
    cout << " After " << fun_name << " :\n";            \
    fun;                                                \
    STR_COUT(str);                                      \
} while(0)

/* 输出容器调用函数的值*/
#define FUN_VALUE(fun) do {                             \
    std::string fun_name = #fun;                        \
    cout << " " << fun_name << " : " << fun << "\n";    \
} while(0)

/* 输出测试数量级*/
void test_scale(size_t scale1, size_t scale2, size_t scale3, size_t wide)
{
    std::string str1, str2, str3;
    std::stringstream ss;
    ss << scale1 << " " << scale2 << " " << scale3;
    ss >> str1 >> str2 >> str3;
    str1 += "   |";
    cout << std::setw(wide) << str1;
    str2 += "   |";
    cout << std::setw(wide) << str2;
    str3 += "   |";
    cout << std::setw(wide) << str3;
    cout << "\n";
}

#define TEST_SCALE(scale1, scale2, scale3, wide) test_scale(scale1, scale2, scale3, wide)

/* 常用测试性能的宏定义*/
#define FUN_TEST_FORMAT1(mode, fun, arg, count) do {            \
    srand((int)time(0));                                        \
    clock_t start, end;                                         \
    mode c;                                                     \
    char buf[10];                                               \
    start = clock();                                            \
    for(size_t i = 0; i < count; ++i)                           \
        c.fun(arg);                                             \
    end = clock();                                              \
    int n = static_cast<int>(                                   \
            static_cast<double>(end-start)                      \
            / CLOCKS_PER_SEC * 1000);                           \
    std::snprintf(buf, sizeof(buf), "%d", n);                   \
    std::string t = buf;                                        \
    t += "ms    |";                                             \
    cout << std::setw(WIDE) << t;                               \
} while(0)

#define FUN_TEST_FORMAT2(mode, fun, arg1, arg2, count) do {     \
    srand((int)time(0));                                        \
    clock_t start, end;                                         \
    mode c;                                                     \
    char buf[10];                                               \
    start = clock();                                            \
    for(size_t i = 0; i < count; ++i)                           \
        c.fun(c.arg1(), arg2);                                  \
    end = clock();                                              \
    int n = static_cast<int>(                                   \
            static_cast<double>(end-start)                      \
            / CLOCKS_PER_SEC * 1000);                           \
    std::snprintf(buf, sizeof(buf), "%d", n);                   \
    std::string t = buf;                                        \
    t += "ms    |";                                             \
    cout << std::setw(WIDE) << t;                               \
}while(0)

#define LIST_SORT_DO_TEST(mode, count) do {                        \
    srand((int)time(0));                                        \
    clock_t start, end;                                         \
    mode::list<int> l;                                          \
    char buf[10];                                               \
    for(size_t i = 0; i < count; ++i)                           \
        l.insert(l.end(), rand());                              \
    start = clock();                                            \
    l.sort();                                                   \
    end = clock();                                              \
    int n = static_cast<int>(                                   \
            static_cast<double>(end-start)                      \
            / CLOCKS_PER_SEC * 1000);                           \
    std::snprintf(buf, sizeof(buf), "%d", n);                   \
    std::string t = buf;                                        \
    t += "ms    |";                                             \
    cout << std::setw(WIDE) << t;                               \
} while(0)

#define MAP_EMPLACE_DO_TEST(mode, con, count) do {                 \
    srand((int)time(0));                                        \
    clock_t start, end;                                         \
    mode::con<int, int> c;                                      \
    char buf[10];                                               \
    start = clock();                                            \
    for(size_t i = 0; i < count; ++i)                           \
        c.emplace(mode::make_pair(rand(), rand()));             \
    end = clock();                                              \
    int n = static_cast<int>(                                   \
            static_cast<double>(end-start)                      \
            / CLOCKS_PER_SEC * 1000);                           \
    std::snprintf(buf, sizeof(buf), "%d", n);                   \
    std::string t = buf;                                        \
    t += "ms    |";                                             \
    cout << std::setw(WIDE) << t;                               \
} while(0)

/* 重构重复代码*/
#define CON_TEST_P1(con, fun, arg, scale1, scale2, scale3)          \
    TEST_SCALE(scale1, scale2, scale3, WIDE);                       \
    cout << "|         std         |";                              \
    FUN_TEST_FORMAT1(std::con, fun, arg, scale1);                   \
    FUN_TEST_FORMAT1(std::con, fun, arg, scale2);                   \
    FUN_TEST_FORMAT1(std::con, fun, arg, scale3);                   \
    cout << "\n|      leptstl        |";                            \
    FUN_TEST_FORMAT1(leptstl::con, fun, arg, scale1);               \
    FUN_TEST_FORMAT1(leptstl::con, fun, arg, scale2);               \
    FUN_TEST_FORMAT1(leptstl::con, fun, arg, scale3);

#define CON_TEST_P2(con, fun, arg1, arg2, scale1, scale2, scale3)   \
    TEST_SCALE(scale1, scale2, scale3, WIDE);                       \
    cout << "|         std         |";                              \
    FUN_TEST_FORMAT2(std::con, fun, arg1, arg2, scale1);            \
    FUN_TEST_FORMAT2(std::con, fun, arg1, arg2, scale2);            \
    FUN_TEST_FORMAT2(std::con, fun, arg1, arg2, scale3);            \
    cout << "\n|      leptstl        |";                            \
    FUN_TEST_FORMAT2(leptstl::con, fun, arg1, arg2, scale1);        \
    FUN_TEST_FORMAT2(leptstl::con, fun, arg1, arg2, scale2);        \
    FUN_TEST_FORMAT2(leptstl::con, fun, arg1, arg2, scale3);

#define MAP_EMPLACE_TEST(con, scale1, scale2, scale3)               \
    TEST_SCALE(scale1, scale2, scale3, WIDE);                       \
    cout << "|         std         |";                              \
    MAP_EMPLACE_DO_TEST(std, con, scale1);                          \
    MAP_EMPLACE_DO_TEST(std, con, scale2);                          \
    MAP_EMPLACE_DO_TEST(std, con, scale3);                          \
    cout << "\n|      leptstl        |";                            \
    MAP_EMPLACE_DO_TEST(leptstl, con, scale1);                      \
    MAP_EMPLACE_DO_TEST(leptstl, con, scale2);                      \
    MAP_EMPLACE_DO_TEST(leptstl, con, scale3);               

#define LIST_SORT_TEST(scale1, scale2, scale3)                      \
    TEST_SCALE(scale1, scale2, scale3, WIDE);                       \
    cout << "|         std         |";                              \
    LIST_SORT_DO_TEST(std, scale1);                                 \
    LIST_SORT_DO_TEST(std, scale2);                                 \
    LIST_SORT_DO_TEST(std, scale3);                                 \
    cout << "\n|      leptstl        |";                            \
    LIST_SORT_DO_TEST(leptstl, scale1);                             \
    LIST_SORT_DO_TEST(leptstl, scale2);                             \
    LIST_SORT_DO_TEST(leptstl, scale3);                          

/* 简单测试的宏定义*/
#define TEST(testcase_name) LEPTSTL_TEST_(testcase_name)

/* 运行所有测试案例*/
#define RUN_ALL_ALGORITHM_TESTS() leptstl::test::UnitTest::GetInstance()->Run()

/* 是否开启性能测试*/
#ifndef PERFORMANCE_TEST_ON
#define PERFORMANCE_TEST_ON 1
#endif 

/*是否开启大数据量测试*/
#ifndef LARGER_TEST_DATA_ON
#define LARGER_TEST_DATA_ON 0
#endif 

    }   /* namespace test */
}       /* namespace leptstl */
#endif /* LEPTSTL_TEST_H__ */

