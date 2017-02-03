#include <gtest\gtest.h>

#include <someclass.h>


TEST(testMath, addTest)
{
	Math t;
	EXPECT_EQ(100, t.add(90, 10));
}