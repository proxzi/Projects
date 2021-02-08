////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель модифицированной оболочки.
         \en Constructor of a modified shell. 
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_MODIFIED_SOLID_H
#define __CR_MODIFIED_SOLID_H


#include <creator.h>
#include <op_shell_parameter.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель модифицированной оболочки.
           \en Constructor of a modified shell. \~
  \details \ru Строитель оболочки, выполняющий модификацию исходной оболочки.  
    Строитель выполняет следующие модификации исходной оболочки: \n 
    удаление из тела выбранных граней с окружением, \n 
    создание тела из выбранных граней с окружением, \n 
    перемещение выбранных граней с окружением относительно оставшихся граней тела, \n 
    замена выбранных граней тела эквидистантными гранями (перемещение по нормали, изменение радиуса), \n 
    замена выбранных граней тела деформируемыми  гранями (превращение в NURBS для редактирования).\n
           \en Constructor of a shell performing modification of the source shell.  
    Constructor performs the following modifications of the source shell: \n 
    deletion the selected faces with neighborhood from the solid, \n 
    creation of the solid from the selected faces with the neighborhood, \n 
    translation of the selected faces with the neighborhood relative to the remained faces of the solid, \n 
    replacement of the selected faces of the solid with the offset faces (translation along the normal, changing the radius), \n 
    replacement of the specified faces of the solid with the deformable faces (conversion to the NURBS for editing).\n \~ 
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbFaceModifiedSolid : public MbCreator {
protected: // \ru Данные класса. \en Data of class. 
  ModifyValues               parameters;  ///< \ru Параметры редактирования оболочки. \en Shell editing parameters. 
  SArray<MbItemIndex>        faceIndices; ///< \ru Идентификаторы модифицированных граней. \en Identifiers of the modified faces. 
  SArray<MbEdgeFacesIndexes> edgeIndices; ///< \ru Идентификаторы модифицированных рёбер.  \en Identifiers of the modified edges. 
  RPArray<MbSurface>         surfaces;    ///< \ru Массив-указателей на nurbs поверхности граней. \en Array of pointers to NURBS surfaces of the faces. 

public: 
  // \ru Конструктор по параметрам. \en Constructor by parameters. 
  MbFaceModifiedSolid( const ModifyValues & p, const SArray<MbItemIndex> & faces, 
                       RPArray<MbSurface> & surfs, const MbSNameMaker & names );
  // \ru Конструктор по параметрам. \en Constructor by parameters. 
  MbFaceModifiedSolid( const ModifyValues & p, const SArray<MbEdgeFacesIndexes> edges, 
                       const MbSNameMaker & names );
private: 
  // \ru Конструктор дублирующий. \en Duplicating constructor. 
  MbFaceModifiedSolid( const MbFaceModifiedSolid & init, MbRegDuplicate * ireg );
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbFaceModifiedSolid( const MbFaceModifiedSolid & init ); 

public: // \ru Деструктор \en Destructor 
  ~MbFaceModifiedSolid();

public: 

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию \en Create a copy 
  virtual bool        IsSame( const MbCreator & other, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  virtual bool        SetEqual ( const MbCreator & ); // \ru Сделать равным \en Make equal 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать по матрице \en Transform according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг по вектору \en Translation by the vector 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 
  virtual void        GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  /// \ru Построение оболочки \en Creation of a shell 
  virtual bool        CreateShell( MbFaceShell *& shell, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * items = NULL );
  virtual void        Refresh( MbFaceShell & outer ); ///< \ru Обновить форму оболочки \en Update shape of the shell 

          // \ru Дать параметры. \en Get the parameters. 
          void        GetParameters(       ModifyValues & params ) const { params = parameters; }
          // \ru Установить параметры. \en Set the parameters. 
          void        SetParameters( const ModifyValues & params )       { parameters = params; }

          void        GetFaceIndices( SArray<MbItemIndex> & faces ) const { faces = faceIndices; } // \ru Идентификаторы модифицированных граней. \en Identifiers of the modified faces. 
          void        GetEdgeIndices( SArray<MbEdgeFacesIndexes> & edges ) const { edges = edgeIndices; } // \ru Идентификаторы модифицированных рёбер.  \en Identifiers of the modified edges. 

private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbFaceModifiedSolid & );
          void        SurfacesFree(); // \ru Удалить поверхности \en Delete the surfaces 
          void        SurfacesAddRef(); // \ru Учесть поверхности \en Consider the surfaces 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbFaceModifiedSolid )
};

IMPL_PERSISTENT_OPS( MbFaceModifiedSolid )

//------------------------------------------------------------------------------
/** \brief \ru Построить модифицированную оболочку.
           \en Construct the modified shell. \~
  \details \ru Построить оболочку тела путём модификации исходной оболочки. 
    В зависимости от параметров возможны следующие модификации исходной оболочки: \n 
    удаление из тела выбранных граней с окружением, \n 
    создание тела из выбранных граней с окружением, \n 
    перемещение выбранных граней с окружением относительно оставшихся граней тела, \n 
    замена выбранных граней тела эквидистантными гранями (перемещение по нормали, изменение радиуса), \n 
    замена выбранных граней тела деформируемыми  гранями (превращение в NURBS для редактирования).\n 
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en Construct the solid's shell by modification the source shell. 
    The following modifications of the source shell are possible depend on the parameters: \n 
    deletion the selected faces with neighborhood from the solid, \n 
    creation of the solid from the selected faces with the neighborhood, \n 
    translation of the selected faces with the neighborhood relative to the remained faces of the solid, \n 
    replacement of the selected faces of the solid with the offset faces (translation along the normal, changing the radius), \n 
    replacement of the specified faces of the solid with the deformable faces (conversion to the NURBS for editing).\n 
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  outer      - \ru Исходная оболочка.
                           \en The source shell. \~
  \param[in]  sameShell  - \ru Режим копирования исходной оболочки.
                           \en Mode of copying the source shell. \~
  \param[in]  parameters - \ru Параметры модификации.
                           \en Parameters of the modification. \~
  \param[in]  faces      - \ru Изменяемые грани тела.
                           \en Faces to be modified. \~
  \param[in]  edges      - \ru Изменяемые рёроа тела.
                           \en Edges to be modified. \~
  \param[in]  names      - \ru Именователь операции.
                           \en An object defining names generation in the operation. \~
  \param[out] res        - \ru Код результата операции выдавливания.
                           \en The extrusion operation result code. \~
  \param[out] shell      - \ru Построенная оболочка.
                           \en The resultant shell. \~
  \result \ru Возвращает строитель оболочки.
          \en Returns the shell constructor. \~
  \ingroup Model_Creators
*/
// ---
MATH_FUNC (MbCreator *) CreateFaceModifiedSolid( MbFaceShell * outer, 
                                                 MbeCopyMode sameShell, 
                                                 const ModifyValues & parameters, 
                                                 const RPArray<MbFace> & faces, 
                                                 const RPArray<MbCurveEdge> & edges, 
                                                 const MbSNameMaker & names, 
                                                 MbResultType & res,
                                                 MbFaceShell *& shell );


#endif // __CR_MODIFIED_SOLID_H
