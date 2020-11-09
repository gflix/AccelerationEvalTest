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
