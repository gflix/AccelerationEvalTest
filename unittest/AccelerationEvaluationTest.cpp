#include <gtest/gtest.h>
extern "C"
{
    #include <AccelerationEvaluation.h>
}

TEST(AccelerationEvaluationTest, initsVertex)
{
    // setup
    Vertex test;

    Vertex expected;
    expected.x = 0;
    expected.y = 0;
    expected.z = 0;

    // exercise
    initVertex(&test);

    // verify
    EXPECT_EQ(expected.x, test.x);
    EXPECT_EQ(expected.y, test.y);
    EXPECT_EQ(expected.z, test.z);
}

TEST(AccelerationEvaluationTest, initsAccelerationEvaluationState)
{
    // setup
    AccelerationEvaluationState test;

    AccelerationEvaluationState expected;
    expected.latchEnable = false;
    expected.currentSample.x = 0;
    expected.currentSample.y = 0;
    expected.currentSample.z = 0;
    expected.maxPlaneYZ.x = 0;
    expected.maxPlaneYZ.y = 0;
    expected.maxPlaneYZ.z = 0;
    expected.maxPlaneXZ.x = 0;
    expected.maxPlaneXZ.y = 0;
    expected.maxPlaneXZ.z = 0;
    expected.maxPlaneXY.x = 0;
    expected.maxPlaneXY.y = 0;
    expected.maxPlaneXY.z = 0;

    // exercise
    initAccelerationEvaluationState(&test);

    // verify
    EXPECT_EQ(expected.latchEnable, test.latchEnable);
    EXPECT_EQ(expected.currentSample.x, test.currentSample.x);
    EXPECT_EQ(expected.currentSample.y, test.currentSample.y);
    EXPECT_EQ(expected.currentSample.z, test.currentSample.z);
    EXPECT_EQ(expected.maxPlaneYZ.x, test.maxPlaneYZ.x);
    EXPECT_EQ(expected.maxPlaneYZ.y, test.maxPlaneYZ.y);
    EXPECT_EQ(expected.maxPlaneYZ.z, test.maxPlaneYZ.z);
    EXPECT_EQ(expected.maxPlaneXZ.x, test.maxPlaneXZ.x);
    EXPECT_EQ(expected.maxPlaneXZ.y, test.maxPlaneXZ.y);
    EXPECT_EQ(expected.maxPlaneXZ.z, test.maxPlaneXZ.z);
    EXPECT_EQ(expected.maxPlaneXY.x, test.maxPlaneXY.x);
    EXPECT_EQ(expected.maxPlaneXY.y, test.maxPlaneXY.y);
    EXPECT_EQ(expected.maxPlaneXY.z, test.maxPlaneXY.z);
}
