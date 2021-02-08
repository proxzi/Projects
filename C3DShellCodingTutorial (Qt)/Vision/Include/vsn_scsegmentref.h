////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneSegmentRef представляет ссылку на представление геометрии.
         \en SceneSegmentRef class sets reference to geometry representation. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_SCSEGMENTREF_H
#define __VSN_SCSEGMENTREF_H

#include <set>
#include <list>

#include "vsn_string.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Material;
class AbsGeometryRep;
class GeometryRep;
class SceneSegment;
class SceneSegmentData;
class SceneSegmentRefPrivate;

//------------------------------------------------------------------------------
/** \brief \ru Класс SceneSegmentRef представляет ссылку на представление геометрии.
           \en SceneSegmentRef class sets reference to geometry representation. \~
  \details \ru Класс SceneSegmentRef необходим и выполняет функцию экономии памяти для одинакового представления геометрии.
           \en SceneSegmentRef class is required. It performs the function of memory saving for equal geometry representation. 

    \ingroup Vision_SceneGraph
*/
// ---
class VSN_CLASS SceneSegmentRef
{
public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~ 
    \param[in] name - \ru Имя.
                      \en Name. \~
  */
  SceneSegmentRef( const String& name = String() );

  /** \brief \ru Специальный конструктор с указателем на представление.
             \en Special constructor with pointer to representation. \~ 
    \param[in] pRep - \ru Представление.
                      \en Representation. \~
  */
  SceneSegmentRef( AbsGeometryRep* pRep);

  /// \ru Деструктор. \en Destructor. 
  virtual ~SceneSegmentRef();

public:
  /** \brief \ru Вернуть true, если в этой ссылке есть экземпляр данных.
             \en True if data instance exists in the reference. \~ 
    \return \ru True, если в этой ссылке есть экземпляр данных.
            \en True if data instance exists in the reference. \~
  */
  bool HasDataSegment() const;

  /** \brief \ru Вернуть указатель на первый сегмент данных.
             \en Returns pointer to the first data segment. \~ 
      \return \ru Указатель на первый сегмент данных.
              \en Pointer to the first data segment. \~
  */
  SceneSegmentData* GetHeadDataSegment() const;

  /// \ru Вернуть список указателей на сегменты сцены. \en Returns the list of pointers to scene segments. \~
  std::list<SceneSegmentData*> GetSegmentData() const;

  /// \ru Вернуть массив указателей на сегменты сцены этой ссылки. \en Returns the array of pointers to scene segments of given reference. \~
  std::set<SceneSegment*> GetSceneSegmentsSet() const;

  /// \ru Вернуть список указателей на сегменты сцены этой ссылки. \en Returns the list of pointers to scene segments of given reference. \~
  std::list<SceneSegment*> GetSceneSegmentsList() const;

  /** \brief \ru Вернуть true, если данная ссылка имеет представление.
             \en True if given reference has representation. \~ 
    \return \ru True, если данная ссылка имеет представление.
            \en True if given reference has representation. \~
  */
  bool IsHasRep() const;

  /// \ru Вернуть указатель на представление этой ссылки. \en Returns pointer to representation of given reference. \~
  AbsGeometryRep* GetRepresentation() const;

  /** \brief \ru Установить представление этой ссылки.
             \en Sets representation for the reference. \~ 
    \param[in] pRep - \ru Источник представления.
                      \en Representation source. \~
  */
  void SetRepresentation(GeometryRep* pRep);

  /// \ru Вернуть имя ссылки. \en Returns reference name. \~
  const String& GetName() const;

  /** \brief \ru Установить имя этой ссылки.
             \en Sets reference name. \~ 
    \param[in] name - \ru Имя.
                      \en Name. \~
  */
  void SetName(const String& name);

  /// \ru Вернуть количество граней. \en Returns face count. \~
  size_t GetFaceCount() const;

  /// \ru Вернуть количество вершин. \en Returns vertex count. \~
  size_t GetVertexCount() const;

  /// \ru Вернуть количество материалов. \en Returns material count. \~
  size_t GetMaterialCount() const;

  /// \ru Вернуть количество тел. \en Returns body count. \~
  size_t GetGeometryCount() const;

  /// \ru Вернуть массив материалов. \en Returns material array. \~
  std::set<Material*> GetMaterials() const;

  /// \ru Вернуть имя представления. \en Returns representation name. \~
  String GetNameRep() const;

  /** \brief \ru Установить имя представления.
             \en Sets representation name. \~ 
    \param[in] repName - \ru Имя представления.
                         \en Representation name. \~
  */
  void SetRepName( const String& repName );

  /** \brief \ru Вернуть true, если представление загружено.
             \en True if representation is loaded. \~ 
    \return \ru True, если представление загружено.
            \en True if representation is loaded. \~
  */
  bool IsLoadedRep() const;

  /** \brief \ru Вернуть true, если представление является пустым либо представления нет.
             \en True if no representation is found or representation is empty. \~ 
    \return \ru True, если представление является пустым либо представления нет.
            \en True if no representation is found or representation is empty. \~
  */
  bool IsEmptyRep() const;

  public:
  /** \brief \ru Добавить сегмент данных.
             \en Adds data segment. \~ 
    \param[in] pSegmentData - \ru Новый сегмент данных.
                              \en New data segment. \~
  */
  void AddSegmentData( SceneSegmentData* pSegmentData );

  /** \brief \ru Удалить из массива сегмент данных.
             \en Removes data segment from array. \~ 
    \param[in] pSegmentData - \ru Удаляемый сегмент данных.
                              \en Removable data segment. \~
  */
  void RemoveSegmentData( SceneSegmentData* pSegmentData );

  /** \brief \ru Добавить данные сцены во все подсегменты этой ссылки.
             \en Adds scene data to all subsegments of given reference. \~ 
    \details \ru Добавить данные сцены во все подсегменты этой ссылки. Вернуть массив сегментов, добавленных этой ссылкой.
             \en Adds scene data to all subsegments of given reference. Returns the array of segments added by the reference. \~
    \param[in] pSceneSegment - \ru Добавляемая сцена.
                               \en Added scene. \~
    \return \ru Массив сегментов, добавленных этой ссылкой.
            \en The array of segments added by the reference. \~
  */
//  std::list<SceneSegment*> AddChild( SceneSegment* pSceneSegment );

  /** \brief \ru Оператор копирования.
             \en Copying operator. \~ 
    \param[in] \ru Копируемый сегмент данных.
               \en Сopied data segment. \~
    \return \ru Ссылка на копию сегмента данных.
            \en Reference to the copy of data segment. \~
  */
//  SceneSegmentRef& operator = ( const SceneSegmentRef& );

private:
  VSN_DECLARE_PRIVATE(SceneSegmentRef)
};
VSN_END_NAMESPACE

#endif /* __VSN_SCSEGMENTREF_H */
