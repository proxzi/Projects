////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Строитель оболочки с уклонёнными гранями.
         \en Constructor of a shell with drafted faces. 
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CR_DRAFT_SOLID_H
#define __CR_DRAFT_SOLID_H


#include <creator.h>


//------------------------------------------------------------------------------
/** \brief \ru Строитель оболочки с уклонёнными гранями.
           \en Constructor of a shell with drafted faces. \~
  \details \ru Строитель оболочки с уклонёнными гранями для создания литейных уклонов.\n
           \en Constructor of a shell with drafted faces for pattern drafts creation. \~
  \ingroup Model_Creators
*/
// ---
class MATH_CLASS MbDraftSolid: public MbCreator {
protected:
  double              angle;        ///< \ru Угол уклона. \en Draft angle. 
  c3d::ItemIndices    faceIndices;  ///< \ru Номера множества уклоняемых граней. \en Indices of faces to draft. 
  MbeFacePropagation  fp;           ///< \ru Признак захвата граней ( face propagation ). \en Flag of face propagation. 
  // \ru Атрибуты, определяющие направление тяги (pull direction) и нейтральную изолинию уклона. \en Attributes determining the pull direction and the neutral isoline of the draft. 
  MbPlacement3D *     np;           ///< \ru Нейтральная плоскость ( neutral plane )         ( не обязателен ). \en Neutral plane (optional). 
  ptrdiff_t           edgeNb;       ///< \ru Номер прямолинейного ребра, направляющего уклон ( не обязателен ). \en The index of straight edge specifying the draft (optional). 
  SArray<ptrdiff_t> * pl;           ///< \ru Линии разъема (ребра) ( parting line  )         ( не обязателен ). \en Parting lines (of edge) (optional). 
  bool                reverse;      ///< \ru Обратное направление тяги. \en Reverse pull direction. 
  bool                step;         ///< \ru Ступенчатый способ уклона. \en Stepwise method of draft.  

public:
  /// \ru Конструктор уклона по известной нейтральной плоскости. \en Constructor of drafting by the given neutral plane. 
  MbDraftSolid( const MbPlacement3D &            nPlace,   // нейтральная плоскость ( neutral plane )
                      double                     ang,      // угол уклона
                const std::vector<MbItemIndex> & faceInds, // номера множества уклоняемых граней
                      MbeFacePropagation         faceProp, // признак захвата граней
                      bool                       rev, // обратное направление тяги
                const MbSNameMaker &             n )
    : MbCreator  ( n        )
    , angle      ( ang      ) 
    , faceIndices( faceInds )
    , fp         ( faceProp ) 
    , np         ( new MbPlacement3D( nPlace ) )
    , edgeNb     ( -1       )
    , pl         ( NULL     )
    , reverse    ( rev      )
    , step       ( false    )
  {
  }
  // \ru Конструктор уклона по линии разъема \en Constructor of drafting by the parting line 
  MbDraftSolid(       double              ang,       // угол уклона
                const MbPlacement3D *     nPlace,    // нейтральная плоскость ( neutral plane )
                      ptrdiff_t           edgeInd,   // номер прямолинейного ребра - направляющего уклон  ( не обязателен )
                      MbeFacePropagation  faceProp,  // признак захвата граней
                const SArray<ptrdiff_t> & partLines, // линии разъема (ребра) (parting line) (не обязателен)
                      bool                rev,       // обратное направление тяги
                      bool                st,        // ступенчатый способ уклона
                const MbSNameMaker &      n )
    : MbCreator  ( n        )
    , angle      ( ang      ) 
    , faceIndices(          )
    , fp         ( faceProp ) 
    , np         ( nPlace ? new MbPlacement3D( *nPlace ) : NULL )
    , edgeNb     ( edgeInd  )
    , pl         ( new SArray<ptrdiff_t>( partLines ) )
    , reverse    ( rev      )
    , step       ( st       )
  {
  }
private :
  MbDraftSolid( const MbDraftSolid &, MbRegDuplicate * );  // \ru Конструктор копирования \en Copy-constructor 
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en Declaration without implementation of the copy-constructor to prevent copying by default. 
  MbDraftSolid( const MbDraftSolid & ); 
public :
  virtual ~MbDraftSolid();

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeCreatorType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbCreator & Duplicate( MbRegDuplicate * = NULL ) const;
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );               // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL   );               // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D   &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual MbePrompt   GetPropertyName(); // \ru Выдать заголовок свойства объекта \en Get a name of object property 

  virtual bool        IsSame   ( const MbCreator &, double accuracy ) const; // \ru Являются ли объекты равными? \en Determine whether an object is equal? 
  virtual bool        SetEqual ( const MbCreator & );       // \ru Сделать равным \en Make equal 
  virtual bool        IsSimilar( const MbCreator & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 

  // \ru Общие функции твердого тела \en Common functions of solid 

  virtual bool        CreateShell( MbFaceShell *&, MbeCopyMode sameShell, 
                                   RPArray<MbSpaceItem> * = NULL ); // \ru Построение \en Construction 

private :
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void        operator = ( const MbDraftSolid & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbDraftSolid )
};

IMPL_PERSISTENT_OPS( MbDraftSolid )

//------------------------------------------------------------------------------
/** \brief \ru Построить оболочку с уклоном граней.
           \en Create a shell with drafted faces. \~
  \details \ru Для исходной оболочки построить оболочку с уклоном граней от нейтральной изоплоскости для создания литейных уклонов. \n
    Одновременно с построением оболочки функция создаёт её строитель.\n
           \en For the source shell create a shell with faces drafted from the neutral isoplane for pattern tapers creation. \n
    The function simultaneously creates the shell and its constructor.\n \~ 
  \param[in]  solid      - \ru Исходная оболочка.
                           \en The source shell. \~
  \param[in]  sameShell  - \ru Режим копирования исходной оболочки.
                           \en Mode of copying the source shell. \~
  \param[in]  np         - \ru Локальная система координат, плоскость XY которой является нейтральной плоскостью ( neutral plane ).
                           \en The local coordinate system XY plane of which is a neutral plane. \~
  \param[in]  angle      - \ru Угол уклона.
                           \en Draft angle. \~
  \param[in]  faces      - \ru Уклоняемые грани.
                           \en The faces to draft. \~
  \param[in]  fp         - \ru Признак захвата граней ( face propagation ).
                           \en Flag of face propagation. \~
  \param[in]  reverse    - \ru Флаг для обратного направления тяги.
                           \en Flag for reverse pull direction. \~
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
MATH_FUNC (MbCreator *) CreateDraft(       MbFaceShell *      solid,
                                           MbeCopyMode        sameShell,
                                     const MbPlacement3D &    np,
                                           double             angle,
                                     const RPArray<MbFace> &  faces,
                                           MbeFacePropagation fp,
                                           bool               reverse,
                                     const MbSNameMaker &     names,
                                           MbResultType &     res,
                                           MbFaceShell *&     shell );


#endif // __CR_DRAFT_SOLID_H
