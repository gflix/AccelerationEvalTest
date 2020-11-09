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

TEST(AccelerationEvaluationTest, copiesVertex)
{
    // setup
    Vertex test;

    Vertex expected;
    expected.x = 1;
    expected.y = 2;
    expected.z = 4;

    // exercise
    copyVertex(&test, &expected);

    // verify
    EXPECT_EQ(expected.x, test.x);
    EXPECT_EQ(expected.y, test.y);
    EXPECT_EQ(expected.z, test.z);
}

TEST(AccelerationEvaluationTest, setsLatchEnableToAccelerationEvaluationState)
{
    // setup
    AccelerationEvaluationState test;
    initAccelerationEvaluationState(&test);

    // exercise
    setLatchEnable(&test, true);

    // verify
    EXPECT_TRUE(test.latchEnable);
}

TEST(AccelerationEvaluationTest, copiesCurrentSampleToMaxPlanesOnRisingEdgeOfLatchEnable)
{
    // setup
    AccelerationEvaluationState test;
    initAccelerationEvaluationState(&test);
    test.latchEnable = false;
    test.currentSample.x = -3;
    test.currentSample.y = 2;
    test.currentSample.z = -1;

    Vertex expected;
    copyVertex(&expected, &test.currentSample);

    // exercise
    setLatchEnable(&test, true);

    // verify
    EXPECT_EQ(test.currentSample.x, test.maxPlaneYZ.x);
    EXPECT_EQ(test.currentSample.y, test.maxPlaneYZ.y);
    EXPECT_EQ(test.currentSample.z, test.maxPlaneYZ.z);
    EXPECT_EQ(test.currentSample.x, test.maxPlaneXZ.x);
    EXPECT_EQ(test.currentSample.y, test.maxPlaneXZ.y);
    EXPECT_EQ(test.currentSample.z, test.maxPlaneXZ.z);
    EXPECT_EQ(test.currentSample.x, test.maxPlaneXY.x);
    EXPECT_EQ(test.currentSample.y, test.maxPlaneXY.y);
    EXPECT_EQ(test.currentSample.z, test.maxPlaneXY.z);
}

TEST(AccelerationEvaluationTest, doesNotCopyCurrentSampleToMaxPlanesOnFallingEdgeOfLatchEnable)
{
    // setup
    AccelerationEvaluationState test;
    initAccelerationEvaluationState(&test);
    test.latchEnable = true;
    test.currentSample.x = -3;
    test.currentSample.y = 2;
    test.currentSample.z = -1;

    Vertex expected;
    initVertex(&expected);

    // exercise
    setLatchEnable(&test, false);

    // verify
    EXPECT_EQ(expected.x, test.maxPlaneYZ.x);
    EXPECT_EQ(expected.y, test.maxPlaneYZ.y);
    EXPECT_EQ(expected.z, test.maxPlaneYZ.z);
    EXPECT_EQ(expected.x, test.maxPlaneXZ.x);
    EXPECT_EQ(expected.y, test.maxPlaneXZ.y);
    EXPECT_EQ(expected.z, test.maxPlaneXZ.z);
    EXPECT_EQ(expected.x, test.maxPlaneXY.x);
    EXPECT_EQ(expected.y, test.maxPlaneXY.y);
    EXPECT_EQ(expected.z, test.maxPlaneXY.z);
}

TEST(AccelerationEvaluationTest, doesNotEvaluateVertexWhenLatchIsNotEnabled)
{
    // setup
    AccelerationEvaluationState test;
    initAccelerationEvaluationState(&test);
    test.latchEnable = false;

    Vertex sample;
    initVertex(&sample);
    sample.x = -1;
    sample.y = 2;
    sample.z = -3;

    Vertex expected;
    initVertex(&expected);

    // exercise
    evaluateSample(&test, &sample);

    // verify
    EXPECT_EQ(sample.x, test.currentSample.x);  // current sample gets stored independently from latch enable
    EXPECT_EQ(sample.y, test.currentSample.y);
    EXPECT_EQ(sample.z, test.currentSample.z);
    EXPECT_EQ(expected.x, test.maxPlaneYZ.x);  // maxPlane values are not updated when latch is not enabled
    EXPECT_EQ(expected.y, test.maxPlaneYZ.y);
    EXPECT_EQ(expected.z, test.maxPlaneYZ.z);
    EXPECT_EQ(expected.x, test.maxPlaneXZ.x);
    EXPECT_EQ(expected.y, test.maxPlaneXZ.y);
    EXPECT_EQ(expected.z, test.maxPlaneXZ.z);
    EXPECT_EQ(expected.x, test.maxPlaneXY.x);
    EXPECT_EQ(expected.y, test.maxPlaneXY.y);
    EXPECT_EQ(expected.z, test.maxPlaneXY.z);
}

TEST(AccelerationEvaluationTest, evaluatesVertexWhenLatchIsEnabled)
{
    // setup
    AccelerationEvaluationState test;
    initAccelerationEvaluationState(&test);

    Vertex sample;
    initVertex(&sample);
    sample.x = -1;
    sample.y = 2;
    sample.z = -3;

    Vertex expected;
    copyVertex(&expected, &sample);

    setLatchEnable(&test, true);

    // exercise
    evaluateSample(&test, &sample);

    setLatchEnable(&test, false);

    // verify
    EXPECT_EQ(sample.x, test.currentSample.x);  // current sample gets stored independently from latch enable
    EXPECT_EQ(sample.y, test.currentSample.y);
    EXPECT_EQ(sample.z, test.currentSample.z);
    EXPECT_EQ(expected.x, test.maxPlaneYZ.x);  // maxPlane values are entirely updated when latch is enabled
    EXPECT_EQ(expected.y, test.maxPlaneYZ.y);
    EXPECT_EQ(expected.z, test.maxPlaneYZ.z);
    EXPECT_EQ(expected.x, test.maxPlaneXZ.x);
    EXPECT_EQ(expected.y, test.maxPlaneXZ.y);
    EXPECT_EQ(expected.z, test.maxPlaneXZ.z);
    EXPECT_EQ(expected.x, test.maxPlaneXY.x);
    EXPECT_EQ(expected.y, test.maxPlaneXY.y);
    EXPECT_EQ(expected.z, test.maxPlaneXY.z);
}

TEST(AccelerationEvaluationTest, evaluatesMultipleVertexesWhenLatchIsEnabled)
{
    // setup
    AccelerationEvaluationState test;
    initAccelerationEvaluationState(&test);

    Vertex samples[5];
    initVertex(&samples[0]);  // will modify maxPlaneYZ
    samples[0].x = -1;
    samples[0].y = 0;
    samples[0].z = 0;
    initVertex(&samples[1]);  // will modify maxPlaneXZ
    samples[1].x = 0;
    samples[1].y = 2;
    samples[1].z = 0;
    initVertex(&samples[2]);  // will modify maxPlaneXY
    samples[2].x = 0;
    samples[2].y = 0;
    samples[2].z = -3;
    initVertex(&samples[3]);  // will not modify any maxPlane
    samples[3].x = 1;
    samples[3].y = 1;
    samples[3].z = 1;
    initVertex(&samples[4]);  // will modify maxPlaneYZ and maxPlaneXZ
    samples[4].x = -2;
    samples[4].y = 3;
    samples[4].z = 0;

    setLatchEnable(&test, true);

    // exercise
    evaluateSample(&test, &samples[0]);
    evaluateSample(&test, &samples[1]);
    evaluateSample(&test, &samples[2]);
    evaluateSample(&test, &samples[3]);
    evaluateSample(&test, &samples[4]);

    setLatchEnable(&test, false);

    // verify
    EXPECT_EQ(samples[4].x, test.currentSample.x);  // latest sample gets stored independently from latch enable
    EXPECT_EQ(samples[4].y, test.currentSample.y);
    EXPECT_EQ(samples[4].z, test.currentSample.z);
    EXPECT_EQ(samples[4].x, test.maxPlaneYZ.x);  // maxPlaneYZ was latest updated by samples[4]
    EXPECT_EQ(samples[4].y, test.maxPlaneYZ.y);
    EXPECT_EQ(samples[4].z, test.maxPlaneYZ.z);
    EXPECT_EQ(samples[4].x, test.maxPlaneXZ.x);  // maxPlaneXZ was latest updated by samples[4]
    EXPECT_EQ(samples[4].y, test.maxPlaneXZ.y);
    EXPECT_EQ(samples[4].z, test.maxPlaneXZ.z);
    EXPECT_EQ(samples[2].x, test.maxPlaneXY.x);  // maxPlaneXY was latest updated by samples[2]
    EXPECT_EQ(samples[2].y, test.maxPlaneXY.y);
    EXPECT_EQ(samples[2].z, test.maxPlaneXY.z);
}
