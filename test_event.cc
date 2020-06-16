#include<gtest/gtest.h>
#include<map>
#include<iostream>

using namespace std;

class Student
{
    public:
        Student(){age = 0;}
        Student(int a){age = a;}
        void print(){
            cout << "*********" << age << "*************" << endl;
        }
    private:
        int age;

};

//全局事件
class FooEnvironment : public testing::Environment{
    public:
        virtual void SetUp()
        {
            std::cout << "foo fooenvironment setup" << std::endl;
        }
        virtual void TearDown()
        {
            std::cout << "foo fooenvironment teardown" << std::endl;
        }

};

static Student *s;

//TestSuite event
//在第一个test之前，最后一个test之后调用SetUpTestCase()和TearDownTestCase()
class TestMap : public testing::Test
{
    public:
    //实现两个静态方法
        static void SetUpTestCase()
        {
            cout << "setuptestcase()" << endl;
            s = new Student(23);
        }
        static void TearDownTestCase()
        {
            delete s;
            cout << "teardowntestcase()" << endl;
        }
    //testcase event
        void SetUp()
        {
           cout << "setup() is running" << endl;
        }
        void TearDown()
        {
             cout << "teardown()" << endl;
        }

};

TEST_F(TestMap,Test1)
{
    s->print();
}

int main(int argc, char** argv)
{
    testing :: AddGlobalTestEnvironment(new FooEnvironment);
    testing :: InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

//make: g++ test_event.cc  -lgtest -lpthread
