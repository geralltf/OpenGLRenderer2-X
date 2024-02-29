#ifndef VECTORLIB_H
#define VECTORLIB_H

#include <cmath>

//#include "MatrixLib.h"
//#include "Vector2i.h"
//#include "Vector2f.h"
//#include "Vector3f.h"
//#include "Vector4f.h"

//static bool is_equal(float x, float y);
inline static bool is_equal(float x, float y)
{
    float epsilon = 0.01f;
    if (fabs(x - y) < epsilon)
    {
        return true;
    }
    return false;
}

//class dud {
//public:
//    static int DUD_TEST;
//};


#endif