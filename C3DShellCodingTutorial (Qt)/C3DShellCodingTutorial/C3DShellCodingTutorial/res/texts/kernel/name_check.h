////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Работа с топологическими именами объекта.
         \en Treatment of object's topological names. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __NAME_CEHCK_H
#define __NAME_CEHCK_H


#include <templ_s_array.h>
#include <topology.h>
#include <topology_faceset.h>


class MATH_CLASS MbSNameMaker;


//------------------------------------------------------------------------------
/** \brief \ru Сравнение точек в пространстве.
           \en Points comparison in space. \~
  \details \ru Сравнение точек в пространстве с точностью Math::region: 
               по первой координате, по второй координате, по третьей координате.
           \en Points comparison with precision Math::region: 
               in the first coordinate, in the second coordinate, in the third coordinate. \~
  \param[in] p1 - \ru Первая точка.
                  \en An first point. \~
  \param[in] p2 - \ru Множество граней.
                  \en Вторая точка. \~
  \return \ru Возвращает: -1, если p1 < p2; +1, если p1 > p2; 0, если p1 == p2.
          \en Returns: -1 -if p1 < p2; +1 -if p1 > p2; 0 -if p1 == p2. \~
  \ingroup Names
*/
// ---
inline int PointCompare3D ( const MbCartPoint3D & p1, const MbCartPoint3D & p2 )
{
  if ( p2.x + Math::region < p1.x ) // по X
    return 1;
  else if ( p1.x + Math::region < p2.x )
    return -1;
  else {
    if ( p2.y + Math::region < p1.y ) // по Y
      return 1;
    else if ( p1.y + Math::region < p2.y )
      return -1;
    else {
      if ( p2.z + Math::region < p1.z ) // по Z
        return 1;
      else if ( p1.z + Math::region < p2.z )
        return -1;
    }
  }

  return 0;
}


//------------------------------------------------------------------------------
/** \brief \ru Установить имена элементам оболочки.
           \en Set names for elements of shell. \~
  \details \ru Установить имена элементам оболочки: граням, ребрам, вершинам.
           \en Set names for elements of shell: for faces, edges, vertices. \~
  \param[in] edges - \ru Множество ребер.
                     \en An array of edges. \~
  \param[in] faces - \ru Множество граней.
                     \en An array of faces. \~
  \param[in] nameMaker - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in] processVertexes - \ru Устанавливать ли имена вершинам.
                               \en Whether to set names to vertices. \~
  \ingroup Names
*/
// ---
MATH_FUNC (void) SetShellNames( RPArray<MbCurveEdge>  & edges,
                                const RPArray<MbFace> & faces,
                                const MbSNameMaker & nameMaker,
                                bool processVertexes );


//------------------------------------------------------------------------------
/** \brief \ru Установить имена элементам оболочки.
           \en Set names for elements of shell. \~
  \details \ru Установить имена граням оболочки.
           \en Set names for faces of shell. \~
  \param[in] faces - \ru Множество граней.
                     \en An array of faces. \~
  \param[in] nameMaker - \ru Именователь.
                         \en An object for naming the new objects. \~
  \param[in] processVertexes - \ru Устанавливать ли имена вершинам.
                               \en Whether to set names to vertices. \~
  \ingroup Names
*/
// ---
MATH_FUNC (void) SetFacesNames( const RPArray<MbFace> & faces,
                                const MbSNameMaker & nameMaker,
                                bool processVertexes );


//------------------------------------------------------------------------------
/** \brief \ru Установить имена элементам оболочки.
           \en Set names for elements of shell. \~
  \details \ru Установить имена элементам оболочки: граням, ребрам, вершинам.
           \en Set names for elements of shell: for faces, edges, vertices. \~
  \param[in] shell - \ru Оболочка.
                     \en A shell. \~
  \param[in] nameMaker - \ru Именователь.
                         \en An object for naming the new objects. \~
  \ingroup Names
*/
// ---
inline
void SetShellNames(       MbFaceShell & shell, 
                    const MbSNameMaker & nameMaker )
{
  RPArray<MbCurveEdge> edges( 0, 1 );
  RPArray<MbFace>      faces( 0, 1 );

  shell.GetEdges( edges ); // \ru Получение массива ребер \en Get an array of edges 
  shell.GetFaces( faces );

  ::SetShellNames( edges, faces, nameMaker, true );
}


//------------------------------------------------------------------------------
/** \brief \ru Имя со счётчиком совпадений.
           \en Name with hits counter. \~
  \details \ru Имя со счётчиком совпадений. \n
           \en Name with hits counter. \n \~
  \ingroup Names
*/
// ---
struct NameIntersectionInfo {
  const MbName * name;          ///< \ru Имя объектов. \en A name of objects. 
  size_t         intersections; ///< \ru Количество совпадений. \en The count of coincidences. 

  NameIntersectionInfo() : name( NULL ), intersections( 0 ) {}
};


//------------------------------------------------------------------------------
/** \brief \ru Проверить имена на совпадение.
           \en Check names for coincidence. \~
  \details \ru Проверить имена составляющих элементов оболочке на совпадение. \n
           \en Check names of shell's components for coincidence. \n \~
  \param[in] shells - \ru Множество проверяемых оболочек.
                      \en An array of checked shells. \~
  \param[out] infos - \ru Множество совпадающих имен со счетчиком совпадений.
                      \en Array of coincident names with hits counter. \~
  \return \ru Возвращает true, если совпадающих имен не найдено.
          \en Returns true if no coincident names found. \~
  \ingroup Names
*/
// ---
MATH_FUNC (bool) CheckShellNames( const RPArray<const MbFaceShell> & shells, SArray<NameIntersectionInfo> & infos );


//-----------------------------------------------------------------------------
/** \brief \ru Выбрать имя объединяемых ребер.
           \en Select name for united edges. \~
  \details \ru Выбрать наиболее подходящее имя при объединении двух ребер, \n
           новое имя будет установленно первому ребру. \n
           \en Select the most suitable name while uniting two edges, \n
           the new name will be set to the first edge. \n \~
  \param[in,out] edge1 - \ru Первое ребро.
                         \en The first edge. \~
  \param[in]     edge2 - \ru Второе ребро.
                         \en The second edge. \~
  \param[in]     version - \ru Версия исполнения.
                           \en The version. \~
  \ingroup Names
*/
//---
MATH_FUNC (void) CombineNames( MbCurveEdge & edge1, const MbCurveEdge & edge2, VERSION version );


#endif // __NAME_CEHCK_H
