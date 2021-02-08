////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель разрезанного тела.
         \en Cut solid constructor.
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_CUTTING_SOLID_H
#define __CR_CUTTING_SOLID_H

#include <creator.h>
#include <mb_placement3d.h>
#include <op_boolean_flags.h>
#include <op_shell_parameter.h>


class  MATH_CLASS MbSurface;
class  MATH_CLASS MbContour;


//------------------------------------------------------------------------------
/** \brief \ru Строитель разрезанного тела.
           \en Cut solid constructor. \~
  \details \ru Строитель тела, разрезанного поверхностью или набором граней, полученного выдавливанием плоского контура.\n
           \en Constructor of a solid cut by a surface or a set of faces obtained by extrusion of a planar contour.\n \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbCuttingSolid : public MbCreator {
private:
  typedef MbShellCuttingParams::ProlongState CuttingProlongState;
protected :
  // Surface
  c3d::SurfaceSPtr        surface;      ///< \ru Режущая поверхность. \en Cutting surface. 
  // Sketch contour
  c3d::PlaneContourSPtr   contour;      ///< \ru Режущий контур (вместо поверхности). \en Cutting contour (instead of surface). 
  MbPlacement3D           place;        ///< \ru Местная система координат контура. \en Local coordinate system of the contour. 
  MbVector3D              direction;    ///< \ru Направление и длина выдавливания контура. \en Direction and distance of the contour extrusion. 
  // Solid
  c3d::CreatorsSPtrVector creators;     ///< \ru Строители оболочки. \en Shell creators. 

  ThreeStates             part;         ///< \ru Оставляемая часть (если part больше 0, то оставляем часть тела со стороны нормали поверхности). \en A part to be kept (if part is bigger than 0, then keep a part of  solid from the side of surface normal). 
  CuttingProlongState     prolongState; ///< \ru Тип продления режущей поверхности. \en Prolongation type of cutter surface.

  bool                    closed;       ///< \ru Замкнутоcть оболочки разрезаемого объекта. \en Closedness of the shell of the object being cut.
  bool                    mergeFaces;   ///< \ru Сливать подобные грани (true). \en Whether to merge similar faces (true). 
  bool                    mergeEdges;   ///< \ru Сливать подобные ребра (true). \en Whether to merge similar edges (true). 
  double                  buildSag;     ///< \ru Угловое отклонение при движении по кривым и поверхностям. \en Angular deviation while moving along curves and surfaces. 

public :
  MbCuttingSolid( const MbShellCuttingParams & cuttingParams, bool sameCutterObject );
  DEPRECATE_DECLARE
  MbCuttingSolid( const MbSurface & surface, bool sameSurface, int part, 
                  bool closed, const MbMergingFlags & flags, const MbSNameMaker & n );
  DEPRECATE_DECLARE
  MbCuttingSolid( const MbPlacement3D & place, const MbContour & contour, const MbVector3D & direction, int part, 
                  bool closed, const MbMergingFlags & flags, const MbSNameMaker & n );
private :
  MbCuttingSolid( const MbCuttingSolid &, MbRegDuplicate * ireg ); 
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbCuttingSolid( const MbCuttingSolid & ); 
public :
  virtual ~MbCuttingSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector3D &, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 

  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar ( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual( const MbCreator & );       // \ru Сделать равным \en Make equal 

  // \ru Общие функции твердого тела \en Common functions of solid 

  virtual bool        CreateShell( MbFaceShell *&, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * = NULL ); // \ru Построение \en Construction 

          // \ru Оставляемая часть (если part больше 0, то оставляем часть тела со стороны нормали поверхности). \en A part to be kept (if part is bigger than 0, then keep a part of  solid from the side of surface normal). 
          ThreeStates GetPart() const { return part; } 
          void        SetPart( ThreeStates p ) { part = p; } 
          void        SetOppositePart() { if ( part == ts_negative ) 
                                            part = ts_positive; 
                                          else if ( part == ts_positive )
                                            part = ts_negative; } 

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void    operator = ( const MbCuttingSolid & ); 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCuttingSolid )
}; // MbCuttingSolid

IMPL_PERSISTENT_OPS( MbCuttingSolid )


//------------------------------------------------------------------------------
/** \brief \ru Отрезать от оболочки некоторую её часть.
           \en Cut a part of the shell. \~
  \details \ru Для указанной оболочки построить оболочку без части граней, отрезанных от неё : 
    (1) указанной поверхностью, (2) набором граней, полученной выдавливанием плоского контура, (3) оболочкой. \n
    Одновременно с построением оболочки функция создаёт её строитель. \n
           \en For a given shell create a shell without a part of faces cut from it by :
     (1) the given surface, (2) a set of faces obtained by extrusion of a planar contour, (3) the given shell. \n
    The function simultaneously constructs the shell and creates its constructor. \n \~
  \param[in]  solid          - \ru Исходная оболочка.
                               \en The source shell. \~
  \param[in]  sameShell      - \ru Способ копирования граней исходной оболочки.
                               \en Method of copying the source shell faces. \~
  \param[in]  cuttingParams  - \ru Параметры операции.
                               \en Operation parameters. \~
  \param[out] res            - \ru Код результата операции.
                               \en Operation result code. \~
  \param[out] shell1         - \ru Построенный первый набор граней.
                               \en Constructed first set of faces. \~  
  \param[out] shell2         - \ru Построенный второй набор граней.
                               \en Constructed second set of faces. \~  
  \result \ru Возвращает строитель, если операция была выполнена успешно.
          \en Returns the constructor if the operation has been successfully performed. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCuttingSolid *) CreatePart(       MbFaceShell *          solid, 
                                               MbeCopyMode            sameShell, 
                                         const MbShellCuttingParams & cuttingParams,
                                               MbResultType &         res, 
                                               MbFaceShell *&         shell1,
                                               MbFaceShell *&         shell2 );

#endif // __CR_CUTTING_SOLID_H
