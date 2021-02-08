////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Построение усеченной оболочки.
         \en Construction of a truncated shell. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __TRUNCATED_SHELL_H
#define __TRUNCATED_SHELL_H


#include <creator.h>
#include <cr_split_data.h>
#include <math_define.h>
#include <mb_enum.h>
#include <mb_operation_result.h>


class  MATH_CLASS  MbCurve;
class  MATH_CLASS  MbAxis3D;
class  MATH_CLASS  MbSpaceItem;
class  MATH_CLASS  MbPlacement3D;
class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbFace;
class  MATH_CLASS  MbSolid;
class  MATH_CLASS  MbSNameMaker;
struct MATH_CLASS  MbMergingFlags;


//------------------------------------------------------------------------------
/** \brief \ru Строитель усеченной оболочки.
           \en Constructor of a truncated shell. \~
  \details \ru Строитель усеченной оболочки режет исходную оболочку на части указанными элементами, 
    которыми могут служить двумерные кривые в локальной системе координат, трёхмерные кривые, поверхности и оболочки. \n
           \en Constructor of a truncated shell cuts the initial shell into parts by the specified elements 
    which can be two-dimensional curves in the local coordinate system, three-dimensional curves, surfaces and shells. \n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbTruncatedShell : public MbCreator {
private :
  std::vector<MbItemIndex>  selIndices; ///< \ru Идентификаторы выбранных граней усекаемой оболочки. \en Identifiers of selected faces of the shell being truncated. 
  MbSplitData               splitItems; ///< \ru Усекающие элементы c ориентациями. \en Truncating elements with orientations. 
  SArray<bool>              orients;    ///< \ru Ориентация усекающих элементов. \en Orientation of truncating elements. 
  bool                      mergeFaces; ///< \ru Сливать подобные грани (true). \en Whether to merge similar faces (true). 
  bool                      mergeEdges; ///< \ru Сливать подобные ребра (true). \en Whether to merge similar edges (true). 

public:
  /// \ru Конструктор по двумерным кривым. \en Constructor by two-dimensional curves. 
  MbTruncatedShell( const MbPlacement3D &, const RPArray<MbContour> &, bool same, 
                    const SArray<bool> & orients, const MbMergingFlags &, const MbSNameMaker & );
  /// \ru Конструктор по трехмерным кривым. \en Constructor by three-dimensional curves. 
  MbTruncatedShell( const RPArray<MbCurve3D> &, bool same, 
                    const SArray<bool> & orients, const MbMergingFlags &, const MbSNameMaker & );
  /// \ru Конструктор по поверхностям. \en Constructor by surfaces. 
  MbTruncatedShell( const RPArray<MbSurface> &, bool same, 
                    const SArray<bool> & orients, const MbMergingFlags &, const MbSNameMaker & );
  /// \ru Конструктор по строителям тела. \en Constructor by solid creators. 
  MbTruncatedShell( const MbSolid &, bool same, bool keepShell,
                    bool orient, const MbMergingFlags &, const MbSNameMaker & );

  virtual ~MbTruncatedShell();

private:
  MbTruncatedShell( const MbTruncatedShell &, MbRegDuplicate * );

public:
  virtual MbeCreatorType  IsA()  const; // \ru Тип элемента \en Type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 

  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName();                        // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem>   & ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  virtual size_t      GetCreatorsCount( MbeCreatorType ct ) const; // \ru Посчитать внутренние построители по типу. \en Count internal creators by type.
  virtual bool        GetInternalCreators( MbeCreatorType, c3d::ConstCreatorsSPtrVector & ) const; // \ru Получить внутренние построители по типу. \en Get internal creators by type.
  virtual bool        SetInternalCreators( MbeCreatorType, c3d::CreatorsSPtrVector & );            // \ru Получить внутренние построители по типу. \en Get internal creators by type.

  virtual bool        IsSame( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal?
  virtual bool        IsSimilar ( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual bool        SetEqual( const MbCreator & );         // \ru Сделать равным \en Make equal 

  // \ru Построение оболочки по исходным данным \en Construction of a shell from the given data 
  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL );

          // \ru Установить номера выбраных граней усекаемого тела \en Set indices of selected faces of the solid being truncated. 
          void        SetSelIndices( const std::vector<MbItemIndex> & selInds );

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbTruncatedShell )
OBVIOUS_PRIVATE_COPY( MbTruncatedShell )
};

IMPL_PERSISTENT_OPS( MbTruncatedShell )

//------------------------------------------------------------------------------
/** \brief \ru Построить усечённую оболочку.
           \en Build a truncated shell. \~
  \details \ru Построить усечённую оболочку резкой исходного тела на части указанными элементами, 
    которыми могут служить двумерные кривые в локальной системе координат, трёхмерные кривые, поверхности и оболочки.
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct a truncated shell by cutting the initial solid into parts by the specified elements 
    which can be two-dimensional curves in the local coordinate system, three-dimensional curves, surfaces and shells.
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  initSolid - \ru Исходное тело.
                          \en The initial solid. \~
  \param[in]  selIndices - \ru Идентификаторы выбранныых граней, приотсутствии - всё тело.
                           \en Identifiers of selected faces, if not specified - the whole solid. \~
  \param[in]  sameShell  - \ru Режим копирования исходной оболочки.
                           \en Mode of copying the initial shell. \~
  \param[in]  operNames - \ru Именователь граней.
                          \en An object for naming faces. \~
  \param[in]  items - \ru Усекающие объекты.
                      \en Truncating objects. \~
  \param[in]  orients - \ru Ориентация усекающих объектов.
                        \en The truncating objects orientation. \~
  \param[in]  curvesSplitMode - \ru Кривые используются как линии разъема.
                                \en The curves are used as parting lines. \~
  \param[in]  solidsCopyMode - \ru Режим копирования усекающих объектов.
                               \en Mode of copying the truncating objects. \~
  \param[in] mergeFlags - \ru Флаги слияния элементов оболочки.
                          \en Control flags of shell items merging. \~
  \param[out] res - \ru Код результата операции.
                    \en Operation result code. \~
  \param[out] resShell - \ru Построенная усеченная оболочка.
                         \en Constructed truncated shell. \~
  \param[out] resDir - \ru Направление фантома усечения.
                       \en Direction of truncation phantom. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) TruncateSurfacesSol( MbSolid                & initSolid,
                                             SArray<size_t>         & selIndices,
                                             MbeCopyMode              sameShell,
                                             const MbSNameMaker     & operNames,
                                             RPArray<MbSpaceItem>   & items,
                                             SArray<bool>           & orients,
                                             bool                     curvesSplitMode,
                                             MbeCopyMode              solidsCopyMode,
                                             const MbMergingFlags   & mergeFlags,       // флаги слияния граней и ребер
                                             MbResultType           & res,
                                             MbFaceShell           *& resShell,
                                             MbPlacement3D         *& resDir );


#endif // __TRUNCATED_SHELL_H
