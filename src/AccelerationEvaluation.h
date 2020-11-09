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

#endif /* ACCELERATIONEVALUATION_H_ */
