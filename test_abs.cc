#include<iostream>
#include<gtest/gtest.h>

int abs(int a)
{
    return  a > 0 ? a : -a; 
}


TEST(test_,test_abs)
{
    ASSERT_TRUE(abs(1) == 1) << "abs(1) = 1";
    ASSERT_TRUE(abs(-1) == 1) << "abs(-1) = 1";
    ASSERT_FALSE(abs(-2) == 2) << "abs(-2) = 2";; //期待结果是false
    EXPECT_EQ(abs(10),10);
    EXPECT_EQ(abs(10),abs(-10));
     
}


int main(int argc,char ** argv)
{   
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
    
}