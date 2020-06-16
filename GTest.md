# GTEST
gtest是一个跨平台的(Liunx、Mac OS X、Windows 、Cygwin 、Windows CE and Symbian ) C++单元测试框架，由google公司发布。gtest是为在不同平台上为编写C++测试而生成的。它提供了丰富的断言、致命和非致命判断、参数化、”死亡测试”等等。 

## 基本概念
要测试一个类或者函数，我们需要对其行为做出断言。当一个断言失败时，Google Test会在屏幕上输出该代码所在的源文件及其所在的位置行号，以及错误信息。也可以在编写断言时，提供一个自定义的错误信息，这个信息在失败时会被附加在Google Test的错误信息之后。

断言常常成对出现，他们都测试同一个类或者函数，但对当前功能有着不同的效果。ASSERT_*版本的断言失败时会产生致命失败，并结束当前函数。EXPECT_*版本的断言产生非致命失败，而不会中止当前函数。通常更推荐使用EXPECT_*断言，因为他们运行一个测试中可以有不止一个的错误被报告出来。但如果在编写断言如果失败，就没有必要继续往下执行的测试时，就应该使用ASSERT_*断言。因为失败的ASSERT_*断言会立即从当前的函数返回，可能会跳过其后的一些清洁代码，也许会导致空间泄漏。

## gtest系列之TEST宏
* TEST(test_case_name, test_name)
* TEST_F(test_fixture,test_name) //多个测试场景需要相同数据配置的情况，用TEST_F。TEST_F test fixture，测试夹具，测试套，承担了一个注册的功能。 

TestCase：字面意思，测试用例。为一个或多个方法提供测试方法，一般是一个test。  
TestSuite：测试集合,即一组测试。一个test suite是把多个相关测试归入一组的快捷方式。如果自己没有定义，Junit会自动提供一个test suite ,包括TestCase中的所有测试。  
TEST宏的作用是创建一个简单测试，它定义了一个测试函数，在这个函数里可以使用任何C++代码并使用提供的断言来进行检查。
## GTest的断言
 gtest中断言的宏可以分为两类：一类是ASSERT宏，另一类就是EXPECT宏了。
1. ASSERT_系列：如果当前点检测失败则退出当前函数

2. EXPECT_系列：如果当前点检测失败则继续往下执行 
如果你对自动输出的错误信息不满意的话，也是可以通过operator<<能够在失败的时候打印日志，将一些自定义的信息输出。 
* 布尔值检查
    * condition is true;期待结果是true  
    ASSERT_TRUE(condition);  
    EXPECT_TRUE(condition);  

    * 期待结果是false
    ASSERT_FALSE(condition);
    EXPECT_FALSE(condition);

* 数值型数据检查
    * expected == actual  传入的是需要比较的两个数 equal  
    ASSERT_EQ(expected,actual);
    EXPECT_EQ(expected,actual);  

    * val1 != val2  not equal，不等于才返回true  
    ASSERT_NE(val1, val2);  
    EXPECT_NE(val1, val2);  

    * val1 < val2  less than，小于才返回true  
    ASSERT_LT(val1, val2);  
    EXPECT_LT(val1, val2);  

    * val1 <= val2  less equal，小于等于才返回true
    ASSERT_LE(val1, val2);  
    EXPECT_LE(val1, val2);  

    * val1 > val2  greater than，大于才返回true
    ASSERT_GT(val1, val2);  
    EXPECT_GT(val1, val2);  

    * val1 >= val2  greater equal，大于等于才返回true
    ASSERT_GE(val1, val2);  
    EXPECT_GE(val1, val2);  

* 字符串比较
    * 两个C字符串有相同的内容
    ASSERT_STREQ(expected_str, actual_str);  
    EXPECT_STREQ(expected_str, actual_str);  

    * 两个C字符串有不同的内容  
    ASSERT_STRNE(str1, str2);  
    EXPECT_STRNE(str1, str2);  

    * 两个C字符串有相同的内容，忽略大小写  
    ASSERT_STRCASEEQ(expected_str, actual_str);  
    EXPECT_STRCASEEQ(expected_str, actual_str);  

    * 两个C字符串有不同的内容，忽略大小写  
    ASSERT_STRCASENE(str1, str2);  
    EXPECT_STRCASENE(str1, str2);  

## 事件机制
### 全局事件
要实现全局事件，必须写一个类**继承testing::Environment类**，实现里面的**SetUp**和**TearDown**方法。

1. SetUp()方法在所有案例执行前执行

2. TearDown()方法在所有案例执行后执行

还需要告诉gtest添加这个全局事件，我们需要在main函数中通过testing::AddGlobalTestEnvironment方法将事件挂进来，也就是说，我们可以写很多个这样的类，然后将他们的事件都挂上去。

### TestSuite事件
我们需要写一个类，**继承testing::Test**，然后实现两个静态方法

1. SetUpTestCase() 方法在第一个TestCase之前执行

2. TearDownTestCase() 方法在最后一个TestCase之后执行

在编写测试案例时，我们需要使用TEST_F这个宏，第一个参数必须是我们上面类的名字，代表一个TestSuite。

### TestCase事件
TestCase事件是挂在每个案例执行前后的，实现方式和上面的几乎一样，不过需要实现的是SetUp方法和TearDown方法：

1. SetUp()方法在每个TestCase之前执行

2. TearDown()方法在每个TestCase之后执行

## gtest系列之死亡测试
这里的”死亡”指的是程序的奔溃。通常在测试的过程中，我们需要考虑各种各样的输入，有的输入可能直接导致程序奔溃，这个时候我们就要检查程序是否按照预期的方式挂掉，这也就是所谓的”死亡测试”。 
* 死亡测试所用到的宏：

1. ASSERT_DEATH(参数1，参数2)，程序挂了并且错误信息和参数2匹配，此时认为测试通过。如果参数2为空字符串，则只需要看程序挂没挂即可。

2. ASSERT_EXIT(参数1，参数2，参数3)，语句停止并且错误信息和被提前给的信息匹配。