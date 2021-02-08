#ifndef __MATHFUNCTIONS_H
#define __MATHFUNCTIONS_H

#include <cur_line3d.h>
#include <mb_vector.h>

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

bool Compare(double p1, double p2);
bool IsEqual(double p1, double p2, double accuracy);
bool IsEqualAngle(double p1, double p2);

bool Compare(const MbVector3D& v1, const MbVector3D& v2);
bool Compare(const MbVector3D& v1, const MbVector3D& v2, double accuracy);
bool Compare(const MbVector& v1, const MbVector& v2);
bool Compare(const MbVector& v1, const MbVector& v2, double accuracy);

VSN_FUNC(MbVector3D) TransformingGivenVector(const MbMatrix3D& mtx, const MbVector3D &Vect);

MbMatrix3D RotationMatrix(const MbMatrix3D& mtx);
MbMatrix3D RotationMatrix(const MbMatrix3D& mtx, const MbVector3D &v1, const MbVector3D &v2);

VSN_FUNC(void) SetVectorLength(MbVector3D& vec, double lenght);
VSN_FUNC(MbVector3D) SetVectorLength(const MbVector3D& vec, double lenght);

VSN_END_NAMESPACE

#endif /* __MATHFUNCTIONS_H */
