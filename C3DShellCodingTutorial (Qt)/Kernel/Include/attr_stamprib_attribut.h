////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Атрибут ребра жесткости листового тела.
         \en Attribute of reinforsed rib of sheet solid. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTR_STAMPRIB_ATTRIBUTE_H
#define __ATTR_STAMPRIB_ATTRIBUTE_H


#include <attr_geometric_attribut.h>
#include <op_swept_parameter.h>


//------------------------------------------------------------------------------
/** \brief \ru Атрибут ребра жесткости листового тела.
           \en Attribute of reinforsed rib of sheet solid. \~
  \details \ru Атрибут ребра жесткости листового тела. Двумерный контур ребра 
               жесткости и локальная система координат, в плоскости XY которой
               расположен двумерный контур содержатся в MbGeomAttribute.
           \en Attribute of reinforsed rib of sheet solid. Two-dimensional contour 
               of a rib and a local coordinate system the two-dimensional contour 
               is located in XY plane of are stored in MbGeomAttribute \n \~
  \ingroup Model_Attributes
 */
class MATH_CLASS MbStampRibAttribute : public MbGeomAttribute
{
protected :
  size_t         index;     ///< \ru Индекс сегмента в контуре, от которого будет установлено направление уклона. \en Index of a segment in the contour at which the inclination direction will be set. 
  SheetRibValues pars;      ///< \ru Параметры операции. \en The operation parameters.
  MbSNameMaker   names;     ///< \ru Именователь операции. \en An object defining names generation in the operation.
  MbVector3D     bendNorm;  ///< \ru Нормаль поверхности сгиба (только для внутреннего использования). \en A normal to bend surface (for internal usage only).
  MbCartPoint3D  bendPoint; ///< \ru Точка на оси сгиба сгиба (только для внутреннего использования). \en A point on bend axis (for internal usage only).
private:
  // \ru Конструктор копирования. \en Copy constructor. 
  MbStampRibAttribute( const MbStampRibAttribute & init, MbRegDuplicate * iReg );
public :
  /// \ru Конструктор. \en Constructor. 
  MbStampRibAttribute( const MbSpaceItem & item, MbeCreatorType t, size_t index, const SheetRibValues & pars, const MbSNameMaker & n, bool keepItem); 
  /// \ru Конструктор. \en Constructor. 
  MbStampRibAttribute( const MbSpaceItem & item, MbeCreatorType t, size_t index, const SheetRibValues & pars, const MbSNameMaker & n, bool keepItem, const c3d::string_t & itemPrompt ); 
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbStampRibAttribute();

public:
  // \ru Выдать подтип атрибута. \en Get subtype of an attribute. 
  virtual MbeAttributeType AttributeType() const;
  // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual MbAttribute & Duplicate( MbRegDuplicate * = NULL ) const; 
  // \ru Определить, являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    IsSame( const MbAttribute &, double accuracy ) const;
  // \ru Инициализировать данные по присланным. \en Initialize data. 
  virtual bool    Init( const MbAttribute & ); 

  // \ru Выполнить действия при трансформировании владельца. \en Perform actions when transforming the owner. 
  virtual void    OnTransformOwner( const MbAttributeContainer & owner, const MbMatrix3D & matr, MbRegTransform * iReg ); 
  // \ru Выполнить действия при перемещении владельца. \en Perform actions when moving the owner. 
  virtual void    OnMoveOwner( const MbAttributeContainer & owner, const MbVector3D & to, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при вращении владельца. \en Perform actions when rotating the owner. 
  virtual void    OnRotateOwner( const MbAttributeContainer & owner, const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL ); 
  // \ru Выполнить действия при копировании владельца. \en Perform actions when copying the owner. 
  virtual void    OnCopyOwner( const MbAttributeContainer & owner, MbAttributeContainer & other, MbRegDuplicate * iReg ); 
  // \ru Выполнить действия при объединении владельца. \en Perform actions when merging the owner. 
  virtual void    OnMergeOwner( const MbAttributeContainer & owner, MbAttributeContainer & other ); 

  virtual void    GetCharValue( TCHAR * v ) const; // \ru Выдать строковое значение свойства. \en Get a string value of the property. 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual size_t  SetProperties( const MbProperties & ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual MbePrompt GetPropertyName(); // \ru Выдать заголовок свойства объекта. \en Get a name of object property.
          /// \ru Дать индекс сегмента в контуре. \en Get index of a segment in the contour.
          const  size_t & GetIndex() const { return index; } 
          /// \ru Дать параметры операции. \en Get operation parameters.
          const  SheetRibValues & GetRibValues() const { return pars; } 
          /// \ru Дать именователь операции. \en Get an object defining a name of the operation.
          const  MbSNameMaker & GetNameMaker() const { return names; } 
          /// \ru Дать нормаль к поверхности сгиба. \en Get normal to bend surface.
          const  MbVector3D & GetBendNormal() const { return bendNorm; } 
          /// \ru Установить нормаль к поверхности сгиба. \en Set normal to bend surface.
          void SetBendNormal( const  MbVector3D & n ) {  bendNorm = n; } 
          /// \ru Дать точку на оси сгиба. \en Get point on bend axis.
          const  MbCartPoint3D & GetBendPoint() const { return bendPoint; } 
          /// \ru Установить точку на оси сгиба. \en Set point on bend axis.
          void SetBendPoint( const  MbCartPoint3D & p ) {  bendPoint = p; } 
DECLARE_PERSISTENT_CLASS( MbStampRibAttribute ) 
OBVIOUS_PRIVATE_COPY( MbStampRibAttribute )
}; 

IMPL_PERSISTENT_OPS( MbStampRibAttribute )

#endif // __ATTR_STAMPRIB_ATTRIBUTE_H
