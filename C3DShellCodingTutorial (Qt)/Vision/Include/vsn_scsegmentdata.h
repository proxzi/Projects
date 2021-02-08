////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneSegmentData представляет данные сегмента сцены.
         \en SceneSegmentData class represents scene segment data. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SCSEGMENTDATA_H
#define __VSN_SCSEGMENTDATA_H


#include "vsn_renderobject.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class AbsGeometryRep;
class SceneSegmentRef;
class SceneSegment;
class SceneSegmentDataPrivate;

//------------------------------------------------------------------------------
/** \brief \ru Класс SceneSegmentData представляет данные сегмента сцены. 
           \en SceneSegmentData class represents scene segment data. \~
  \details \ru Класс SceneSegmentData может содержать представление геометрии, а также ссылку на ее.
               Класс SceneSegmentData может имеет контейнер SceneSegment в качестве дополнительной информации о ссылке на представление.
           \en SceneSegmentData class contains geometry representation and also reference to it. 
               SceneSegmentData class has SceneSegment container as additional information on representation reference.   

  \ingroup Vision_SceneGraph
*/
// ---
class VSN_CLASS SceneSegmentData
{
public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~ 
    \param[in] pRef - \ru Узел ссылки графа сцены.
                      \en Scene graph reference segment . \~
  */
  SceneSegmentData(SceneSegmentRef* pRef = nullptr);

  /** \brief \ru Cпециальный конструктор с представлением.
             \en Special constructor with representation.. \~ 
    \param[in] pRep - \ru Представление.
                      \en Representation. \~
  */
  SceneSegmentData(AbsGeometryRep* pRep);

  /** \brief \ru Конструктор копирования.
             \en Copy constructor. \~ 
    \param[in] other - \ru Данные сегмента графа сцены.
                       \en Scene graph segment data. \~
  */
  SceneSegmentData(const SceneSegmentData& other);

  /** \brief \ru Конструктор копирования.
             \en Copy constructor.. \~ 
    \param[in] pOther - \ru Указатель на данные сегмента.
                        \en Pointer to segment data. \~
  */
  SceneSegmentData( SceneSegmentData* pOther );

  /** \brief \ru Специальный конструктор с установкой имени.
             \en Special constructor with setting name. \~ 
    \param[in] name - \ru Имя.
                      \en Name. \~
  */
  SceneSegmentData( const String& name );

  /// \ru Деструктор. \en Destructor. 
  virtual ~SceneSegmentData();

public:
  /** \brief \ru Установить данным сегмента ссылку на геометрию.
             \en Sets for segment data reference to geometry. \~ 
    \param[in] pSegmentRef - \ru Узел ссылки графа сцены.
                             \en Scene graph reference segment. \~
  */
  void SetReference( SceneSegmentRef* pSegmentRef );

  /** \brief \ru Вернуть true, если этот сегмент имеет данные.
             \en True if segment has data. \~ 
    \return \ru True, если этот сегмент имеет данные.
            \en True if segment has data . \~
  */
  bool HasSegmentData() const;

  /// \ru Вернуть количество вставленых сегментов. \en Returns count of inserted segments. \~
  size_t GetSegmentCount() const;

  /// \ru Вернуть указатель на первый сегмент. \en Returns pointer to the first segment. \~
  SceneSegment* GetFirstSegmentData() const;

  /// \ru Вернуть относительную матрицу сегмента. \en Returns relative matrix of segment. \~
  const MbMatrix3D& GetRelativeMatrix() const;

  /// \ru Вернуть ссылку на эти данные. \en Returns reference to this data. \~
  SceneSegmentRef* GetDataReference() const;

  /// \ru Вернуть массив сегментов. \en Returns array of segments. \~
  std::list<SceneSegment*> GetSegmentData() const;

  /// \ru Вернуть имя вставки сегмента. \en Returns the name of segment insertion. \~
  const String& GetName() const;

  /** \brief \ru Установить имя вставки сегмента.
             \en Sets the name of segment insertion. \~ 
    \param[in] name - \ru Устанавливаемое имя.
                      \en Set name. \~
  */
  void SetName( const String& name );

  /// \ru Вернуть количество ссылок на эти данные. \en Returns the reference count to this data. \~
  int GetDataUseCount() const;

public:
  /** \brief \ru Добавить новый созданный сегмент.
             \en Adds created segment. \~ 
    \param[in] pSegment - \ru Добавляемый сегмент.
                          \en Added segment. \~
  */
  void SegmentCreated(SceneSegment* pSegment);

  /** \brief \ru Удалить из массива данный сегмент.
             \en Removes given segment from array. \~ 
    \param[in] pSegment - \ru Удаляемый сегмент.
                          \en Removed segment. \~
  */
  void SegmentDeleted(SceneSegment* pSegment);

  /** \brief \ru Переместить данные по заданной матрице.
             \en Replaces data by set matrix. \~ 
    \param[in] matrix - \ru Матрица перемещения.
                        \en Move matrix. \~
    \return \ru Переместить данные по матрице.
            \en Moves data by matrix. \~
  */
  SceneSegmentData* Move(const MbMatrix3D& matrix);

  /** \brief \ru Преобразовать данные по координатам.
             \en Transforms data by coordinates. \~ 
    \param[in] x - \ru Координата x.
                   \en X-coordinate. \~
    \param[in] y - \ru Координата y.
                   \en Y-coordinate. \~
    \param[in] z - \ru Координата z.
                   \en Z-coordinate. \~
    \return \ru Преобразованный сегмент данных.
            \en Transformed data segment. \~
  */
  SceneSegmentData* Translate( double x, double y, double z );

  /** \brief \ru Преобразовать данные по данному вектору.
             \en Transforms data by given vector. \~ 
    \param[in] vec - \ru Вектор преобразования.
                     \en Transformation vector. \~
    \return \ru Преобразованный сегмент данных.
            \en Transformed data segment. \~
  */
  SceneSegmentData* Translate( const MbVector3D& vec );

  /** \brief \ru Установить относительную матрицу.
             \en Sets relative matrix. \~ 
    \param[in] matrix - \ru Новая относительная матрица.
                        \en New relative matrix. \~
    \return \ru Сегмент данных с изменённой матрицей.
            \en Data segment with changed matrix. \~
  */
  SceneSegmentData* SetMatrix(const MbMatrix3D& matrix );

  /** \brief \ru Cбросить матрицу в единичную.
             \en Resets matrix to identity one. \~ 
    \return \ru Сегмент данных со сброшенной в единичную матрицей.
            \en Data segment with identity matrix. \~
  */
  SceneSegmentData* ResetToIdentityMatrix();

  /** \brief \ru Обновить абсолютную матрицу для всех подсегментов.
             \en Refreshes absolute matrix for all subsegments. \~ 
  */
  void UpdateDataAbsoluteMatrix();

private:
  VSN_DECLARE_PRIVATE(SceneSegmentData)
};

VSN_END_NAMESPACE

#endif /* __VSN_SCSEGMENTDATA_H */
