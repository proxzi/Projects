////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Интерфейсы, используемые при импорте и экспорте.
         \en Interfaces used for import and export. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONV_MODEL_PROPERTIES_H
#define __CONV_MODEL_PROPERTIES_H


#include <model_item.h>
#include <attribute.h>
#include <conv_error_result.h>
#include <conv_annotation_item.h>
#include <conv_i_converter.h>
#include <mb_enum.h>
#include <templ_ifc_array.h>
#include <alg_indicator.h>
#include <vector>
#include <map>


class  MATH_CLASS MbPlacement3D;
class  MATH_CLASS MbItem;
class  MATH_CLASS MbName;
class             ItModelAssembly;
class             ItModelPart; 


/** \brief \ru Контейнер объектов аннотации.
           \en Container of annotation objects. \~
\ingroup Exchange_Base
*/
typedef std::vector<AnnotationSPtr> vector_of_annotation;


/** \brief \ru Ассоциация наборов аннотационных объектов элементам со счётчиком ссылок.
           \en Association of sets of annotation objects with elements with reference counter. \~
\ingroup Exchange_Base
*/
typedef std::map< SPtr<const MbItem>, vector_of_annotation > map_of_visual_items;


/** \brief \ru Контейнер текстовых блоков.
           \en Container of text blocks. \~
\ingroup Exchange_Base
*/
typedef std::vector< SPtr<MaTextItem> > vector_of_text;


//------------------------------------------------------------------------------
/** \brief \ru Типы линий, передаваемых через конвертер.
           \en Types of lines passed via converter. \~
\ingroup Data_Interface
*/
// ---
enum MbeLineFontPattern {
  lfp_BEGIN = 0,            ///< \ru Для удобства перебора. \en For the convenient search. 
  lfp_STEPcontinuous,       ///< \ru Непрерывная в конвертерах STEP и IGES. \en Continuous line in STEP and IGES (Solid) converters. 
  lfp_STEPchain,            ///< \ru Штрих-пунктирная в конвертерах STEP и IGES. \en Chain line( dash-dotted) in STEP and IGES converters.
  lfp_STEPchainDoubleDash,  ///< \ru Штриховая с двумя пунктирами в конвертерах STEP и IGES. \en Dash-double-dot line in STEP and IGES (Phantom) converter. 
  lfp_STEPdashed,           ///< \ru Штриховая в конвертерах STEP и IGES. \en Dash line in STEP and IGES converters.
  lfp_STEPdotted,           ///< \ru Пунктирная в конвертерах STEP и IGES. \en Dotted line in STEP and IGES converters. 
  lfp_END                   ///< \ru Для удобства перебора. \en For search 
};


//------------------------------------------------------------------------------
/** \brief \ru Отображение точек, передаваемых через конвертер.
           \en Representation of points passed via converter. \~
\ingroup Data_Interface
*/
// ---
enum MbeDotMarkerSymbol {
  dms_BEGIN = 0,          ///< \ru Для удобства перебора. \en For the convenient search. 
  dms_STEPdot,            ///< \ru Точка. \en A point. 
  dms_STEPx,              ///< \ru Косой крест. \en x - cross. 
  dms_STEPplus,           ///< \ru Прямой крест. \en Plus. 
  dms_STEPasterisk,       ///< \ru Звёздочка. \en Asterisk. 
  dms_STEPring,           ///< \ru Кольцо. \en Ring. 
  dms_STEPsquare,         ///< \ru Квадрат. \en Square. 
  dms_STEPtriangle,       ///< \ru Треугольник. \en Triangle. 
  dms_END                 ///< \ru Для удобства перебора. \en For the convenient search. 
};


//------------------------------------------------------------------------------
/** \brief \ru Тип объектов, которые необходимо выдать для экспорта или добавить при импорте.
           \en Type of objects to be returned for export or to be added while importing. \~
\ingroup Data_Interface
*/
// ---
enum MbeGettingItemType {
  git_Item = 0,       ///< \ru Получить элементы всех типов. \en Get items of all types.
  git_Solid,          ///< \ru Получить тела. \en Get solids.  
  git_Surface,        ///< \ru Получить поверхности. \en Get surfaces.
  git_WireFrame,      ///< \ru Получить проволочные каркасы. \en Get wire frames.
  git_PlaneInstance,  ///< \ru Получить вставки плоских объектов (эскизы). \en Get plane instances (drafts).
  git_PointFrame,     ///< \ru Получить точечные каркасы. \en Get point frames.
  git_AssociatedGeometry ///< \ru Получить ассоциированные геометрические объекты (резьбы). \en Get associated geometry objects (threads).
};


//------------------------------------------------------------------------------
/** \brief \ru Интерфейс свойств вставки, подсборки или детали.
           \en Interface of properties of an instance, a subassembly or a part. \~
\ingroup Exchange_Interface
*/
// ---
class ItModelInstanceProperties : public MbRefItem
{
public:

  /// \ru Атрибуты. \en Attributes. 

  /// \ru Задать атрибуты. \en Set attributes. 
  virtual bool SetAttributes( const c3d::AttrSPtrVector& /*attributes*/ ) = 0;

  /// \ru Получить атрибуты. \en Get attributes. 
  virtual c3d::AttrSPtrVector GetAttributes( ) const = 0;// { return c3d::AttrSPtrVector(); }


  /// \ru Технические требования. \en Technical requirements. 

  /// \ru Получить технические требования. \en Get technical requirements. 
  virtual void          GetRequirements( vector_of_annotation &, eTextForm ) const = 0; 

  /// \ru Задать технические требования. \en Set technical requirements. 
  virtual void          SetRequirements( const vector_of_annotation & ) = 0; 

  /// \ru Наименование. \en Name. 

  /// \ru Задать имя документа. \en Set document's name. 
  DEPRECATE_DECLARE virtual bool          SetName( const std::string& /*name*/ ) { return false; }; 
  /// \ru Получить имя документа. \en Get document's name. 
  DEPRECATE_DECLARE virtual std::string   Name()          const { return std::string(); };

  /// \ru Обозначение. \en Marking. 

  /// \ru Задать обозначение документа. \en Set document marking. 
  DEPRECATE_DECLARE virtual bool          SetMarking( const std::string& /*name*/ ) { return false; }; 
  /// \ru Получить обозначение документа. \en Get document marking. 
  DEPRECATE_DECLARE virtual std::string   Marking()          const { return std::string(); };

  /// \ru Автор. \en Author. 

  /// \ru Задать имя автора. \en Set author's name. 
  DEPRECATE_DECLARE virtual bool          SetAuthor( const std::string& /*name*/ ) { return false; }; 
  /// \ru Получить имя автора. \en Get author's name. 
  DEPRECATE_DECLARE virtual std::string   Author()          const { return std::string(); };

  /// \ru Организация. \en Organization. 

  /// \ru Задать имя автора. \en Set author's name. 
  DEPRECATE_DECLARE virtual bool          SetOrganization( const std::string& /*name*/ ) { return false; }; 
  /// \ru Получить имя автора. \en Get author's name. 
  DEPRECATE_DECLARE virtual std::string   Organization()          const { return std::string(); };

  /// \ru Комментарий. \en Comment. 

  /// \ru Задать комментарии. \en Set the comments.
  DEPRECATE_DECLARE virtual bool          SetComments( const std::vector< std::string > & /*comments*/ ) { return false; }; 
  /// \ru Получить следующий комментарий. \en Get the next comment. 
  DEPRECATE_DECLARE virtual std::vector< std::string > GetComments( ) const { return std::vector< std::string >(); }; 

  /// \ru Цвет сборки, детали или вставки. \en Color of an assembly, a part or an instance. 

  /// \ru Задать цветовые свойства. \en Set color properties. 
  DEPRECATE_DECLARE virtual bool          SetColor( const MbAttributeContainer & ) { return false; }; 
  /// \ru Получить цветовые свойства. \en Get color properties. 
  DEPRECATE_DECLARE virtual bool          GetColor( MbAttributeContainer & ) const { return false; }; 

  /// \ru Цвет тела. \en Solid color. 

  /// \ru Задать цветовые свойства оболочки. \en Set color properties of a shell. 
  DEPRECATE_DECLARE virtual bool          SetColor( const MbAttributeContainer &, size_t ) { return false; }; 

  /// \ru Цвет грани. \en Face color. 

  /// \ru Задать цветовые свойства грани \en Set color properties of a face. 
  DEPRECATE_DECLARE virtual bool          SetColor( const MbAttributeContainer &, const MbName & ) { return false; }; 
  /// \ru Получить цветовые свойства грани. \en Get color properties of a face. 
  DEPRECATE_DECLARE virtual bool          GetColor( MbAttributeContainer &, const MbName & ) const { return false; }; 
};


//------------------------------------------------------------------------------
/** \brief \ru Интерфейс вставки компоненты.
           \en Interface of the component instance. \~
\ingroup Exchange_Interface
*/
// ---
class ItModelInstance : public ItModelInstanceProperties
{
public:
  // \ru Выдать идентификатор сборки или детали \en Get identifier of an assembly or a part 
  virtual void            * GetId() = 0;
  /// \ru Выдать расположение этой вставки в координатах родителя. \en Get the placement of this instance in parent's coordinates. 
  virtual bool              GetPlacement( MbPlacement3D & ) const = 0; 
  /// \ru Это сборка? \en Is it an assembly? 
  virtual bool              IsAssembly() const = 0; 
  /// \ru Это ни сборка, ни деталь? \en Is it neither an assembly nor a part? 
  virtual bool              IsEmpty() const = 0; 

  /** \brief \ru Создать пустую сборку при импорте и увеличить счётчик ссылок на 1.
             \en Create an empty assembly while importing and increase the reference counter by 1. \~  
  \param[in] place - \ru ЛСК сборки в родительской модели.
                     \en LCS of the assembly in the parent's model. \~
  \param[in] fileName - \ru Имя сборки.
                        \en Assembly name. \~
  \return \ru Экземпляр сборки, если операция прошла успешно, NULL в противном случае.
          \en Instance of an assembly if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelAssembly> CreateAssembly( const MbPlacement3D &place, const std::vector< SPtr<MbItem> > & componentItems, const c3d::string_t& fileName ) = 0;
  
  /** \brief \ru Создать деталь при импорте.
             \en Create a part while importing. \~
  \details \ru Увеличить счётчик ссылок детали на 1.
           \en Increase the reference counter of a part by 1. \~
  \param[in] place - \ru ЛСК детали.
                     \en LCS of a part. \~
  \param[in] solids - \ru Тела, включаемые в деталь.
                      \en Solids included in the part. \~
  \param[in] fileName - \ru Название детали.
                        \en Solid's name. \~
  \return \ru Экземпляр детали, если операция прошла успешно, NULL в противном случае.
          \en Instance of the part if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelPart>   CreatePart( const MbPlacement3D &place, const std::vector< SPtr<MbItem> > & componentItems, const c3d::string_t& fileName ) = 0;

  /** \brief \ru Получить сборку для экспорта.
             \en Get an assembly for export. \~
  \return \ru Экземпляр сборки, если операция прошла успешно, NULL в противном случае.
          \en Instance of an assembly if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelAssembly> GetInstanceAssembly( ) = 0;


  /** \brief \ru Получить деталь для экспорта.
             \en Get the detail for export. \~
  \return \ru Экземпляр детали, если операция прошла успешно, NULL в противном случае.
          \en Instance of the part if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelPart>   GetInstancePart( ) = 0;

  /** \brief \ru Создать подсборку при импорте, и её вставку.
             \en Create a subassembly and its instance while importing. \~
  \param[in] place - \ru ЛСК сборки в родительской модели.
                     \en LCS of the assembly in the parent's model. \~
  \param[in] existing - \ru Сборка, подлежащая вставке.
                        \en An assembly to insert. \~
  \return \ru true, если операция прошла успешно, false в противном случае.
          \en true if the operation succeeded, false - otherwise. \~
  */
  virtual bool              SetAssembly( const MbPlacement3D & place, const ItModelAssembly * existing ) = 0;

  /** \brief \ru Создать деталь при импорте, и её вставку.
             \en Create a part while importing and its instance. \~
  \param[in] place - \ru ЛСК детали в родительской модели.
                     \en LCS of a part in the parent's model. \~
  \param[in] existing - \ru Деталь, подлежащая вставке.
                        \en Detail to insert. \~
  \return \ru true, если операция прошла успешно, false в противном случае.
          \en true if the operation succeeded, false - otherwise. \~
  */
  virtual bool              SetPart( const MbPlacement3D & place, const ItModelPart * existing ) = 0;

};


//------------------------------------------------------------------------------
/** \brief \ru Интерфейс сборки.
           \en Interface of the assembly. \~
  \details \ru Экземпляр должен порождаться в методах CreateAssembly реализаций 
  интерфейсов ItModelDocument и ItModelAInstance. Собственные элементы детали 
  должны передаваться как параметры конструктора. \~ \en The object should be 
  created in the CreateAssembly method of the implementations of the 
  ItModelDocument and ItModelInstance interfaces. Own Items of the detail should 
  be arguments of the constructor.
\ingroup Exchange_Interface
*/
// ---
class ItModelAssembly : public ItModelInstanceProperties
{
public:
  /** \brief \ru Получить имя файла сборки без пути и расширения  для экспорта.
             \en Get the file name of an assembly without the path and the extension for export. \~
  \return \ru Имя файла сборки.
          \en An assembly file name. \~
  */
  virtual  c3d::path_string PureFileName() const = 0;

  /** \brief \ru Получить пустой интерфейс вставки для создания подсборки или детали при импорте.
             \en Get an empty interface of the insertion for creation of subassembly or a part while importing. \~
  \details \ru Увеличить счётчик ссылок на 1.
           \en Increase the reference counter by 1. \~
  \return \ru Интерфейс вставки, если операция прошла успешно или NULL в противном случае.
          \en Interface of the instance if the operation succeeded and NULL otherwise. \~
  */
  virtual SPtr<ItModelInstance> PrepareInstance() = 0;

  /** \brief \ru Получить интерфейс следующей вставки для создания подсборки или детали при экспорте.
             \en Get the interface of the next insertion for creation of a subassembly or a part while exporting. \~
  \return \ru Интерфейс вставки, если операция прошла успешно или NULL в противном случае.
          \en Interface of the insertion if the operation succeeded and NULL otherwise. \~
  */
  virtual SPtr<ItModelInstance> NextInstance( bool includeInvisible ) = 0;

  /// \ru Выдать ЛСК, общую для элементов компонента. \en Get the placement, which all the items of the component use for transformation.
  virtual bool GetPlacement( MbPlacement3D & ) const { return false; }; 

  /** \brief \ru Получить объекты из корня сборки при экспорте.
             \en Get objects from the assembly root while exporting. \~
  \param[out] items - \ru Наполняемый массив (состоит из объектов классов MbSolid, MbCurve3D, MbCartPoint3D).
                      \en Array to fill (consist of objects of classes MbSolid, MbCurve3D, MbCartPoint3D). \~
  \param[in] includeInvisible - \ru Если true, то выдаются все тела, включая невидимые, если false - только видимые.
                                \en If true, then all the solids are returned, including invisible ones, if false - only visible ones. \~
  */
  virtual void              GetItems( std::vector< SPtr<MbItem> > & items, MbeGettingItemType itemType, bool includeInvisible ) const = 0;

  /** \brief \ru Добавить объекты в корень сборки при импорте.
             \en Add objects to the assembly root while importing. \~
  \param[in] items - \ru Объекты, добавляемые в модель (тела, кривые и точки).
                     \en Objects to add to the model (solids, curves and points). \~
  */
  virtual void              AddItems( const std::vector< SPtr<MbItem> > & items ) = 0;

  /** \brief \ru Получить элементы аннотации из сборки.
             \en Get elements of annotation from the assembly. \~
  \param[in] eTextForm - \ru Форма представления текста.
                          \en Text representation form. \~  
  \param[in] includeInvisible - \ru Если true, то выдаются все объекты аннотации, включая невидимые, если false - только видимые.
                                \en If true, all the annotation objects are returned, including invisible ones, if false - only visible ones. \~
  \return \ru Контейнер объектов аннотации.
          \en Vector of annotation objects. \~
  */
  virtual vector_of_annotation GetAnnotationItems( eTextForm, bool ) const { return vector_of_annotation(); }; // Реализация будет удалена после того, как она будет осуществлена на стороне 3D
  virtual vector_of_annotation GetAnnotationItems( eTextForm ) const  { return vector_of_annotation(); }; // Будет удалена после её реализации на стороне 3D

  /** \brief \ru Задать элементы аннотации в сборке.
             \en Set elements of annotation in the assembly. \~
  \param[in] sourceDim - \ru Элементы аннотации
                          \en Elements of annotation. \~
  */
  virtual void          SetAnnotationItems( const vector_of_annotation & ) = 0;

};


//------------------------------------------------------------------------------
/** \brief \ru Интерфейс детали.
           \en Interface of a part. \~
  \details \ru Экземпляр должен порождаться в методах CreatePart реализаций 
  интерфейсов ItModelDocument и ItModelAInstance. Собственные элементы детали 
  должны передаваться как параметры конструктора. \~ \en The object should be 
  created in the CreatePart method of the implementations of the 
  ItModelDocument and ItModelInstance interfaces. Own Items of the detail should 
  be arguments of the constructor.
\ingroup Exchange_Interface
*/
// ---
class ItModelPart : public ItModelInstanceProperties
{
public:
  /** \brief \ru Получить имя файла детали без пути и расширения  для экспорта.
             \en Get the file name of a part without the path and extension for export. \~
  \return \ru Имя файла детали.
          \en A part file name. \~
  */
  virtual c3d::path_string PureFileName() const = 0;

  /** \brief \ru Получить пустой интерфейс вставки для создания подсборки или детали при импорте.
             \en Get an empty interface of the insertion for creation of subassembly or a part while importing. \~
  \details \ru Увеличить счётчик ссылок на 1.
           \en Increase the reference counter by 1. \~
  \return \ru Интерфейс вставки, если операция прошла успешно или NULL в противном случае.
          \en Interface of the instance if the operation succeeded and NULL otherwise. \~
  */
  virtual SPtr<ItModelInstance> PrepareInstance() = 0;

  /** \brief \ru Получить интерфейс следующей вставки для создания подсборки или детали при экспорте.
             \en Get the interface of the next insertion for creation of a subassembly or a part while exporting. \~
  \return \ru Интерфейс вставки, если операция прошла успешно или NULL в противном случае.
          \en Interface of the insertion if the operation succeeded and NULL otherwise. \~
  */
  virtual SPtr<ItModelInstance> NextInstance( bool includeInvisible ) = 0;

  /// \ru Выдать ЛСК, общую для элементов компонента. \en Get the placement, which all the items of the component use for transformation.
  virtual bool GetPlacement( MbPlacement3D & ) const { return false; }; 

  /** \brief \ru Получить объекты из детали при экспорте.
             \en Get objects from the part while exporting. \~
  \param[out] items - \ru Наполняемый массив (состоит из объектов классов MbSolid, MbWireFrame, MbPointFrame).
                      \en Array to fill (consists of objects of classes MbSolid, MbWireFrame, MbPointFrame). \~
  \param[in] itemType - \ru Тип объектов, которыми нужно наполнить массив.
                        \en Type of objects the array should be filled with. \~
  \param[in] includeInvisible - \ru Если true, то выдаются все тела, включая невидимые, если false - только видимые.
                                \en If true, all the solids are returned, including invisible ones, if false - only visible ones. \~
  */
  virtual void          GetItems( std::vector< SPtr<MbItem> > & items, MbeGettingItemType itemType, bool includeInvisible ) const = 0;

  /** \brief \ru Добавить объекты в деталь при импорте.
             \en Add objects to a part while importing. \~
  \param[in] items - \ru Объекты, добавляемые в модель (кривые и точки).
                     \en Objects to be added to the model (curves and points). \~
  */
  virtual void          AddItems( const std::vector< SPtr<MbItem> > & items ) = 0;

  /** \brief \ru Получить элементы аннотации из детали.
             \en Get elements of annotation from the detail. \~
  \param[in] eTextForm - \ru Форма представления текста.
                          \en Text representation form. \~  
  \param[in] includeInvisible - \ru Если true, то выдаются все объекты аннотации, включая невидимые, если false - только видимые.
                                \en If true, all the annotation objects are returned, including invisible ones, if false - only visible ones. \~
  \return \ru Контейнер объектов аннотации.
          \en Vector of annotation objects. \~
  */
  virtual vector_of_annotation GetAnnotationItems( eTextForm, bool ) const { return vector_of_annotation(); }; // Реализация будет удалена после того, как она будет осуществлена на стороне 3D
  virtual vector_of_annotation GetAnnotationItems( eTextForm ) const { return vector_of_annotation(); }; // Будет удалена после её реализации на стороне 3D


  /** \brief \ru Задать элементы аннотации в детали.
             \en Set elements of annotation in the part. \~
  \param[in] sourceDim - \ru Элементы аннотации
                          \en Elements of annotation. \~
  */
  virtual void          SetAnnotationItems( const vector_of_annotation & ) = 0;

};

//------------------------------------------------------------------------------
/** \brief \ru Интерфейс документа модели сборки или детали.
           \en Interface of document of an assembly model or a part model. \~
\ingroup Exchange_Interface
*/
// ---
class ItModelDocument : public MbRefItem
{
public:
  /// \ru Это сборка? \en Is it an assembly? 
  virtual bool              IsAssembly() const = 0;
  /// \ru Это ни сборка, ни деталь? \en Is it neither an assembly nor a part? 
  virtual bool              IsEmpty() const = 0; 

  /** \brief \ru Прообраз новой интерфейсной функции - задать модель ЛСК, относительно которой позиционируется модель.
             \en Prototype of a new interface function - get the placement the model is defined in. \~
  */
  //virtual MbPlacement3D     GetOriginLocation() const = 0;

  /** \brief \ru Прообраз новой интерфейсной функции - задать модель для наполнения.
             \en Prototype of a new interface function - set a model to fill. \~
  */
  virtual void              SetContent( MbItem* /*content*/) = 0;

  /** \brief \ru Прообраз новой интерфейсной функции - получить наполнение.
             \en Prototype of a new interface function - get the filling. \~
  */
  virtual MbItem *          GetContent() /*{ return NULL; }*/ = 0;

  /** \brief \ru Создать документ с новой сборкой при импорте.
             \en Create a document with a new assembly while importing. \~
  \details \ru Увеличить счётчик ссылок результирующего документа на 1.
           \en Increase the reference counter of the resultant document by 1. \~  
  \param[in] fileName - \ru Имя сборки.
                        \en Assembly name. \~
  \param[in] solids - \ru Тела, добавляемые в сборку.
                      \en Solids to add into the assembly. \~
  \return \ru Экземпляр сборки, если операция прошла успешно, NULL в противном случае.
          \en Instance of an assembly if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelAssembly> CreateAssembly( const std::vector< SPtr<MbItem> > & componentItems, const c3d::string_t& fileName ) = 0;


  /** \brief \ru Создать документ с новой деталью при импорте.
             \en Create a document with a new part while importing. \~
  \details \ru Увеличить счётчик ссылок результирующего документа на 1.
           \en Increase the reference counter of the resultant document by 1. \~  
  \param[in] solids - \ru Тела, добавляемые в деталь.
                      \en Solids to add into a part. \~
  \param[in] fileName - \ru Имя детали.
                        \en A part name. \~
  \return \ru Экземпляр детали, если операция прошла успешно, NULL в противном случае.
          \en Instance of the part if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelPart>   CreatePart( const std::vector< SPtr<MbItem> > & componentItems, const c3d::string_t& fileName ) = 0;

  /** \brief \ru Получить сборку для экспорта.
             \en Get an assembly for export. \~
  \details \ru Увеличить счётчик ссылок результирующей сборки на 1.
           \en Increase the reference counter of the resultant assembly by 1. \~
  \return \ru Экземпляр сборки, если операция прошла успешно, NULL в противном случае.
          \en Instance of an assembly if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelAssembly> GetInstanceAssembly( ) = 0;


  /** \brief \ru Получить деталь для экспорта.
             \en Get the detail for export. \~
  \details \ru Увеличить счётчик ссылок результирующей детали на 1.
           \en Increase the reference counter of the resultant part by 1. \~
  \return \ru Экземпляр детали, если операция прошла успешно, NULL в противном случае.
          \en Instance of the part if the operation succeeded, NULL - otherwise. \~
  */
  virtual SPtr<ItModelPart>   GetInstancePart( ) = 0;

  /** \brief \ru Завершить импорт и сохранить документ.
             \en Complete the import and save the document. \~
  \return \ru true, если операция прошла успешно, false в противном случае.
          \en true if the operation succeeded, false - otherwise. \~
  \param[in] \ru indicator Объект для отображения хода процесса.
             \en indicator An object indicating a process progress. \~
  */
  virtual bool              FinishImport( IProgressIndicator * indicator  ) = 0;

  /** \brief \ru Получить элементы аннотации, соответствующие элементам геометрической модели.
             \en Get elements of annotation, corresponding items of geometric model. \~
  \param[in] eTextForm - \ru Форма представления текста.
                          \en Text representation form. \~  
  \return \ru Контейнер объектов аннотации.
          \en Vector of annotation objects. \~
  */
  virtual map_of_visual_items GetAnnotationItems( eTextForm ) const = 0; 

  /// \ru Задать размеры. \en Set sizes. 
  virtual void              SetAnnotationItems( const map_of_visual_items& ) = 0; 

  /// \ru Открыть документ. \en Open a document.  
  virtual void               OpenDocument() = 0; 

};



//------------------------------------------------------------------------------
/** \brief \ru Реализация документа модели, формирующая регулярную структуру.
           \en Implementation of model document which has regular structure. \~
\ingroup Exchange_Interface
*/
// ---
class CONV_CLASS C3dModelDocument: public ItModelDocument {

  SPtr<ItModelPart> part; ///< \ru Представление в виде детали. \en Representation as detail.
  SPtr<ItModelAssembly> assembly; ///< \ru Представление в виде сборки. \en Representation as assembly.
  map_of_visual_items visualItems; ///< \ru Элементы аннотации. \en Annotation items.
  c3d::ItemSPtr rawContent;
public:

  virtual ~C3dModelDocument(); ///< \ru Деструктор. \en Descructor.

  // Является ли сборкой.
  virtual bool              IsAssembly() const;
  // Пуст ли.
  virtual bool              IsEmpty() const;
  // Задать модель напрямую.
  virtual void              SetContent( MbItem* /*content*/);
  // Выдать модель напрямую.
  virtual MbItem *          GetContent();
  // Создать сборку.
  virtual SPtr<ItModelAssembly> CreateAssembly( const std::vector< SPtr<MbItem> > & componentItems, const c3d::string_t& fileName );
  // Создать деталь.
  virtual SPtr<ItModelPart>   CreatePart( const std::vector< SPtr<MbItem> > & componentItems, const c3d::string_t& fileName );
  // Выдать сборку.
  virtual SPtr<ItModelAssembly> GetInstanceAssembly( );
  // Выдать деталь.
  virtual SPtr<ItModelPart>   GetInstancePart( );
  // Завершить импорт.
  virtual bool              FinishImport( IProgressIndicator *  );
  // Выдать элементы аннотации.
  virtual map_of_visual_items GetAnnotationItems( eTextForm ) const; 
  // Задать элементы аннотации.
  virtual void              SetAnnotationItems( const map_of_visual_items& vi );
  // Открыть документ.
  virtual void              OpenDocument();

  /// \ru Зарегистрировать элемент аннотации. \en Register annotation object.
  void RegisterAnnotation( c3d::ItemSPtr component, const vector_of_annotation& annotation, const vector_of_annotation& requirements );
};


typedef C3dModelDocument RegularModelDocument;
typedef C3dModelDocument ConvModelDocument;


//------------------------------------------------------------------------------
/** \brief \ru Упрощенная реализация интерфейса свойств конвертера.
           \en Simple implementation of converter's properties. \~
\ingroup Exchange_Interface
*/
class CONV_CLASS ConvConvertorProperty3D : public IConvertorProperty3D {
public:  
  std::string       docName;  ///< \ru Имя документа. \en Document name.  
  c3d::path_string  fileName; ///< \ru Имя файла. \en File name.
  bool              fileASCII; ///< \ru Экспортировать ли в текстовый файл (если формат поддерживает двоичный). \en Export to text file (if format supports binary one).
  long int          formatVersion; /// \ru Версия формата при экспорте. \en The version of format for export.
  bool              exportIGESTopology; ///< \ru Экспортировать ли топологию в IGES. \en Export topology items into IGES.
  std::vector<bool> ioPermissions; ///< \ru Фильтр объектов по типам. \en Type objects filter.
  std::map<MbeConverterStrings, std::string> propertyStrings; ///< \ru Особые значения сведений о документе. \en Specific values of documents properties.
  eTextForm         annotTextReprSTEP; ///< \ru Представление текста элементов аннотации. \en Text representation in annotation items.
  MbPlacement3D     originLocation; ///< \ru ЛСК документа. \en Own placement of the document.
  bool              replaceLocationsToRight; ///< \ru Следует ли принудительно преобразовывать ЛСК объектов к правым (для форматов, допускающих левые). \en Force replacement of locations to right ones.
  bool              enableAutostitch; ///< \ru Сшивать ли поверхности автоматически. \en Automatically stitch surfaces into shells.
  double            autostitchPrecision; ///< \ru Точность сшивки. \en Stitch precision.
  bool              showMessages; ///< \ru Отображать ли сообщения. \en Invoke messages show.
  MbStepData        tesseleationStepData; ///< \ru Параметры триангуляции при экспорте в STL и VRML. \en Tessellation parameters for export into STL and VRML.
  MbStepData        LOD0StepData; ///< \ru Параметры триангуляции при экспорте в JT. \en Tessellation parameters for export into JT.
  bool              dualSeams; ///< \ru Признак сдваивания швов при экспорте в STL и VRML. \en Make dual seams when export into STL and VRML.
  bool              joinSimilarFaces; ///< \ru Выполнять ли слияние подобных граней. \en Whether to join similar faces.
  bool              addRemovedFacesAsShells; ///< \ru Добавлять ли удаленные грани в качестве отдельных оболочек. \en Whether to add removed faces as shells.
  double            lengthUnitsFactor; ///< \ru Единицы длины модели. \en Length units of the model.
  double            appUnitsFactor; ///< \ru Единицы длины модели пользовательского приложения. \en Length units of the model used in user application.
  bool              auditEnabled;
  
  /// \ru Сведения о сообщениях конвертера. \en Converter message data.
  struct LogRecord {
    ptrdiff_t id; ///< \ru Идентификатор записи. \en Record id.
    eMsgType msgType; ///< \ru Тип сообщения. \en Message type.
    eMsgDetail msgText; ///< \ru Код сообщения. \en Message code.
  };
  
  std::vector< LogRecord > logRecords; ///< \ru Сообщения конвертера. \en Converter messages.

public:

  ConvConvertorProperty3D(); ///< \ru Конструктор. \en Constructor.

  /// \ru Получить имя документа. \en Get document's name. 
  virtual const std::string GetDocumentName   () const { return docName; };
  /// \ru Получить имя файла для конвертирования. \en Get file name for converting. 
  virtual const c3d::path_string FullFilePath  () const { return fileName; };
  /// \ru Является ли файл текстовым. \en Whether the file is a text file. 
  virtual bool           IsFileAscii      () const;
  /// \ru Получить версию формата при экспорте. \en Get the version of format for export.
  virtual long int       GetFormatVersion () const;
  /// \ru Следует ли экспортировать только поверхности ( введено для работы конвертера IGES ). \en Whether to export only surfaces (introduced for work with converter IGES ). 
  virtual bool           IsOutOnlySurfaces() const;
  /// \ru Является ли экспортируемый документ сборкой. \en Whether the document for export is an assembly. 
  virtual bool           IsAssembling     () const { return true; }; 
  /// \ru Получить значение разрешения на импорт экспорт объектов определенного типа. \en Get the value of permission for import-export of objects of a certain type. 
  virtual bool           GetIoPermission( MbeIOPermiss nPermission ) const;
  /// \ru Получить значения разрешений на импорт экспорт объектов определенных типов. \en Get values of permission for import-export of objects of certain types. 
  virtual void           GetIoPermissions( std::vector<bool>& ioPermissions ) const; 
  /// \ru Установить разрешение на импорт экспорт объектов определенного типа. \en Set permission for import-export of objects of a certain type. 
  virtual void           SetIoPermission( MbeIOPermiss nPermission, bool isSet );
  /// \ru Получить значение специфичной строки для конвертера. \en Get the value of a certain string for the converter. 
  virtual bool           GetPropertyString ( MbeConverterStrings nString, std::string &  propertyString ) const; 
  /// \ru Установить значение специфичной строки для конвертера. \en Set the value of a certain string for the converter. 
  virtual void           SetPropertyString ( MbeConverterStrings nString, const std::string &  propertyString ); 
  /// \ru Представление текста в аннотационных объектах. \en Text representation in annotation objects. 
  virtual eTextForm      GetAnnotationTextRepresentation () const;
  /// \ru Следует ли компоненты экспортировать в разные файлы (если позволяет формат). \en Export components into separate files ( if provided in format). 
  virtual bool           ExportComponentsSeparately() const;
  /// \ru Получить ЛСК, относительно которой позиционирована модель. \en Get the location, the model is placed in.
  virtual MbPlacement3D  GetOriginLocation() const;
  /// \ru Заменять ли принудительно СК компонент на правые. \en Replace components' placements to right-oriented.
  virtual bool           ReplaceLocationsToRight() const;
  /**  \brief \ru Сшивать ли поверхности автоматически.
              \en If surfaces should be stitched automatically. \~
    \return \ru true - Сшивать поверхности автоматически, false - Спросить пользователя, сшивать ли поверхности.
            \en true - Stitch surfaces automatically, false - Ask user first time. \~
    \param[out] stitchPrecision - \ru Точность сшивки.
                                  \en Stitch precision. \~
  */  virtual bool           EnableAutoStitch( double& /*stitchPrecision*/ ) const;

  /// \ru Получить множитель единиц длины по отношению к миллиметру. \en Get the factor of the length units to millimeters.
  virtual double         LengthUnitsFactor() const;

  /**  \brief \ru Получить множитель единиц длины по отношению к миллиметру в модели приложения. 
  \en Get the factor of the length units to millimeters in the application model. \~  
  */
  virtual double         AppLengthUnitsFactor() const;

  /**  \brief \ru Сделать запись в журнал конвертирования.
              \en Make a record in the converter report. \~
    \param[in] id - \ru Идентификатор элемента внутри файла стороннего формата.
                    \en Identifier of an element inside the file of a foreign format. \~
    \param[in] msgType - \ru Тип сообщения.
                         \en Message type. \~
    \param[in] msgText - \ru Код сообщения.
                         \en Message code. \~
  */
  virtual void           LogReport( ptrdiff_t id, eMsgType msgType, eMsgDetail msgText );

//   /**  \brief \ru Следует ли показывать сообщения и диалоги пользователю. \en Whether to show messages and dialog to the user. \~
//    \details \ru Обеспечивает работу через API. \en Provide possibility for work via API. \~
//    \return \ru true - обычная работа, false - через API. \en true - ordinary work, false - via API. \~
//   */
   virtual bool          CanShowMessages() const;

  /// \ru Дать данные вычисления триангуляции (для конвертера STL и VRML). \en Get data for step calculation during triangulation (for STL, VRML only).
  virtual MbStepData     TesselationParameters() const;
  /// \ru Дать данные вычисления триангуляции уровня детализации (для конвертера JT). \en Get data for step calculation during triangulation of LOD0 (for JTonly).
  virtual MbStepData    LOD0TesselationParameters() const;
  /// \ru Получить флаг сохранения совпадающих точек швов. (для конвертера STL и VRML). \en Whether to keep coincident points of seams (for STL, VRML only).
  virtual bool           DualSeams() const;
  /// \ru Задать флаг сохранения совпадающих точек швов. (для конвертера STL и VRML). \en Whether to keep coincident points of seams (for STL, VRML only).
  virtual void           DualSeams( bool );
  /// \ru Проводить ли аудит траснляции. \en Whether to audit the translation.
  virtual bool          TotalAudit();
  /// \ru Выполнять ли слияние подобных граней. \en Whether to join similar faces.
  virtual bool          JoinSimilarFaces() const { return joinSimilarFaces; }
  /// \ru Добавлять ли удаленные грани в качестве оболочек. \en Whether to add removed faces as shells.
  virtual bool          AddRemovedFacesAsShells() const { return addRemovedFacesAsShells; }

  OBVIOUS_PRIVATE_COPY( ConvConvertorProperty3D )

}; // IConvertorProperty3D



#endif // __CONV_MODEL_PROPERTIES_H
