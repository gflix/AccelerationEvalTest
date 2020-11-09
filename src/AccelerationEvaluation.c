#include <math.h>
#include <AccelerationEvaluation.h>

void initVertex(Vertex* vertex)
{
    vertex->x = 0;
    vertex->y = 0;
    vertex->z = 0;
}

void initAccelerationEvaluationState(AccelerationEvaluationState* state)
{
    state->latchEnable = false;
    initVertex(&state->currentSample);
    initVertex(&state->maxPlaneYZ);
    initVertex(&state->maxPlaneXZ);
    initVertex(&state->maxPlaneXY);
}

void copyVertex(Vertex* destination, Vertex* source)
{
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
}

void setLatchEnable(AccelerationEvaluationState* state, bool nextLatchEnableState)
{
    if (!state->latchEnable && nextLatchEnableState)
    {
        copyVertex(&state->maxPlaneYZ, &state->currentSample);
        copyVertex(&state->maxPlaneXZ, &state->currentSample);
        copyVertex(&state->maxPlaneXY, &state->currentSample);
    }
    state->latchEnable = nextLatchEnableState;
}

void evaluateSample(AccelerationEvaluationState* state, Vertex* sample)
{
    if (state->latchEnable)
    {
        if (fabs(sample->x) > fabs(state->maxPlaneYZ.x))
        {
            copyVertex(&state->maxPlaneYZ, sample);
        }
        if (fabs(sample->y) > fabs(state->maxPlaneXZ.y))
        {
            copyVertex(&state->maxPlaneXZ, sample);
        }
        if (fabs(sample->z) > fabs(state->maxPlaneXY.z))
        {
            copyVertex(&state->maxPlaneXY, sample);
        }
    }
    copyVertex(&state->currentSample, sample);
}
