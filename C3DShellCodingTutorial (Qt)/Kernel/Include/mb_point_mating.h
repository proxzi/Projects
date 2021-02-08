////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Модуль геометрических построений. Сопряжение в точке
         \en Geometric constructions module. Conjugation at point. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __MB_POINT_MATING_H
#define __MB_POINT_MATING_H


#include <templ_s_array.h>
#include <io_tape.h>
#include <mb_enum.h>
#include <mb_property.h>
#include <mb_property_title.h>


//------------------------------------------------------------------------------
/// \ru Параметры сопряжения в точке \en Parameters of conjugation at point 
//---
template <class Vector>
class MbPntMatingData {
private: // \ru данные \en data 
//OV_x64 The structure's size can be decreased via changing the fields' order. The size can be reduced from 56 to 40 bytes.
//OV_x64   MbeMatingType       type;         ///< \ru тип сопряжения \en conjugation type 
//OV_x64   Vector            * tangent;      ///< \ru направляющий касательный вектор \en guide tangent vector 
//OV_x64   Vector            * tangentDer1;  ///< \ru первая производная касательного вектора \en first derivative of tangent vector 
//OV_x64   Vector            * tangentDer2;  ///< \ru вторая производная касательного вектора \en second derivative of tangent vector  
//OV_x64   bool                movePnts;     ///< \ru двигать исходные точки или добавлять \en move or add source points  
//OV_x64   SArray<ptrdiff_t> * changedPnts;  ///< \ru индексы измененных точек \en indices of changed points 
//OV_x64   bool                attach;       ///< \ru данные служат для стыковки сплайна с кривой \en data for spline and curve connection  

  Vector            * tangent;      ///< \ru Направляющий касательный вектор. \en Guide tangent vector. 
  Vector            * tangentDer1;  ///< \ru Первая производная касательного вектора. \en First derivative of tangent vector. 
  Vector            * tangentDer2;  ///< \ru Вторая производная касательного вектора. \en Second derivative of tangent vector. 
  SArray<ptrdiff_t> * changedPnts;  ///< \ru Индексы измененных точек. \en Indices of changed points. 
  MbeMatingType       type;         ///< \ru Тип сопряжения. \en Conjugation type. 
  bool                movePnts;     ///< \ru Двигать исходные точки или добавлять. \en Move or add source points. 
  bool                attach;       ///< \ru Данные служат для стыковки сплайна с кривой. \en Data for a spline and a curve connection. 

public:
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbPntMatingData();
  /// \ru Конструктор по всем параметрам сопряжения в точке. \en Constructor by all parameters of conjugation at point. 
  MbPntMatingData( const MbeMatingType type, const Vector * tang, 
                   const Vector * tangDer1, const Vector * tangDer2, 
                   SArray<ptrdiff_t> *& changedPnts,
                   bool movePnts, bool isAttach );
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbPntMatingData( const MbPntMatingData & );
  /// \ru Деструктор. \en Destructor. 
  ~MbPntMatingData();

public:
  /// \ru Инициализировать по всем параметрам сопряжения в точке. \en Initialize by all parameters of conjugation at point. 
  void Init( const MbeMatingType type, const Vector * tang, 
             const Vector * tangDer1, const Vector * tangDer2, 
             SArray<ptrdiff_t> *& changedPnts,
             bool movePnts, bool isAttach );

  /// \ru Инициализировать по другому объекту параметров сопряжения в точке. \en Initialize by another parameters object of conjugation at point. 
  bool Init( const MbPntMatingData & );

public:
  // \ru доступ к данным \en access to data 
  /// \ru Дать тип сопряжения. \en Get conjugation type. 
  MbeMatingType   GetType()        const { return type; }
  /// \ru Дать направляющий касательный вектор. \en Get guide tangent vector. 
  const Vector *  GetTangent()     const { return tangent; }
  /// \ru Дать первую производную касательного вектора. \en Get the first derivative of tangent vector. 
  const Vector *  GetTangentDer1() const { return tangentDer1; }
  /// \ru Дать вторую производную касательного вектора. \en Get the second derivative of tangent vector. 
  const Vector *  GetTangentDer2() const { return tangentDer2; }
  /// \ru Выдать признак совпадения направлений касательных в точке сопряжения. \en Get attribute of tangent directions coincidence at conjugation point. 
  bool            IsAttach() const { return attach; } 
  /// \ru Выдать признак возможности передвижения исходных точек. \en Get attribute of source points movability. 
  bool            CanMovePoints() const { return movePnts; }
  /// \ru Вернуть массив изменных точек. \en Get array of changed points. 
  const SArray<ptrdiff_t> *  GetChangedPoints() const { return changedPnts; }
  /// \ru Вернуть массив изменных точек. \en Get array of changed points. 
        SArray<ptrdiff_t> *& SetChangedPoints()       { return changedPnts; }

  /// \ru Являются ли объекты равными? \en Determine whether an object is equal?
  bool      IsSame( const MbPntMatingData<Vector> &, double accuracy ) const;
  /// \ru Сделать первичную проверку корректности параметров. \en Initial check of parameters correctness. 
  bool      IsValid() const;
  /// \ru Уcтановить параметры сопряжения. \en Set conjugation parameters. 
  void      SetVector( ptrdiff_t i, const Vector & vect );
  /// \ru Нормализовать касательную в случае стыковки. \en Normalize tangent in case of connection. 
  void      NormalizeAttachTangent();
  /// \ru Дать фактическую степень гладкости визуального перехода. \en Get the actual smoothness degree of visual transition. 
  ptrdiff_t GetSmoothDegree() const;

  /// \ru Выдать свойства объекта. \en Get properties of the object. 
  void      GetProperties( MbProperties & );
  /// \ru Записать свойства объекта. \en Set properties of the object. 
  void      SetProperties( const MbProperties & );

private: // \ru не реализовано \en not implemented 
  void      operator = ( const MbPntMatingData<Vector> & );
};


//------------------------------------------------------------------------------
// \ru конструктор \en constructor 
//---
template <class Vector>
MbPntMatingData<Vector>::MbPntMatingData() 
  : tangent     ( NULL         )
  , tangentDer1 ( NULL         )
  , tangentDer2 ( NULL         )
  , changedPnts ( NULL         )
  , type        ( trt_Position )
  , movePnts    ( false        )
  , attach      ( false        )
{
}


//------------------------------------------------------------------------------
// \ru конструктор \en constructor 
//---
template <class Vector>
MbPntMatingData<Vector>::MbPntMatingData( const MbeMatingType        nType, 
                                          const Vector *             nTang, 
                                          const Vector *             nTangDer1, 
                                          const Vector *             nTangDer2, 
                                                SArray<ptrdiff_t> *& nChangedPnts,
                                                bool                 nMovePnts,
                                                bool                 nAttach )
  : type        ( nType                                                 )
  , tangent     ( (nTang     != NULL) ? new Vector( *nTang )     : NULL )
  , tangentDer1 ( (nTangDer1 != NULL) ? new Vector( *nTangDer1 ) : NULL )
  , tangentDer2 ( (nTangDer2 != NULL) ? new Vector( *nTangDer2 ) : NULL )
  , movePnts    ( nMovePnts                                             )
  , changedPnts ( nChangedPnts                                          )
  , attach      ( nAttach                                               )
{
  if ( type <= trt_Position ) { // BUG_52162
    ::DeleteMatItem( tangent );
    ::DeleteMatItem( tangentDer1 );
    ::DeleteMatItem( tangentDer2 );
  }
}


//------------------------------------------------------------------------------
// \ru конструктор копирования \en copy constructor 
//---
template <class Vector>
MbPntMatingData<Vector>::MbPntMatingData( const MbPntMatingData<Vector> & d )
  : type        ( d.type                                                        )
  , tangent     ( (d.tangent     != NULL) ? new Vector( *d.tangent )     : NULL )
  , tangentDer1 ( (d.tangentDer1 != NULL) ? new Vector( *d.tangentDer1 ) : NULL )
  , tangentDer2 ( (d.tangentDer2 != NULL) ? new Vector( *d.tangentDer2 ) : NULL )
  , movePnts    ( d.movePnts                                                    )
  , changedPnts ( d.changedPnts                                                 )
  , attach      ( d.attach                                                      )
{
}


//------------------------------------------------------------------------------
// \ru деструктор \en destructor 
//---
template <class Vector>
MbPntMatingData<Vector> ::~MbPntMatingData()
{
  ::DeleteMatItem( tangent );
  ::DeleteMatItem( tangentDer1 );
  ::DeleteMatItem( tangentDer2 );
}


//------------------------------------------------------------------------------
// \ru инициализация данных \en data initialization 
//---
template <class Vector>
void MbPntMatingData<Vector>::Init( const MbeMatingType        nType,
                                    const Vector *             nTang, 
                                    const Vector *             nTangDer1,
                                    const Vector *             nTangDer2, 
                                          SArray<ptrdiff_t> *& nChangedPnts,
                                          bool                 nMovePnts, 
                                          bool                 nAttach )
{
  type = nType;

  if ( tangent != NULL && nTang != NULL ) // \ru касательный вектор \en tangent vector 
    tangent->Init( *nTang );
  else if ( nTang != NULL )
    tangent = new Vector( *nTang );
  else if ( tangent != NULL )
    ::DeleteMatItem( tangent );

  if ( tangentDer1 != NULL && nTangDer1 != NULL ) // \ru первая производная касательного вектора \en first derivative of tangent vector 
    tangentDer1->Init( *nTangDer1 );
  else if ( nTangDer1 != NULL )
    tangentDer1 = new Vector( *nTangDer1 );
  else if ( tangentDer1 != NULL )
    ::DeleteMatItem( tangentDer1 );

  if ( tangentDer2 != NULL && nTangDer2 != NULL ) // \ru вторая производная касательного вектора \en second derivative of tangent vector  
    tangentDer2->Init( *nTangDer2 );
  else if ( nTangDer2 != NULL )
    tangentDer2 = new Vector( *nTangDer2 );
  else if ( tangentDer2 != NULL )
    ::DeleteMatItem( tangentDer2 );

  if ( type <= trt_Position ) { // BUG_52162
    ::DeleteMatItem( tangent );
    ::DeleteMatItem( tangentDer1 );
    ::DeleteMatItem( tangentDer2 );
  }

  if ( changedPnts != NULL )
    changedPnts->Flush();

  movePnts    = nMovePnts;
  changedPnts = nChangedPnts;
  attach      = nAttach;
}


//------------------------------------------------------------------------------
// \ru инициализация данных \en data initialization 
//---
template <class Vector>
bool MbPntMatingData<Vector>::Init( const MbPntMatingData & d )
{
  C3D_ASSERT( changedPnts == NULL );

  if ( this != &d ) {
    SArray<ptrdiff_t> * dummyInds = NULL;
    Init( d.type, d.tangent, d.tangentDer1, d.tangentDer2, dummyInds, d.movePnts, d.attach );
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru Являются ли объекты равными? \en Determine whether an object is equal?
//---
template <class Vector>
bool MbPntMatingData<Vector>::IsSame( const MbPntMatingData<Vector> & other, double accuracy ) const 
{
  bool isSame = false;

  if ( c3d::EqualVectors( *tangent, *other.tangent, accuracy ) &&
       c3d::EqualVectors( *tangentDer1, *other.tangentDer1, accuracy ) &&
       c3d::EqualVectors( *tangentDer2, *other.tangentDer2, accuracy ) &&
       *changedPnts == *other.changedPnts &&
       type == other.type &&
       movePnts == other.movePnts &&
       attach == other.attach )
    isSame = true;

  return isSame;
}


//------------------------------------------------------------------------------
// \ru первичная проверка корректности параметров \en initial check of parameters correctness 
//---
template <class Vector>
bool MbPntMatingData<Vector>::IsValid() const 
{
  bool isValid = true;

  if ( type >= trt_Position ) {
    double lenEps = LENGTH_EPSILON;
    bool isTang = (tangent != NULL);
    bool isTangDer1 = (tangentDer1 != NULL);
    bool isTangDer2 = (tangentDer2 != NULL);
    bool isTangLen = (isTang && tangent->Length() > lenEps);

    switch( type ) {
      case trt_Tangent:
        isValid = isTangLen; 
        break;
      case trt_Normal:
        // \ru под нормалью понимается как касательное сопряжение с тем, что названо нормалью, \en normal is considered to be either a tangent conjugation with what is called normal 
        // \ru так и управление только главной нормалью \en or only principal normal management   
        isValid = !attach && (isTangLen || (isTangDer1 && tangentDer1->Length() > lenEps)); 
        break;
      case trt_SmoothG2 :
        isValid = isTangLen && (isTangDer1 && tangent->Orthogonal( *tangentDer1 )); 
        break;
      case trt_SmoothG3:
        isValid = isTangLen && (isTangDer1 && tangent->Orthogonal( *tangentDer1 )) && isTangDer2;
        break;
      default: break;
    }
  }

  return isValid;
}


//------------------------------------------------------------------------------
// \ru фактическая степень гладкости визуального перехода \en actual smoothness degree of visual transition 
//---
template <class Vector>
ptrdiff_t MbPntMatingData<Vector>::GetSmoothDegree() const
{  
  ptrdiff_t res = 0;
  switch ( type ) {
    case trt_Tangent :
      res = 1;
      break;
    case trt_Normal :
      if ( tangentDer1 != NULL )  res = 2;
      else if ( tangent != NULL ) res = 1;
      break;
    case trt_SmoothG2:
      res = 2;
      break;
    case trt_SmoothG3:
      res = 3;
      break;  
    default: break;
  }
  return res;
}


//------------------------------------------------------------------------------
// \ru уcтановка параметров сопряжения \en set conjugation parameters 
//---
template <class Vector>
void MbPntMatingData<Vector>::SetVector( ptrdiff_t i, const Vector & vect )
{
  switch ( i ) {
    case 0 : {
      if ( tangent != NULL ) tangent->Init( vect );
      else                   tangent = new Vector( vect );
      break;
    }
    case 1 : {
      if ( tangentDer1 != NULL ) tangentDer1->Init( vect );
      else                       tangentDer1 = new Vector( vect );
      break;
    }
    case 2 : {
      if ( tangentDer2 != NULL ) tangentDer2->Init( vect );
      else                       tangentDer2 = new Vector( vect );
      break;
    }
  }
}


//------------------------------------------------------------------------------
// \ru нормализовать касательную в случае стыковки \en normalize tangent in case of connection 
//---
template <class Vector>
void MbPntMatingData<Vector>::NormalizeAttachTangent() 
{
  if ( attach && tangent != NULL  ) {
    double tangLen = tangent->Length();
    if ( tangLen > LENGTH_EPSILON )
      (*tangent) /= tangLen;
  }
}


//------------------------------------------------------------------------------
// \ru выдать свойства объекта \en get properties of object 
// ---
template <class Vector>
void MbPntMatingData<Vector>::GetProperties( MbProperties & properties )
{
/*
  properties.SetName( IDS_PROP_0900 );

  TCHAR * typeName = new TCHAR[256];

  switch ( type ) {
    case trt_None     : _sntprintf( typeName, IDS_PROP_0902 ); break;
    case trt_Position : _sntprintf( typeName, IDS_PROP_0903 ); break;
    case trt_Tangent  : _sntprintf( typeName, IDS_PROP_0904 ); break;
    case trt_Normal   : _sntprintf( typeName, IDS_PROP_0905 ); break;
    case trt_SmoothG2 : _sntprintf( typeName, IDS_PROP_0906 ); break;
    case trt_SmoothG3 : _sntprintf( typeName, IDS_PROP_0907 ); break;
    default           : _sntprintf( typeName, IDS_ITEM_0902 ); break;
  }

  properties.Add( new StringProperty( IDS_PROP_0901, typeName, false ) );  
*/
  if ( tangent != NULL )
    properties.Add( new MathItemProperty<Vector>( IDS_PROP_0908, tangent, true ) );
  if ( tangentDer1 != NULL )
    properties.Add( new MathItemProperty<Vector>( IDS_PROP_0909, tangentDer1, true ) );
  if ( tangentDer2 != NULL )
    properties.Add( new MathItemProperty<Vector>( IDS_PROP_0910, tangentDer2, true ) );

  properties.Add( new BoolProperty( IDS_PROP_0911, movePnts, false ) );
  properties.Add( new BoolProperty( IDS_PROP_0912, attach,   false ) );
}


//------------------------------------------------------------------------------
// \ru выдать свойства объекта \en get properties of object 
// ---
template <class Vector>
void MbPntMatingData<Vector>::SetProperties( const MbProperties & /*properties*/ )
{
}


//------------------------------------------------------------------------------
// \ru определено ли сопряжение \en whether conjugation is defined 
//---
template <class Vector>
bool IsMatingDefined( const MbPntMatingData<Vector> * data )
{
  bool isDefined = false;

  if ( data != NULL && data->IsValid() ) {
    if ( data->GetType() > trt_Position ) // \ru по позиции и так выполнится, поэтому считаем не заданным \en would be held at position, so assumed as undefined 
      isDefined = true;
  }

  return isDefined;
}


//------------------------------------------------------------------------------
// \ru определены ли сопряжение \en whether conjugation is defined 
//---
template <class Vector>
bool IsAnyMatingDefined( const RPArray< MbPntMatingData<Vector> > & data )
{
  bool isDefined = false;

  if ( data.Count() > 0 ) {
    for ( size_t k = 0, cnt = data.Count(); k < cnt; k++ ) {
      if ( ::IsMatingDefined( data[k] ) ) {
        isDefined = true;
        break;
      }
    }
  }

  return isDefined;
}


//------------------------------------------------------------------------------
// \ru копировать сопряжения \en copy conjugations 
//---
template <class Vector>
bool CopyMating( const RPArray< MbPntMatingData<Vector> > & src, RPArray< MbPntMatingData<Vector> > & dst )
{
  bool isDone = false;

  if ( src.Count() > 0 && dst.Count() < 1 ) {
    isDone = true;
    for ( size_t k = 0, cnt = src.Count(); k < cnt && isDone; k++ ) {
      MbPntMatingData<Vector> * copyItem = NULL;
      if ( src[k] != NULL ) {
        copyItem = new MbPntMatingData<Vector>();
        isDone = copyItem->Init( *src[k] );
      }
      dst.Add( copyItem );
    }
    if ( !isDone )
      ::DeleteMatItems( dst );
  }

  return isDone;
}


//------------------------------------------------------------------------------
// \ru Являются ли объекты равными? \en Determine whether an object is equal?
//---
template <class Vector>
bool IsSame( const RPArray< MbPntMatingData<Vector> > & data, const RPArray< MbPntMatingData<Vector> > & other, double accuracy )
{
  bool isSame = false;

  if ( data.Count() == other.Count() ) {
    isSame = true;
    for ( size_t k = 0, cnt = data.Count(); k < cnt; k++ )
      if ( !data[k]->IsSame( *other[k], accuracy ) ) {
        isSame = false;
        break;
      }
  }

  return isSame;
}


//------------------------------------------------------------------------------
// \ru трансформировать сопряжения \en transform conjugations 
//---
template <class Vector, class Matrix>
void TransformMating( const RPArray< MbPntMatingData<Vector> > & data, const Matrix & matr )
{
  Vector vect;
  for ( size_t k = 0, kcnt = data.Count(); k < kcnt; k++ ) {
    MbPntMatingData<Vector> * dataItem = data[k];

    if ( dataItem != NULL ) {
      if ( dataItem->GetTangent() != NULL ) {
        vect = *dataItem->GetTangent();
        vect.Transform( matr );
        dataItem->SetVector( 0, vect );
      }
      if ( dataItem->GetTangentDer1() != NULL ) {
        vect = *dataItem->GetTangentDer1();
        vect.Transform( matr );
        dataItem->SetVector( 1, vect );
      }
      if ( dataItem->GetTangentDer2() != NULL ) {
        vect = *dataItem->GetTangentDer2();
        vect.Transform( matr );
        dataItem->SetVector( 2, vect );
      }
    }
  }
}


//------------------------------------------------------------------------------
// \ru вращать сопряжения \en rotate conjugations 
//---
template <class Vector, class Axis>
void RotateMating( const RPArray< MbPntMatingData<Vector> > & data, const Axis & axis, double angle )
{
  Vector vect;
  for ( size_t i = 0; i < data.Count(); i++ ) {
    MbPntMatingData<Vector> * dataItem = data[i];

    if ( dataItem->GetTangent() != NULL ){
      vect = *dataItem->GetTangent();
      vect.Rotate( axis, angle );
      dataItem->SetVector( 0, vect );
    }
    if ( dataItem->GetTangentDer1() != NULL ){
      vect = *dataItem->GetTangentDer1();
      vect.Rotate( axis, angle );
      dataItem->SetVector( 1, vect );
    }
    if ( dataItem->GetTangentDer2() != NULL ){
      vect = *dataItem->GetTangentDer2();
      vect.Rotate( axis, angle );
      dataItem->SetVector( 2, vect );
    }
  }
}


//------------------------------------------------------------------------------
// \ru запись массива данных сопряжений \en conjugation data array writing 
//---
template <class Vector>
void WriteMating( writer & out, const RPArray< MbPntMatingData<Vector> > & data )
{
  if ( out.good() ) {
    size_t cnt = data.Count();
    WriteCOUNT( out, cnt );
    for ( size_t k = 0; k < cnt && out.good(); k++ ) {
      const MbPntMatingData<Vector> * item = data[k];
      // \ru наличие сопряжения \en presence of conjugation 
      bool isItem = (item != NULL);
      out << isItem;

      if ( isItem && item->GetChangedPoints() != NULL ) {
        C3D_ASSERT_UNCONDITIONAL( false ); // \ru KYA массив индексов должен быть пуст, т.к. он общий для всех сопряжений, им владеет заказчик операции \en KYA array of indices should be empy because it is shared between all of conjugations and owned by user of operation 
        out.setState( io::cantWriteObject );
      }

      if ( isItem && out.good() ) {
        // \ru тип сопряжения \en conjugation type 
        uint32 type = (uint32)item->GetType();
        out << type;
        // \ru касательный вектор \en tangent vector 
        isItem = (item->GetTangent() != NULL);
        out << isItem;
        if ( isItem )
          out << (*item->GetTangent());
        // \ru первая производная касательного вектора \en first derivative of tangent vector 
        isItem = (item->GetTangentDer1() != NULL);
        out << isItem;
        if ( isItem ) 
          out << (*item->GetTangentDer1());
        // \ru вторая производная касательного вектора \en second derivative of tangent vector 
        isItem = (item->GetTangentDer2() != NULL);
        out << isItem;
        if ( isItem )
          out << (*item->GetTangentDer2());
        
        out << (bool)item->CanMovePoints();
        out << (bool)item->IsAttach();
      }
    }
  }
}


//------------------------------------------------------------------------------
// \ru чтение массива данных сопряжений \en conjugation data array reading 
//---
template <class Vector>
void ReadMating( reader & in, RPArray< MbPntMatingData<Vector> > & data )
{
  if ( in.good() ) {
    ::DeleteMatItems( data );
    size_t cnt = ReadCOUNT( in );

    if ( cnt > 0 ) {
      data.Reserve( cnt );
      SArray<ptrdiff_t> * dummyInds = NULL;

      for ( size_t k = 0; k < cnt && in.good(); k++ ) {
        // \ru наличие сопряжения \en presence of conjugation 
        bool isItem = false;
        in >> isItem;

        if ( isItem ) {
          // \ru тип сопряжения \en conjugation type 
          uint32 type = trt_None;
          in >> type;

          MbVector3D * v1 = NULL;
          MbVector3D * v2 = NULL;
          MbVector3D * v3 = NULL;

          // \ru касательный вектор \en tangent vector 
          in >> isItem;
          if ( isItem ) {
            v1 = new Vector;
            in >> *v1;
          }
          // \ru первая производная касательного вектора \en first derivative of tangent vector 
          in >> isItem;
          if ( isItem ) {
            v2 = new Vector;
            in >> *v2;
          }
          // \ru вторая производная касательного вектора \en second derivative of tangent vector 
          in >> isItem;
          if ( isItem ) {
            v3 = new Vector;
            in >> *v3;
          }

          bool movePnts = false;
          in >> movePnts;
          bool attach = false;
          in >> attach;

          MbPntMatingData<Vector> * item = new MbPntMatingData<Vector>();
          item->Init( (MbeMatingType)type, v1, v2, v3, dummyInds, movePnts, attach );
          data.Add( item );

          ::DeleteMatItem( v1 );
          ::DeleteMatItem( v2 );
          ::DeleteMatItem( v3 );
        }
        else {
          data.Add( NULL );
        }
      }
    }
  }
}


//------------------------------------------------------------------------------
// \ru Функция копирования. \en Copy function.
//---
template <class SrcVector, class DstVector>
void CopyPntMatingData( const MbPntMatingData<SrcVector> & srcData, MbPntMatingData<DstVector> & dstData )
{
  MbeMatingType type = srcData.GetType();
  bool movePnts = srcData.CanMovePoints();
  bool attach = srcData.IsAttach();
  SArray<ptrdiff_t> * changedPnts = const_cast<SArray<ptrdiff_t> *>( srcData.GetChangedPoints() );

  size_t dim = std_min( SrcVector::GetDimension(), DstVector::GetDimension() );

  DstVector * tangent = NULL;
  DstVector * tangentDer1 = NULL;
  DstVector * tangentDer2 = NULL;

  if ( srcData.GetTangent() != NULL ) {
    tangent = new DstVector;
    for ( size_t k = 0; k < dim; k++ )
      (*tangent)[k] = (*srcData.GetTangent())[k];
  }
  if ( srcData.GetTangentDer1() != NULL ) {
    tangentDer1 = new DstVector;
    for ( size_t k = 0; k < dim; k++ )
      (*tangentDer1)[k] = (*srcData.GetTangentDer1())[k];
  }
  if ( srcData.GetTangentDer2() != NULL ) {
    tangentDer2 = new DstVector;
    for ( size_t k = 0; k < dim; k++ )
      (*tangentDer2)[k] = (*srcData.GetTangentDer2())[k];
  }

  dstData.Init( type, tangent, tangentDer1, tangentDer2, changedPnts, movePnts, attach );

  ::DeleteMatItem( tangent );
  ::DeleteMatItem( tangentDer1 );
  ::DeleteMatItem( tangentDer2 );
}


#endif
