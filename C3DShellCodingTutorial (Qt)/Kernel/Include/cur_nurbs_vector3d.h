////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Nurbs-вектор.
         \en Nurbs-vecor. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_NURBS_VECTOR3D_H
#define __CUR_NURBS_VECTOR3D_H

#include <mb_cart_point3d.h>
#include <reference_item.h>

//------------------------------------------------------------------------------
/** \brief \ru Координаты для Nurbs-вектора.
           \en Coordinates for Nurbs-vector. \~
  \details \ru Тройка координат для трехмерного Nurbs-вектора. \n
           \en Three coordinates for three-dimensional Nurbs-vector. \n \~
\ingroup Data_Structures
*/
// ---
struct DoubleTriple
{
  double x;
  double y;
  double z;

  // \ru Инициализация. \en Initialization.
  void Init( double xx, double yy, double zz ) { x = xx; y = yy; z = zz; }

  // \ru Инициализация. \en Initialization.
  void Init( const DoubleTriple & ip ) { Init( ip.x, ip.y, ip.z ); }

  // \ru Инициализация. \en Initialization.
  void Init( const DoubleTriple & ip, double iw ) { Init( ip.x * iw, ip.y * iw, ip.z * iw ); }

  // \ru Инициализация. \en Initialization.
  void Init( const MbCartPoint3D & ip, double iw ) { Init( ip.x * iw, ip.y * iw, ip.z * iw ); }

  // \ru Присвоение значений. \en Values assignment. 
  void Dec( const DoubleTriple & p1, const DoubleTriple & p2, double kk ) {
    Init( ( p2.x - p1.x ) * kk, ( p2.y - p1.y ) * kk, ( p2.z - p1.z ) * kk );
  }

};

//------------------------------------------------------------------------------
/** \brief \ru Nurbs-вектор.
           \en Nurbs-vector. \~
  \details \ru Трёхмерный Nurbs-вектор. \n
           \en Three-Dimensional Nurbs-vector. \n \~
  \ingroup Data_Structures
*/
// ---
class MATH_CLASS MbNURBSVector {
  std::vector<DoubleTriple> _vec;
  std::vector<double> _w;
  bool useWeights;

public:
  MbNURBSVector() : useWeights( false ) {}
  ~MbNURBSVector(); // \ru освободить память \en free memory 

public:
  bool CatchMemory( ptrdiff_t count, bool bWeight ); // \ru выделить память \en allocate memory 
  void FreeMemory(); // \ru освободить память \en free memory 
  void Init( ptrdiff_t i, const DoubleTriple & ip, double iw );
  void Init( ptrdiff_t i, double ipx, double ipy, double ipz, double iw );
  void SetZero( ptrdiff_t i );
  void Set( ptrdiff_t i, const MbNURBSVector & p,  ptrdiff_t ip );
  void Dec( ptrdiff_t i, const MbNURBSVector & p1, ptrdiff_t ip1, const MbNURBSVector & p2, ptrdiff_t ip2, double kk );
  void Set( ptrdiff_t i, const MbNURBSVector & p,  ptrdiff_t ip, double kk );
  void Set( ptrdiff_t i, const DoubleTriple * t, double * ww, ptrdiff_t ip );
  void Set( ptrdiff_t i, const DoubleTriple & t );

  double& x( ptrdiff_t i ) { return _vec[i].x; }
  double& y( ptrdiff_t i ) { return _vec[i].y; }
  double& z( ptrdiff_t i ) { return _vec[i].z; }
  double& w( ptrdiff_t i ) { return _w[i]; }
  const double& x( ptrdiff_t i ) const { return _vec[i].x; }
  const double& y( ptrdiff_t i ) const { return _vec[i].y; }
  const double& z( ptrdiff_t i ) const { return _vec[i].z; }
  const double& w( ptrdiff_t i ) const { return _w[i]; }
  bool UseWeights() { return useWeights; }

  DoubleTriple& operator [] ( ptrdiff_t i ) { return _vec[i]; }
  const DoubleTriple& operator [] ( ptrdiff_t i ) const { return _vec[i]; }

private:
  MbNURBSVector( const MbNURBSVector & ); // \ru не реализовано \en not implemented 
  void operator = ( const MbNURBSVector & ); // \ru не реализовано \en not implemented 
};


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector::Init( ptrdiff_t i, const DoubleTriple & ip, double iw )
{
  if ( !useWeights ) {
    _vec[i].Init( ip.x, ip.y, ip.z );
  }
  else {
    _vec[i].Init( ip.x * iw, ip.y * iw, ip.z * iw );
    w(i) = iw;
  }
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector::Init( ptrdiff_t i, double ipx, double ipy, double ipz, double iw )
{
  if ( !useWeights ) {
    x(i) = ipx;
    y(i) = ipy;
    z(i) = ipz;
  }
  else {
    x(i) = ( ipx * iw );
    y(i) = ( ipy * iw );
    z(i) = ( ipz * iw );
    w(i) = iw;
  }
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector::SetZero( ptrdiff_t i ) {
  x(i) = 0.0;
  y(i) = 0.0;
  z(i) = 0.0;
  if ( useWeights )
    w(i) = 0.0;
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector::Set( ptrdiff_t i, const MbNURBSVector & p, ptrdiff_t ip ) {
  _vec[i].Init( p[ip].x, p[ip].y, p[ip].z );
  if ( useWeights )
    w(i) = p.w(ip);
}


//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector::Dec( ptrdiff_t i, 
                                const MbNURBSVector & p1, ptrdiff_t ip1, 
                                const MbNURBSVector & p2, ptrdiff_t ip2, 
                                double kk )
{
  _vec[i].Init( ( p2[ip2].x - p1[ip1].x ) * kk, ( p2[ip2].y - p1[ip1].y ) * kk, ( p2[ip2].z - p1[ip1].z ) * kk );
  if ( useWeights )
    w(i) = ( (p2.w(ip2) - p1.w(ip1)) * kk );
}

//------------------------------------------------------------------------------
//
// ---
inline void MbNURBSVector::Set( ptrdiff_t i, const MbNURBSVector & p, ptrdiff_t ip, double kk ) {
  _vec[i].Init( p[ip].x * kk, p[ip].y * kk, p[ip].z * kk );
  if ( useWeights )
    w(i) = ( p.w(ip) * kk );
}

inline void MbNURBSVector::Set( ptrdiff_t i, const DoubleTriple * t, double * ww, ptrdiff_t ip )
{
  _vec[i].Init( t[ip].x , t[ip].y , t[ip].z );
  if ( useWeights && ww != NULL )
    w(i) = ww[ip];
}

inline void MbNURBSVector::Set( ptrdiff_t i, const DoubleTriple & t )
{
  _vec[i].Init( t.x , t.y , t.z );
}

#endif // __CUR_NURBS_VECTOR3D_H
