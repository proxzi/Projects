////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NURBS вектор 2D.
         \en 2D vector of NURBS. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_NURBS_VECTOR_H
#define __CUR_NURBS_VECTOR_H

#include <mb_cart_point.h>
#include <reference_item.h>


//------------------------------------------------------------------------------
/** \brief \ru Nurbs-вектор.
           \en Nurbs-vecor. \~
  \details \ru Двумерный Nurbs-вектор. \n
           \en Two-Dimensional Nurbs-vecor. \n \~
  \ingroup Data_Structures
*/
// ---
class MbNURBSVector2D {
public:
  double * x;
  double * y;
  double * w;

public:
  MbNURBSVector2D() : x( NULL ), y( NULL ), w( NULL ) {}
  ~MbNURBSVector2D(); // \ru освободить память \en free memory 

public:
  bool CatchMemory( ptrdiff_t count, bool bWeight ); // \ru выделить память \en allocate memory 
  void Init( ptrdiff_t i, const MbCartPoint &ip, double iw );
  void SetZero( ptrdiff_t i );
  void Set( ptrdiff_t i, const MbNURBSVector2D & p,  ptrdiff_t ip );
  void Dec( ptrdiff_t i, const MbNURBSVector2D & p1, ptrdiff_t ip1, const MbNURBSVector2D & p2, ptrdiff_t ip2, double kk );
  void Set( ptrdiff_t i, const MbNURBSVector2D & p,  ptrdiff_t ip, double kk );

private:
  void FreeMemory(); // \ru освободить память \en free memory 
  MbNURBSVector2D( const MbNURBSVector2D & ); // \ru не реализовано \en not implemented 
  void operator = ( const MbNURBSVector2D & ); // \ru не реализовано \en not implemented 
};


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector2D::Init( ptrdiff_t i, const MbCartPoint &ip, double iw ) {
  if ( w != NULL ) {
    x[i] = ( ip.x * iw );
    y[i] = ( ip.y * iw );
    w[i] = iw;
  }
  else {
    x[i] = ip.x;
    y[i] = ip.y;
  }
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector2D::SetZero( ptrdiff_t i ) {
  x[i] = 0.0;
  y[i] = 0.0;
  if ( w != NULL )
    w[i] = 0.0;
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector2D::Set( ptrdiff_t i, const MbNURBSVector2D &p, ptrdiff_t ip ) {
  x[i] = p.x[ip];
  y[i] = p.y[ip];
  if ( w != NULL )
    w[i] = p.w[ip];
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector2D::Dec( ptrdiff_t i, 
                                  const MbNURBSVector2D & p1, ptrdiff_t ip1,
                                  const MbNURBSVector2D & p2, ptrdiff_t ip2, 
                                  double kk )
{
  x[i] = ( (p2.x[ip2] - p1.x[ip1]) * kk );
  y[i] = ( (p2.y[ip2] - p1.y[ip1]) * kk );
  if ( w != NULL )
    w[i] = ( (p2.w[ip2] - p1.w[ip1]) * kk );
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector2D::Set( ptrdiff_t i, const MbNURBSVector2D & p, ptrdiff_t ip, double kk )
{
  x[i] = ( p.x[ip] * kk );
  y[i] = ( p.y[ip] * kk );
  if ( w != NULL )
    w[i] = ( p.w[ip] * kk );
}


#endif // __CUR_NURBS_VECTOR_H

