#include "Matrix4x4.h"

Matrix4x4 MakeIdentity4x4() {
	return Matrix4x4{
	    {
             {1.0f, 0.0f, 0.0f, 0.0f},
             {0.0f, 1.0f, 0.0f, 0.0f},
             {0.0f, 0.0f, 1.0f, 0.0f},
             {0.0f, 0.0f, 0.0f, 1.0f},
	     }
    };
}
