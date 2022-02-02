#ifndef MYTINYSTL_TEST_H_
#define MYTINYSTL_TEST_H_

// 一个简单的单元测试框架，定义了两个类 TestCase 和 UnitTest，以及一系列用于测试的宏

#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

#include "Lib/redbud/io/color.h"

namespace mystl
{
    namespace test
    {
        #define green redbud::io::state::manual << redbud::io::hfg::green
        #define red   redbud::io::state::manual << redbud::io::hfg::red

        #if defined(_MSC_VER)
        #pragma warning(disable : 4244)
        #pragma warning(disable : 4996)
        #endif
    }

    namespace test
    {
        // TestCase 类
        // 封装单个测试案例
        class TestCase
        {
            public:
                // 构造函数，接受一个字符串代表案例名称
                TestCase(const char * case_name) : testcase_name(case_name){}
                
                // 一个纯虚函数，用于测试案例
                virtual void Run() = 0;
            public:
                const char* testcase_name;  // 测试案例的名称
                int         nTestResult;    // 测试案例的执行结果 
                double      nFailed;        // 测试失败的案例数
                double      nPassed;        // 测试通过的案例数
        };

        // UnitTest 类
        // 单元测试，把所有测试案例加入到 vector 中，依次执行测试案例
        class UnitTest
        {
            public:
                // 获取一个案例
                static UnitTest* GetInstance();

                // 将案例依次加入 vector
                TestCase* RegisterTestCase(TestCase* testcase);

                void Run();

            public:
                TestCase* CurrentTestCase;          // 当前执行的测试案例
                double    nPassed;                  // 通过案例数
                double    nFailed;                  // 失败案例数

            protected:
                std::vector<TestCase*> testcases_;  // 保存案例集合
        };
    }
}

#endif