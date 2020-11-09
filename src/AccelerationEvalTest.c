#include <stdio.h>
#include <AccelerationEvaluation.h>

void printVertex(Vertex* vertex)
{
    printf("[x=%5.2f,y=%5.2f,z=%5.2f]\n", vertex->x, vertex->y, vertex->z);
}

Vertex samples[] = {
    {x: 0, y: 0, z: 1},  // samples for the first measurement cycle
    {x: 0.1, y: 0, z: 0.98},
    {x: 0, y: 0, z: 1},
    {x: 0.05, y: 0.2, z: 0.9},
    {x: 0, y: 0, z: 1},
    {x: -0.4, y: -0.21, z: 0.9},
    {x: 0, y: 0, z: 1.1},

    {x: 2, y: -1, z: 1.5},  // samples while latch is not enabled
    {x: 0.5, y: -0.4, z: 0.8},

    {x: 0.2, y: -0.1, z: 0.94},  // samples for the second measurement cycle
    {x: 0, y: 0, z: 1},
};

int main(int argc, char* argv[])
{
    AccelerationEvaluationState state;
    initAccelerationEvaluationState(&state);

    setLatchEnable(&state, false);

    printf("Initializing with first sample, rising edge on latch enable:\n");
    evaluateSample(&state, &samples[0]);
    setLatchEnable(&state, true);
    printf("  currentSample="); printVertex(&state.currentSample);
    printf("  maxPlaneYZ=   "); printVertex(&state.maxPlaneYZ);
    printf("  maxPlaneXZ=   "); printVertex(&state.maxPlaneXZ);
    printf("  maxPlaneXY=   "); printVertex(&state.maxPlaneXY);

    printf("Adding more samples while latch is enabled...\n");
    for (int i = 1; i < 7; ++i)
    {
        evaluateSample(&state, &samples[i]);
    }
    printf("Current state:\n");
    printf("  currentSample="); printVertex(&state.currentSample);
    printf("  maxPlaneYZ=   "); printVertex(&state.maxPlaneYZ);
    printf("  maxPlaneXZ=   "); printVertex(&state.maxPlaneXZ);
    printf("  maxPlaneXY=   "); printVertex(&state.maxPlaneXY);

    setLatchEnable(&state, false);

    printf("Adding more samples while latch is NOT enabled...\n");
    for (int i = 7; i < 9; ++i)
    {
        evaluateSample(&state, &samples[i]);
    }
    printf("Current state:\n");
    printf("  currentSample="); printVertex(&state.currentSample);
    printf("  maxPlaneYZ=   "); printVertex(&state.maxPlaneYZ);
    printf("  maxPlaneXZ=   "); printVertex(&state.maxPlaneXZ);
    printf("  maxPlaneXY=   "); printVertex(&state.maxPlaneXY);

    printf("Initializing second measurement cycle with first sample, rising edge on latch enable:\n");
    evaluateSample(&state, &samples[9]);
    setLatchEnable(&state, true);
    printf("  currentSample="); printVertex(&state.currentSample);
    printf("  maxPlaneYZ=   "); printVertex(&state.maxPlaneYZ);
    printf("  maxPlaneXZ=   "); printVertex(&state.maxPlaneXZ);
    printf("  maxPlaneXY=   "); printVertex(&state.maxPlaneXY);

    printf("Adding more samples while latch is enabled...\n");
    for (int i = 10; i < 11; ++i)
    {
        evaluateSample(&state, &samples[i]);
    }
    printf("Current state:\n");
    printf("  currentSample="); printVertex(&state.currentSample);
    printf("  maxPlaneYZ=   "); printVertex(&state.maxPlaneYZ);
    printf("  maxPlaneXZ=   "); printVertex(&state.maxPlaneXZ);
    printf("  maxPlaneXY=   "); printVertex(&state.maxPlaneXY);

    return 0;
}
