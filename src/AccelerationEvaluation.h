#ifndef ACCELERATIONEVALUATION_H_
#define ACCELERATIONEVALUATION_H_

#include <stdbool.h>

typedef struct
{
    double x;
    double y;
    double z;
} Vertex;


typedef struct
{
    bool latchEnable;
    Vertex currentSample;
    Vertex maxPlaneYZ;
    Vertex maxPlaneXZ;
    Vertex maxPlaneXY;
} AccelerationEvaluationState;

void initVertex(Vertex* vertex);
void initAccelerationEvaluationState(AccelerationEvaluationState* state);

void copyVertex(Vertex* destination, Vertex* source);

void setLatchEnable(AccelerationEvaluationState* state, bool nextLatchEnableState);

void evaluateSample(AccelerationEvaluationState* state, Vertex* sample);

#endif /* ACCELERATIONEVALUATION_H_ */
