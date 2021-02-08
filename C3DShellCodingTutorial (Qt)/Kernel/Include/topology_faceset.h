////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Множество граней или оболочка.
         \en Shell or set of faces. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __TOPOLOGY_FACESET_H
#define __TOPOLOGY_FACESET_H

#include <templ_s_array.h>
#include <templ_sptr.h>
#include <mb_operation_result.h>
#include <mb_data.h>
#include <topology.h>
#include <op_binding_data.h>
#include <vector>
#include <set>


class  MATH_CLASS MbCube;
class  MATH_CLASS MbFunction;
struct MATH_CLASS MbEdgeFacesIndexes; 
class  MATH_CLASS MbShellHistory;
class  MATH_CLASS MbPntLoc;
class  MATH_CLASS MbFaceSetTemp;
struct MATH_CLASS MbEdgeFunction; 
struct MATH_CLASS MbCheckTopologyParams; 
class  MATH_CLASS MbFaceShell;
class  MATH_CLASS MbShellsDistanceData;

namespace c3d // namespace C3D
{
typedef SPtr<MbFaceShell>                       ShellSPtr;
typedef SPtr<const MbFaceShell>                 ConstShellSPtr;

typedef std::pair<size_t, MbFaceShell *>        IndexShell;
typedef std::pair<size_t, const MbFaceShell *>  IndexConstShell;

typedef std::vector<MbFaceShell *>              ShellsVector;
typedef std::vector<const MbFaceShell *>        ConstShellsVector;

typedef std::vector<ShellSPtr>                  ShellsSPtrVector;
typedef std::vector<ConstShellSPtr>             ConstShellsSPtrVector;

typedef std::set<MbFaceShell *>                 ShellsSet;
typedef ShellsSet::iterator                     ShellsSetIt;
typedef ShellsSet::const_iterator               ShellsSetConstIt;
typedef std::pair<ShellsSetConstIt, bool>       ShellsSetRet;

typedef std::set<const MbFaceShell *>           ConstShellsSet;
typedef ConstShellsSet::iterator                ConstShellsSetIt;
typedef ConstShellsSet::const_iterator          ConstShellsSetConstIt;
typedef std::pair<ConstShellsSetConstIt, bool>  ConstShellsSetRet;
}


template <class FacesVector, class EdgesVector>
void GetEdges( const FacesVector & faceSet, EdgesVector & edges );


//------------------------------------------------------------------------------
/** \brief \ru Множество граней или оболочка.
           \en Shell or set of faces. \~
  \details \ru Оболочка представляет собой составную поверхность, образованную конечным множеством граней MbFace, 
    стыкующихся друг с другом по рёбрам MbCurveEdge. \n
      В общем случае оболочка может быть многосвязной, то есть описывать несколько не связанных между собой поверхностей. \n
    Оболочка называется замкнутой, если она не имеет края, в противном случае оболочка называется незамкнутой. \n 
      Замкнутость оболочки указывает на возможность использования множества её внутренних точек в операциях над телами MbSolid.
    Формально множество граней не ограничено никакими условиями, 
    но реально грани множества удовлетворяют некоторым условиям. 
    Чтобы подчеркнуть эту особенность оболочки, вводится понятие "Однородная оболочка".
    Оболочки, удовлетворяющие нижеперечисленным требованиям, называются однородными. \n
    1. Оболочки являются конечными. \n
    2. Оболочки не пересекают сами себя. \n
    3. Оболочки являются двусторонними (ориентируемыми). \n
    4. В каждом ребре оболочки стыкуются не более двух граней. Две грани оболочки стыкуются так, 
       что внешняя сторона одной грани переходит во внешнюю сторону другой грани.\n
    5. При любом обходе любой вершины замкнутой оболочки по её поверхности, 
       мы обязательно посетим все примыкающие к данной вершине грани и пересечём все выходящие из неё рёбра.\n 
      Так как внешняя сторона грани переходит во внешнюю сторону соседней грани, 
    то однородная оболочка также имеет внешнюю и внутреннюю стороны. 
    Замкнутая однородная оболочка делит трёхмерное пространство на две части, одна из которых находится внутри оболочки. 
    Назовем замкнутую однородную оболочку внешней, если её внешняя сторона направлена вне ограничиваемой оболочкой части пространства.\n 
    Назовем замкнутую однородную оболочку внутренней, если её внешняя сторона направлена внутрь ограничиваемой оболочкой части пространства.
           \en A shell is a composite surface formed by finite set of faces MbFace, 
    connected together by edges MbCurveEdge. \n
      In general case a shell may be multiply connected, i.e. it may describe several pairwise not connected surfaces. \n
    A shell is called closed if it has not a boundary, otherwise a shell is called unclosed. \n 
      The closedness of a shell indicates the possibility of using of a set of its internal points in operations with solids MbSolid.
    Formally, a set of faces is not restricted by any conditions, 
    but actually faces of the set satisfy certain conditions. 
    In order to highlight this feature of a shell, the concept "manifold shell" is introduced.
    Shells which satisfy the below requirements are called manifold. \n
    1. Shells are finite. \n
    2. Shells do not intersect themselves. \n
    3. Shells are two-sided (oriented). \n
    4. At each edge of a shell not more than two faces are connected. Two faces of shell connected in such way, 
       that the external side of one face turns to the external side of another face.\n
    5. With any go-round of any vertex of closed shell on its surface, 
       one will visit all faces connected with this vertex of a face and intersect all outgoing edges.\n 
      Since the external side of a face turns to the external side of adjacent face, 
    a manifold shell also has the external and internal sides. 
    A closed manifold shell divides the three-dimensional space into two parts, one of which is located inside the shell. 
    Let closed manifold shell be called external shell, if its external side is directed out from a part of space bounding by the shell.\n 
    Let closed manifold shell be called an internal shell, if its external side is directed inside a part of space bounding by the shell. \~
  \ingroup Topology_Items
*/
// ---
class MATH_CLASS MbFaceShell : public MbTopItem, public MbSyncItem {
protected:
  RPArray<MbFace> faceSet; ///< \ru Множество граней. \en A set of faces. 
  bool            closed;  ///< \ru Признак замкнутости указывает на отсутствие края. \en An attribute of closedness indicates the absence of boundary. 
private:
  mutable MbFaceSetTemp * temporal; ///< \ru Объект сопровождения множества граней (для скорости) \en An object for maintenance of a set of faces (to improve speed) 

public :
  /// \ru Конструктор без параметров. \en Constructor without parameters. 
  MbFaceShell();
  /// \ru Конструктор по набору граней. \en Constructor by a set of faces. 
  template <class Faces>
  MbFaceShell( const Faces & initFaces );
  /// \ru Конструктор по грани. \en Constructor by face. 
  explicit MbFaceShell( const MbFace & face );
  /// \ru Конструктор по граням другой оболочки. \en Constructor by faces of other shell. 
  explicit MbFaceShell( const MbFaceShell & init );
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbFaceShell();

  /// \ru Функции оболочки. \en Functions of shell. 

  virtual MbeTopologyType  IsA() const; // \ru Тип элемента. \en A type of element. 

          /** \brief \ru Создать копию.
                     \en Create a copy. \~
            \details \ru Создать копию оболочки с копированием части данных и 
              перекладыванием из оригинала в копию остальной части данных.  \n
              Параметр history используется, если режим копирования cm_KeepHistory.
                     \en Create a copy of a shell with copying of a part of data and 
              moving another part of data from the original to the copy.  \n
              The parameter 'history' is used if the copying mode is cm_KeepHistory. \~
            \param[in] sameShell - \ru Способ передачи данных при копировании оболочки MbeCopyMode: \n
                       sameShell == cm_Same - в качестве копии возвращяетчя исходная оболока (оболочка не копируется, но выставляются правильно указатели в рёбрах на грани справа и грани слева); \n
                       sameShell == cm_KeepHistory - копируется часть данных (исходная оболочка и её копия имеют общие базовые поверхности и вершины) и заполняются множества граней объекта history; \n
                       sameShell == cm_KeepSurface - копируется часть данных (исходная оболочка и её копия имеют общие базовые поверхности); \n
                       sameShell == cm_Copy - обычное копирование (исходная оболочка и её копия не имеет общих данных). \n
                                   \en A way of data transferring when copying of a shell MbeCopyMode: \n
                       sameShell == cm_Same - an initial shell is returned as the copy (a shell is not copied but the pointers of edges to the faces are correctly set); \n
                       sameShell == cm_KeepHistory - a part of data is copied (the initial shell and its copy have the common basis surfaces and vertices) and the sets of faces of the object 'history' are filled; \n
                       sameShell == cm_KeepSurface - a part of data is copied (the initial shell and its copy have the common basis surfaces); \n
                       sameShell == cm_Copy - an ordinary copying (the initial shell and its copy have no the common data). \n \~
            \param[in] history   - \ru История копий граней используется после операции для замены неизменённых копий граней их оригиналами.
                                   \en A history of faces copies is used after the operation for the replacement of unchanged copies by their originals. \~
            \return \ru Копия объекта или оригинал(в случае режима копирования cm_Same).
                    \en Copy of an object or original (in a case of the mode cm_Same). \~
          */
          MbFaceShell * Copy( MbeCopyMode sameShell, MbShellHistory * history = NULL ); 

          /** \brief \ru Создать копию.
                     \en Create a copy. \~
            \details \ru Создать копию оболочки с регистратором.
                     \en Create a copy of a shell with registrator. \~ 
            \return \ru Копия объекта.
                    \en Copy of the object. \~
          */
          MbFaceShell * Duplicate( MbRegDuplicate * iReg = NULL ) const;

          /// \ru Замкнутая ли оболочка? \en Is shell closed? 
          bool        IsClosed() const    { return closed; }
          /// \ru Установить (не)замкнутость оболочки. \en Set shell (un-) closedness. 
          void        SetClosed( bool c ) { closed = c;    }
          /// \ru Выдать количество граней. \en Get the number of faces. 
          size_t      GetFacesCount()    const { return faceSet.size();    } 
          /// \ru Выдать максимальный индекс грани. \en Get the maximum index of a face. 
          ptrdiff_t   GetFacesMaxIndex() const { return ((ptrdiff_t)faceSet.size() - 1); } 
          /// \ru Добавить грань в оболочку. \en Add a face into a shell. 
          void        AddFace( const MbFace & ); 
          /// \ru Добавить грани в оболочку. \en Add faces into a shell. 
          template <class FacesVector>
          void        AddFaces( const FacesVector & newFaces, bool justAdd )
          {
            if ( !newFaces.empty() ) {
              bool delTemporal = false;
              for ( size_t i = 0, cnt = newFaces.size(); i < cnt; ++i ) {
                const MbFace * newFace = newFaces[i];
                if ( newFace == NULL )
                  continue;
                if ( justAdd || ( std::find( faceSet.begin(), faceSet.end(), newFace ) == faceSet.end() ) ) {
                  faceSet.push_back( const_cast<MbFace *>(newFace) );
                  C3D_ASSERT( !newFace->ToDelete() );
                  ::AddRefItem( newFace );
                  delTemporal = true;
                }
              }
              if ( delTemporal )
                RemoveTemporal();
            }
          }
          /// \ru Вставить грань перед гранью с заданным индексом. \en Insert a face before the face with the given index. 
          void        InsertFace( size_t index, const MbFace & );
          /// \ru Заменить грань с заданным индексом. \en Replace a face with the given index. 
          void        ChangeFace( size_t index, const MbFace & );
          /// \ru Удалить грань с заданным индексом. \en Delete a face at the given index. 
          void        DeleteFace( size_t index ); 
          /// \ru Удалить грань. \en Delete a face. 
          void        DeleteFace( const MbFace * );
          /// \ru Отсоединить грань от оболочки с заданным индексом. \en Detach a face from a shell with the given index. 
          MbFace    * DetachFace( size_t index ); 
          /// \ru Отсоединить грань. \en Detach face. 
          void        DetachFace( const MbFace * );
          /// \ru Удалить все грани оболочки. \en Delete all faces of shell. 
          void        DeleteFaces();
          /// \ru Отсоединить все грани оболочки. \en Detach all faces from shell. 
          void        DetachFaces();
          /// \ru Поменять местами грани оболочки. \en Swap shell faces. 
          void        ExchangeFaces( size_t i1, size_t i2 );
          /// \ru Установить правильную (текущую) информацию в ребрах о соединяемых ими гранях и параметры поверхностей по данным циклов граней (setBounds = true). \en Set the correct (the current) information in edges about the connected by them faces and parameters of surfaces by loops of faces (setBounds = true). 
          void        MakeRight( bool setBounds = false ); 
          /// \ru Верно ли установлены указатели в ребрах на соединяемые ими грани. \en Are the pointers in edges to the connected by them faces correctly set? 
          bool        IsRight() const; 
          /// \ru Обнулить указатели в ребрах на отсутствующую в оболочке грань. \en Set to null in edges the pointers to a face which is absent face 
          void        SetNullToFace( const MbFace * delFace );

          /** \brief \ru Преобразовать согласно матрице.
                     \en Transform according to the matrix. \~
            \details \ru Преобразование оболочки согласно матрице. 
              В оболочке одни и те же геометрические объекты, например поверхности, используются как в гранях, так и в рёбрах.
              Для преобразования каждого геометрического объекта только один раз используется регистратор.
                     \en The transformation of a shell according to a matrix. 
              In a shell the same geometric objects, for example, surfaces, are used in both faces and in edges.
              For the transformation of each geometric object only once a registrator is used. \~
            \param[in] matr - \ru Матрица преобразования.
                              \en A transformation matrix. \~
            \param[in] iReg - \ru Регистратор объектов.
                              \en Registrator of objects: \~
          */
          void        Transform( const MbMatrix3D & matr, MbRegTransform * iReg = NULL );

          /** \brief \ru Сдвинуть вдоль вектора.
                     \en Move along a vector. \~
            \details \ru Сдвиг оболочки вдоль вектора. 
              В оболочке одни и те же геометрические объекты, например поверхности, используются как в гранях, так и в рёбрах.
              Для преобразования каждого геометрического объекта только один раз используется регистратор.
                     \en Move of a shell along a vector. 
              In a shell the same geometric objects, for example, faces, are used in both faces and in edges.
              For the transformation of each geometric object only once a registrator is used. \~
            \param[in] to   - \ru Вектор сдвига.
                              \en Translation vector. \~
            \param[in] iReg - \ru Регистратор.
                              \en Registrator. \~
          */
          void        Move( const MbVector3D & to, MbRegTransform * iReg = NULL );

          /** \brief \ru Повернуть вокруг оси.
                     \en Rotate around an axis. \~
            \details \ru Поворот оболочки вокруг оси. 
              В оболочке одни и те же геометрические объекты, например поверхности, используются как в гранях, так и в рёбрах.
              Для преобразования каждого геометрического объекта только один раз используется регистратор.
                     \en The rotation of a shell around an axis. 
              In a shell the same geometric objects, for example, faces, are used in both faces and in edges.
              For the transformation of each geometric object only once a registrator is used. \~
            \param[in] axis  - \ru Ось поворота.
                               \en The rotation axis. \~
            \param[in] angle - \ru Угол поворота.
                               \en The rotation angle. \~
            \param[in] iReg  - \ru Регистратор.
                               \en Registrator. \~
          */
          void        Rotate( const MbAxis3D & axis, double angle, MbRegTransform * iReg = NULL ); 
          /// \ru Рассчитать расстояние до точки. \en Calculate the distance to a point. 
          double      DistanceToPoint( const MbCartPoint3D & to ) const; 
          /// \ru Вывернуть оболочку наизнанку - переориентировать все грани. \en Revert the shell - reorientation of the whole set of faces. 
          void        Reverse();
          /// \ru Являются ли объекты равными. \en Determine whether objects are equal. 
          bool        IsSame( const MbFaceShell & faces, double accuracy ) const; 
          /// \ru Установить метки всем объектам, имеющим таковые. \en Set labels for all objects which have them. 
          void        SetLabelThrough( MbeLabelState, void * = NULL ) const;
          /// \ru Установить метки всем объектам, имеющим таковые. \en Set labels for all objects which have them. 
          void        SetLabelThrough( MbeLabelState, void *, bool ) const;
          /// \ru Удалить частные метки всем объектам, имеющим таковые. \en Remove private labels for all objects which have them.
          void        RemovePrivateLabelThrough( void * ) const;
          /// \ru Установить флаги изменённости объектов. \en Set flags that objects have been changed. 
          void        SetOwnChangedThrough( MbeChangedType n );
          /// \ru Установить флаги в начальное состояние. \en Set flags to initial state. 
          void        ResetFlags( void * = NULL );
          /// \ru Забрать в оболочку множество граней из оболочки faces. \en Move a set of faces to the shell from another shell.  
          bool        UnionWith( MbFaceShell & faces, c3d::FacesSet * sharedSet = NULL ); 
          /// \ru Установить заданную метку всем вершинам оболочки. \en Set the given label for all vertices of the shell. 
          size_t      SetVerticesLabel( MbeLabelState, void * = NULL) const;
          /// \ru Установить заданную метку всем рёбрам оболочки. \en Set the given label for all edges of the shell. 
          size_t      SetEdgesLabel   ( MbeLabelState, void * = NULL) const;
          /// \ru Установить заданную метку всем граням оболочки. \en Set the given label for all faces of the shell. 
          void        SetFacesLabel   ( MbeLabelState, void * = NULL) const;

          /// \ru Выдать множество вершин оболочки. \en Get a set of vertices of the shell. 
          template <class VerticesVector>
          void        GetVertices( VerticesVector & ) const;
          /// \ru Выдать множество ребер  оболочки. \en Get a set of edges of the shell. 
          template <class EdgesVector>
          void        GetEdges( EdgesVector & edges ) const
          {
            if ( edges.size() < 1 )
              ::GetEdges< RPArray<MbFace>, EdgesVector >( faceSet, edges );
            else {
              size_t count = faceSet.size();
              edges.reserve( edges.size() + count * 2 );
              for ( size_t i = 0; i < count; i++ )
                faceSet[i]->GetEdges<EdgesVector>( edges );
            }
          }
          /// \ru Выдать множество граней оболочки. \en Get a set of faces of the shell. 
          template <class FacesVector>
          void        GetFaces( FacesVector & faces ) const
          {
            faces.reserve( faces.size() + faceSet.size() );
            SPtr<MbFace> face;
            for ( size_t k = 0, kcnt = faceSet.size(); k < kcnt; ++k ) {
              face = const_cast<MbFace *>( faceSet[k] );
              faces.push_back( face );
              ::DetachItem( face );
            }
          }
          /// \ru Выдать множество граней оболочки. \en Get a set of faces of the shell. 
          template <class FacesSet>
          void        GetFacesSet( FacesSet & faces ) const
          {
            for ( size_t k = 0, kcnt = faceSet.size(); k < kcnt; ++k ) {
              if ( faceSet[k] != NULL )
                faces.insert( faceSet[k] );
            }
          }
          /// \ru Выдать множество вершин и множество ребер оболочки. \en Get a set of vertices and a set of edges of the shell. 
          template <class VerticesVector, class EdgesVector>
          void        GetItems( VerticesVector & vertices, EdgesVector & edges ) const;
          /// \ru Выдать множество вершин, множество ребер и множество граней оболочки. \en Get a set of vertices, a set of edges and a set of faces of the shell. 
          void        GetItems( RPArray<MbTopologyItem> & list ) const;

          /// \ru Выдать вершину по индексу. \en Get a vertex by an index. 
          MbVertex *  GetVertex ( size_t index ) const; 
          /// \ru Выдать ребро по индексу. \en Get an edge by an index. 
          MbCurveEdge * GetEdge ( size_t index ) const; 
          /// \ru Выдать грань по индексу. \en Get a face by an index. 
          MbFace *    GetFace   ( size_t index ) const; 
          /// \ru Выдать грань по индексу без проверки корректности индекса. \en Get a face by an index without a check of index correctness. 
          MbFace *   _GetFace   ( size_t index ) const { return faceSet[index]; } 
          /// \ru Выдать поверхность грани по индексу. \en Give a surface of a face by an index. 
   const  MbSurface * GetSurface( size_t index ) const; 
          /// \ru Выдать индекс вершины. \en Get an index of a vertex. 
          size_t      GetVertexIndex( const MbVertex & vertex ) const; 
          /// \ru Выдать индекс ребра. \en Get an index of an edge. 
          size_t      GetEdgeIndex( const MbCurveEdge & edge ) const;
          /// \ru Выдать индекс грани. \en Get an index of a face. 
          size_t      GetFaceIndex( const MbFace & face ) const { return faceSet.FindIt( &face ); }
          /// \ru Найти индекс грани в оболочке. \en Find an index of a face in the shell. 
          size_t      Find( const MbFace * face ) const { return faceSet.FindIt( face ); }
          /// \ru Определить количество связных поверхностей, описываемых оболочкой. \en Define the number of connected faces describing by the shell. 
          size_t      GetShellCount() const; 

          /** \brief \ru Вычислить ближайшее расстояние до оболочки.
                     \en Calculate the nearest distance to a shell. \~
            \details \ru Вычислить ближайшее расстояние до оболочки с заданным допуском с той же системой координат. В случае пересечения или касания оболочек возвращается нулевая дистанция.
                     \en Calculate the nearest distance to a shell with a specified tolerance with the same coordinate system. In case of intersection or tangent of the shells returns to zero distance.\~
            \note    \ru При многократном использовании оболочки следует создать объекты сопровождения оболочки и её граней.
                     \en When multiply use shell, you should create objects for maintenance this shell and its faces. \~
            \param[in] shell - \ru Оболочка.
                               \en Shell. \~
            \param[in] lowerLimitDistance - \ru Минимально допустимое расстояние.
                                            \en Minimum allowed distance. \~
            \param[in] tillFirstLowerLimit - \ru Остановить поиск после первого найденного расстояния меньшего либо равного минимально допустимому.
                                             \en Stop the search after the first found distance is less or equal than to the minimum allowable. \~
            \param[in] epsilon - \ru Погрешность вычисления расстояния между поверхностями граней оболочек.
                                 \en Accuracy of distanse between shell face surfaces. \~
            \param[out] shellsDistanceData - \ru Данные ближайщего расстояния между оболочками.
                                            \en The data of nearest distance beetwen shells. \~

            \return \ru Удалось ли определить минимальное расстояние между оболочками.
                    \en Whether the minimum distance between shells was successfully defined. \~
          */
          bool        DistanceToShell( const MbFaceShell & shell, 
                                       double lowerLimitDistance, bool tillFirstLowerLimit, 
                                       double epsilon, 
                                       std::vector<MbShellsDistanceData> & shellsDistanceData ) const; 

          /** \brief \ru Определить расстояния от точки до оболочки.
                     \en Define the distance from a point to the shell. \~
            \details \ru Определить расстояния от точки до оболочки и положение точки: 
              снаружи оболочки, на оболочке, внутри оболочки.
                     \en Define the distance from a point to the shell and location of a point: 
              outside the shell, on the shell, inside the shell. \~
            \param[in]  pnt - \ru Точка.
                              \en Point. \~
            \param[in]  accuracy - \ru Заданная точность определения положения.
                                   \en A given tolerance for the location definition. \~
            \param[out] finFaceData - \ru Информация об окружении проекции точки pnt на ближайшую грань оболочки.
                                      \en An information about surroundings of the point 'pnt' projection to the nearest face of the shell. \~
            \param[out] rShell - \ru Результат определения: снаружи оболочки (-1), на оболочке (0), внутри оболочки (+1).
                                 \en The result of definition: outside the shell (-1), on the shell (0), inside the shell (+1). \~
            \return \ru Удалось ли определить расстояния от точки до оболочки.
                    \en Whether the distance from a point to the shell was successfully defined.. \~
          */
          bool        DistanceToBound( const MbCartPoint3D & pnt, double accuracy,
                                       MbPntLoc & finFaceData, 
                                       MbeItemLocation & rShell ) const;

          /** \brief \ru Определить положение точки относительно оболочки.
                     \en Define the point location relative to the shell. \~
            \details \ru Определить положение точки относительно оболочки: снаружи оболочки, на оболочке, внутри оболочки.
                     \en Define the point location relative to the shell: outside the shell, on the shell, inside the shell. \~
            \param[in]  pnt - \ru Точка.
                              \en Point. \~
            \param[in]  accuracy    - \ru Заданная точность определения положения.
                                      \en A given tolerance for the location definition. \~
            \param[out] shellPoint  - \ru Ближайшая к точке pnt точка оболочки.
                                      \en A point on the shell which is the nearest to the point 'pnt'. \~
            \param[out] shellNormal - \ru Нормаль в ближайшей к точке pnt точке оболочки.
                                      \en A normal to the nearest to the 'pnt' point on the shell. \~
            \param[out] rShell - \ru Результат определения: снаружи оболочки (-1), на оболочке (0), внутри оболочки (+1).
                                 \en The result of definition: outside the shell (-1), on the shell (0), inside the shell (+1). \~
            \return \ru Удалось ли определить положение точки относительно оболочки.
                    \en Whether the point location relative to the shell was successfully defined. \~
          */
          bool        PointClassification( const MbCartPoint3D & pnt, double accuracy,
                                           MbCartPoint3D & shellPoint, MbVector3D & shellNormal, 
                                           MbeItemLocation & rShell ) const; 

          /** \brief \ru Определить положение точки относительно оболочки.
                     \en Define the point location relative to the shell. \~
            \details \ru Определить положение точки относительно оболочки: снаружи оболочки, на оболочке, внутри оболочки.
                     \en Define the point location relative to the shell: outside the shell, on the shell, inside the shell. \~
            \param[in]  pnt - \ru Точка.
                              \en Point. \~
            \param[in]  accuracy    - \ru Заданная точность определения положения.
                                      \en A given tolerance for the location definition. \~
            \param[out] shellPoint  - \ru Ближайшая к точке pnt точка оболочки.
                                      \en A point on the shell which is the nearest to the point 'pnt'. \~
            \param[out] shellNormal - \ru Нормаль в ближайшей к точке pnt точке оболочки.
                                      \en A normal to the nearest to the 'pnt' point on the shell. \~
            \param[out] rShell - \ru Положение точки относительно оболочки.
                                 \en The point location relative to the shell. \~
            \return \ru Удалось ли определить положение точки относительно оболочки.
                    \en Whether the point location relative to the shell was successfully defined. \~
          */
          bool        PointClassification( const MbCartPoint3D & pnt, double accuracy,
                                           MbCartPoint3D & shellPoint, MbVector3D & shellNormal, 
                                           MbPntLoc & rShell ) const; 

          /** \brief \ru Вычислить точку оболочки.
                     \en Calculate a point of the shell. \~
            \details \ru Вычислить точку оболочки для заданной грани по заданным параметрам её поверхности.
                     \en Calculate a point for the given face by the given parameters of its surface. \~
            \param[in]  n - \ru Индекс грани оболочки.
                            \en An index of a face of the shell. \~
            \param[in]  u - \ru Первый параметр поверхности грани.
                            \en The first parameter of the face surface. \~
            \param[in]  v - \ru Второй параметр поверхности грани.
                            \en The second parameter of the face surface. \~
            \param[out] p - \ru Вычисленная точка оболочки.
                            \en Calculated point of the shell. \~
          */
          void        PointOn( size_t n, double & u, double & v, MbCartPoint3D & p ) const; 

          /** \brief \ru Вычислить нормаль оболочки.
                     \en Calculate a normal of the shell. \~
            \details \ru Вычислить нормаль оболочки для заданной грани по заданным параметрам её поверхности. \n
                     \en Calculate a normal of the shell for the given face by the given parameters of its surface. \n \~
            \param[in]  n - \ru Индекс грани оболочки.
                            \en An index of a face of the shell. \~
            \param[in]  u - \ru Первый параметр поверхности грани.
                            \en The first parameter of the face surface. \~
            \param[in]  v - \ru Второй параметр поверхности грани.
                            \en The second parameter of the face surface. \~
            \param[out] p - \ru Вычисленная нормаль оболочки.
                            \en Calculated normal of the shell. \~
          */
          void        Normal ( size_t n, double & u, double & v, MbVector3D & p ) const; 

          /** \brief \ru Найти все проекции точки на оболочку.
                     \en Find the point projection to the shell. \~
            \details \ru Найти все проекции точки на все грани оболочки. \n
                     \en Find all point projections to all faces of the shell. \n \~
            \param[in] p - \ru Проецируемая точка.
                           \en A point to project. \~
            \param[out] nums - \ru Массив номера граней в оболочки, синхронный с массивом параметров проекций.
                               \en An array of faces numbers in the shell, synchronized with the array of projections parameters \~
            \param[out] uv - \ru Массив параметров проекций.
                             \en An array of projections parameters. \~
          */
          void        NearPointProjection( const MbCartPoint3D & p, SArray<size_t> & nums, SArray<MbCartPoint> & uv ) const;

          /** \brief \ru Найти ближайшую проекцию точки на оболочку.
                     \en Find nearest point projection to the shell. \~
            \details \ru Найти номер грани и параметры её поверхности для ближайшей проекции точки на оболочку. \n
                     \en Find face index and surface parameters for the nearest point projection to the shell. \n \~
            \param[in] p - \ru Проецируемая точка.
                           \en A point to project. \~
            \param[out] faceIndex - \ru Номер грани в оболочке для ближайшей проекции.
                               \en The index of nearest face of the shell. \~
            \param[out] u - \ru Первый параметр поверхности грани проекций для ближайшей проекции точки на оболочку.
                            \en The first parameter of the face surface for the nearest projection. \~
            \param[out] v - \ru Второй параметр поверхности грани проекций для ближайшей проекции точки на оболочку.
                            \en The second parameter of the face surface for the nearest projection. \~
            \return \ru Удалось ли определить положение точки.
                    \en Whether the point projection was successfully defined. \~
          */
          bool        NearPointProjection( const MbCartPoint3D & p, size_t & faceIndex, double & u, double & v ) const;

          /** \brief \ru Найти все проекции точки на оболочку вдоль вектора в любом из двух направлений.
                     \en Find the point projection to the shell along a vector in either of two directions. \~
            \details \ru Найти все проекции точки на все грани оболочки вдоль вектора в любом из двух направлений. \n
                     \en Find all point projections to all faces of the shell along a vector in either of two directions. \n \~
            \param[in] p - \ru Проецируемая точка.
                           \en A point to project. \~
            \param[in] vect - \ru Вектор направления проецирования.
                              \en The vector of direction. \~
            \param[out] nums - \ru Массив номера граней в оболочки, синхронный с массивом параметров проекций.
                               \en An array of faces numbers in the shell, synchronized with the array of projections parameters \~
            \param[out] uv - \ru Массив параметров проекций.
                             \en An array of projections parameters. \~
          */
          void        DirectPointProjection( const MbCartPoint3D & p, const MbVector3D & vect, SArray<size_t> & nums, SArray<MbCartPoint> & uv ) const;

          /** \brief \ru Найти ближайшую проекцию точки на оболочку в направлении вектора.
                     \en Find nearest point projection to the shell in the direction of the vector. \~
            \details \ru Найти номер грани и параметры её поверхности для ближайшей проекции точки на оболочку в направлении вектора. \n
                     \en Find face index and surface parameters for the nearest point projection to the shell in the direction of the vector. \n \~
            \param[in] p - \ru Проецируемая точка.
                           \en A point to project. \~
            \param[out] faceIndex - \ru Номер грани в оболочке для ближайшей проекции.
                               \en The index of nearest face of the shell. \~
            \param[in] vect - \ru Вектор направления проецирования.
                              \en The vector of direction. \~
            \param[out] u - \ru Первый параметр поверхности грани проекций для ближайшей проекции точки на оболочку в направлении вектора.
                            \en The first parameter of the face surface for the nearest projection in the direction of the vector. \~
            \param[out] v - \ru Второй параметр поверхности грани проекций для ближайшей проекции точки на оболочку в направлении вектора.
                            \en The second parameter of the face surface for the nearest projection in the direction of the vector. \~
            \param[in] onlyPositiveDirection - \ru Искать только в положительном направлении вектора vect от точки p.
                                               \en Find in the positive direction of vector vect from point p \~
            \return \ru Удалось ли определить положение точки.
                    \en Whether the point projection was successfully defined. \~
          */
          bool        NearDirectPointProjection( const MbCartPoint3D & p, size_t & faceIndex, const MbVector3D & vect, double & u, double & v,
                                                 bool onlyPositiveDirection = false ) const;

          /** \brief \ru Существует ли проекция в направлении вектора?
                     \en Does the projection in direction of the vector exist? \~
            \details \ru Определить, существует ли хотя бы одна проекция точки на оболочку в направлении вектора.
                     \en Define whether at least one projection of a point to the shell in direction of the vector exists. \~
            \param[in] p    - \ru Проецируемая точка.
                              \en A point to project. \~
            \param[in] vect - \ru Вектор, задающий направление проецирования.
                              \en A vector which defines the direction of projection. \~
            \return \ru true, если нашлась хотя бы одна проекция.
                    \en True if at least one projection is found. \~
          */
          bool        DirectPointProjection( const MbCartPoint3D & p, const MbVector3D & vect ) const;

          /** \brief \ru Пересечение оболочки и кривой.
                     \en Intersection between a shell and a curve. \~
            \details \ru Найти пересечения кривой с гранями оболочки.
                     \en Find intersections between a curve and faces of a shell. \~
            \param[in] curve - \ru Кривая.
                               \en Curve. \~
            \param[out] nn -\ru Номера граней оболочки, у которых есть пересечения с кривой.
                            \en Indices of shell faces that have intersections with the curve. \~
            \param[out] uv -\ru Параметрические точки пересечений на поверхностях граней оболочки.
                            \en Parametric points of intersections on faces' surfaces. \~
            \param[out] tt -\ru Параметры пересечений на кривой.
                            \en Intersection parameters on the curve. \~
          */
          void        CurveIntersection( const MbCurve3D & curve, SArray<size_t> & nn, 
                                         SArray<MbCartPoint> & uv, SArray<double> & tt ) const;
          /// \ru Добавить свой габарит в габаритный куб. \en Add  your own bounding box into bounding cube. 
          void        AddYourGabaritTo( MbCube & ) const;
          /// \ru Рассчитать габарит оболочки. \en Calculate bounding box of the shell. 
          void        CalculateGabarit( MbCube & ) const;
          /// \ru Рассчитать габарит в локальной системы координат, заданной матрицей matrToLocal преобразования в неё \en Calculate bounding box in the local coordinate system which is given by the matrix 'matrToLocal ' of transformation to it.  
          void        CalculateLocalGabarit( const MbMatrix3D    & matrToLocal, MbCube & cube ) const;
          /// \ru Рассчитать габарит в локальной системы координат localPlace. \en Calculate bounding box in the local coordinate system 'localPlace'. 
          void        CalculateLocalGabarit( const MbPlacement3D & localPlace,  MbCube & cube ) const;

          /** \brief \ru Построить полигональную копию оболочки.
                     \en Construct a polygonal copy of the shell. \~
            \details \ru Построить полигональную копию оболочки заполнить ею полигональный объект (сетку) mesh.
                     \en Construct a polygonal copy of a shell and fill a polygonal object (a mesh) by it. \~
            \note    \ru В многопоточном режиме m_Items выполняется параллельно. \en In multithreaded mode m_Items runs in parallel. \~
            \param[in] stepData - \ru Данные для вычисления шага при триангуляции.
                                  \en Data for step calculation during triangulation. \~
            \param[in] note     - \ru Способ построения полигонального объекта.
                                  \en Way for polygonal object constructing. \~
            \param[out] mesh - \ru Заполняемый полигональный объект.
                               \en A polygonal object that being filled. \~ 
          */
          void        CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const;

          /// \ru Выдать свойства объекта. \en Get properties of the object. 
          void        GetProperties( MbProperties & ); 
          /// \ru Установить свойства объекта. \en Set properties of the object. 
          void        SetProperties( const MbProperties & ); 

          /// \ru Установить главное имя и вставить старое в индекс копирования. \en Set the main name and insert an old name to the copy index. 
          void        SetMainName       ( SimpleName mainName, bool addOldMainName );
          /// \ru Установить главное имя и модифицировать имена граней, рёбер и вершин для оболочки-копии для предотвращения совпадения имен нескольких копий. \en Set the main name and modify names of faces, edges and vertices for the shell-copy in order to prevent coincidence of several copies names. 
          void        MakeNewNames      ( SimpleName mainName, SimpleName modifier );
          /// \ru Установить главное имя и модифицировать имена граней для оболочки-копии для предотвращения совпадения имен нескольких копий. \en Set the main name and modify names of faces for the shell-copy in order to prevent coincidence of several copies names. 
          void        MakeNewNames      ( const MbSNameMaker &, SimpleName modifier );
          /// \ru Проименовать грани, рёбра и вершины оболочки. \en Rename faces, edges and vertices of the shell. 
          void        SetShellNames     ( const MbSNameMaker & names );
          /// \ru Заменить в имени метку копирования на index. \en Replace in a name a copying label by 'index'. 
          void        SetNamesCopyIndex ( SimpleName index );
          /// \ru Проименовать грани оболочки именами оболочки s. \en Name shell faces by names of the shell 's'. 
          void        SetShellNames     ( const MbFaceShell * s );
          /// \ru Очистить все имена в оболочке. \en Clear all shell names. 
          void        ClearShellNames   ();
          /// \ru Очистить имена ребер в оболочке. \en Clear all shell edges names. 
          void        ClearEdgesNames   ( bool clearVerticesNames = true );

          /** \brief \ru Проверка оболочки: вершин (удаление совпадающих и лишних), ребер (со слиянием).
                     \en Validation of the shell: vertices (deletion of coincident and extra), edges (with merge). \~
            \details \ru Проверка оболочки: вершин (удаление совпадающих и лишних), ребер (со слиянием).
                     \en Validation of the shell: vertices (deletion of coincident and extra), edges (with merge). \~
            \param[in] checkParams - \ru Параметры функции.
                                     \en Function parameters. \~
          */
          MbResultType CheckTopology( MbCheckTopologyParams & checkParams ); 

          /// \ru Определение замкнутости оболочки с модификацией флага. \en Check shell closedness with flag modification. 
          void        CheckClosed( bool checkChangedOnly = false );
          /// \ru Найти граничные рёбра и сделать граничными их кривые. \en Find the boundary edges, make their curve boundary. 
          bool        MakeBoundaryCurve(); 
          /// \ru Получить краевые ребра оболочки. \en Get boundary edges of the shell. 
          bool        GetBoundaryEdges( RPArray<const MbCurveEdge> & ) const;
          /// \ru Получить краевые ребра оболочки. \en Get boundary edges of the shell. 
          bool        GetBoundaryEdges( c3d::ConstEdgesVector & ) const;

          /// \ru Для множества ребер найти номера ребер и номера ее граней. \en For a set of edges find their indices and indices of their faces. 
          bool        FindFacesIndexByEdges( const RPArray<MbCurveEdge> & init, SArray<MbEdgeFacesIndexes> & indexes, bool any = false ) const;
          /// \ru Для множества структур (ребер и функций изменения радиусов) найти номера ребер и номера ее граней. \en For a set of structures (edges and functions of radii changing) find indices of edges and their faces. 
          bool        FindFacesIndexByEdges( const SArray<MbEdgeFunction> & init, 
                                             RPArray<MbFunction> & functions, SArray<MbEdgeFacesIndexes> & indexes ) const;
          /// \ru Для множества номеров ребер и номеров ее граней найти ребра. \en For a set of edge indices and indices of their faces find edges. 
          bool        FindEdgesByFacesIndex( const SArray<MbEdgeFacesIndexes> & indexes, RPArray<MbFunction> * functions, 
                                             RPArray<MbCurveEdge> & initCurves, RPArray<MbFunction> & initFunctions ) const; 
          /// \ru Найти номера граней по ребру. \en Find faces indices by the edge. 
          bool        FindFacesIndexByEdge( const MbCurveEdge & edge, size_t & ind1, size_t & ind2, bool any = false ) const;
          /// \ru Для множества граней найти множество их номеров. \en For a set of faces find a set of their indices. 
          bool        FindFacesIndexByFaces( const RPArray<MbFace> & init, SArray<size_t> & ind0 ) const;
          /// \ru Для множества граней найти множество их комбинированных номеров. \en For a set of faces find a set of their combined indices. 
          template <class FacesPointersVector, class ItemIndices> // ItemIndices - MbItemIndex vector
          bool        FindIndexByFaces( const FacesPointersVector &, ItemIndices &, size_t mapThreshold = 50 ) const;
          /// \ru Найти множество граней по множеству комбинированных индексов. \en Find a set of faces by a set of combined indices. 
          template <class ItemIndices, class ConstFacesPointersVector> // ItemIndices - MbItemIndex vector
          bool        FindConstFacesByIndex( const ItemIndices &, ConstFacesPointersVector & ) const;
          template <class ItemIndices, class FacesPointersVector> // ItemIndices - MbItemIndex vector
          bool        FindFacesByIndex( const ItemIndices &, FacesPointersVector & );

          bool        FindItemIndexByIndex( const std::vector<c3d::IndicesPair> &                     indexes, 
                                                  std::vector< std::pair<MbItemIndex,MbItemIndex> > & ind0 ) const;
          /// \ru Для множества вершин найти множество их комбинированных номеров. \en For a set of vertices find a set of their combined indices. 
          bool        FindIndexByVertices( const RPArray<MbVertex> & init, SArray<MbItemIndex> & indexes ) const;
          /// \ru Найти множество вершин по множеству комбинированных индексов. \en Find a set of vertices by a set of combined indices. 
          bool        FindVerticesByIndex( const SArray<MbItemIndex> & indexes, RPArray<MbVertex> & init ) const;
          /// \ru Найти комбинированный индекс грани. \en Find combined index of a face. 
          bool        FindIndexByFace( const MbFace &, MbItemIndex & ) const;
          /// \ru Найти грань по комбинированному индексу. \en Find a face by combined index. 
  const   MbFace *    FindFaceByIndex( MbItemIndex & ) const;
          /// \ru Найти грань по комбинированному индексу. \en Find a face by combined index. 
          MbFace *    FindFaceByIndex( MbItemIndex & );
          /// \ru Найти множество ребер с общей заданной вершиной. \en Find a set of edges with the common given vertex. 
          void        FindEdgesForVertex( const MbVertex & vertex, RPArray<MbCurveEdge> & findEdges ) const;
          /// \ru Найти множество граней с общей заданной вершиной. \en Find a set of faces with the common given vertex. 
          void        FindFacesForVertex( const MbVertex & vertex, RPArray<MbFace> & findFaces ) const;
          /// \ru Для ребра edge найти индекс грани, индекс цикла и индекс ребра в этом цикле. \en For the edge 'edge' find an index of face, an index of loop and an index of edge in this loop. 
          bool        FindEdgeNumbers( const MbCurveEdge & edge, size_t & faceN, size_t & loopN, size_t & edgeN ) const;

          /// \ru Найти вершину по имени. \en Find vertex by name. 
  const   MbVertex    * FindVertexByName( const MbName & ) const; 
          /// \ru Найти ребро по имени. \en Find edge by name. 
  const   MbCurveEdge * FindEdgeByName  ( const MbName & ) const; 
          /// \ru Найти грань по имени. \en Find face by name. 
  const   MbFace      * FindFaceByName  ( const MbName & ) const; 

          /// \ru Найти вершину по имени. \en Find vertex by name. 
          MbVertex    * FindVertexByName( const MbName & ); 
          /// \ru Найти ребро по имени. \en Find edge by name. 
          MbCurveEdge * FindEdgeByName  ( const MbName & ); 
          /// \ru Найти грань по имени. \en Find face by name. 
          MbFace      * FindFaceByName  ( const MbName & ); 

          /// \ru Объединить подобные грани. \en Merge similar faces. 
          bool        MergeSimilarFaces();

          /// \ru Создан ли временный объект сопровождения? \en Is a temporary object for the maintenance created? 
          bool        IsTemporal() const { return (temporal != NULL); } 
          /// \ru Удалить временный объект сопровождения. \en Delete a temporary maintenance object. 
          void        RemoveTemporal() const; 
          /// \ru Создать новый временный объект сопровождения. \en Create new temporary maintenance object. 
  const   MbFaceSetTemp * CreateTemporal( bool keepExisting ) const; 
          /// \ru Обновить временный объект сопровождения грани. \en Update a temporary maintenance object of a face. 
          /// \ru changedOnly = true использовать только при не измененной оболочке (после резки ребер), не обновляется дерево габаритов. \en changedOnly = true can only be used intact shell (after cutting edges).
          bool        UpdateTemporal( bool changedOnly = false ) const; 
          /// \ru Создан ли временный объект сопровождения грани? \en Is a temporary object for the maintenance of a face created? 
          bool        IsTemporal( size_t k ) const; 
          /// \ru Получить временный объект сопровождения грани. \en Get a temporary maintenance object of a face. 
          bool        CreateTemporal( size_t k, bool keepExisting ) const; 

          /// \ru Удалить атрибуты типа имя с родительскими именами. \en Delete attributes of name type with parent names. 
          void        RemoveParentNamesAttributes();

private:
          // \ru Объявление (перегрузка) оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en Declaration (overload) of the assignment operator without its implementation, to prevent the default assignment. 
          void        operator = ( const MbFaceShell & ); // \ru НЕЛЬЗЯ! \en NOT ALLOWED !!! 
          // \ru Создать копию набора граней с такой же или противоположной ориентацией. \en Create a copy of face set with such or an opposite orientation. 
          void        DataDuplicate( RPArray<MbFace> & faces, bool in, bool sameSurface, bool sameVertices,
                                     MbRegDuplicate * iReg ) const;
          // \ru Создать копию. \en Create a copy. 
          MbFaceShell * ShellDuplicate( bool sameSurface, bool sameVertices, MbRegDuplicate * iReg ) const;
          // \ru Создать копию. \en Create a copy. 
          MbFaceShell * ShellDuplicate( MbShellHistory & history, MbRegDuplicate * iReg ) const;

          /// \ru Обновить временный объект сопровождения после добавлении части оболочки. \en Update a temporary maintenance object after adding a shell. 
          bool        UpdateTemporalAddingShell( size_t innerBegInd ) const; 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbFaceShell )
};

IMPL_PERSISTENT_OPS( MbFaceShell )


//------------------------------------------------------------------------------
// \ru Конструктор по набору граней. \en Constructor by a set of faces. 
// ---
template <class Faces>
MbFaceShell::MbFaceShell( const Faces & initFaces )
  : MbTopItem()
  , faceSet  ( initFaces.size(), 1 )
  , closed   ( true                )
  , temporal ( NULL                )
{
  for ( size_t i = 0, cnt = initFaces.size(); i < cnt; ++i ) {
    if ( initFaces[i] != NULL )
      AddFace( *initFaces[i] );
  }
}

//------------------------------------------------------------------------------
// \ru Выдать множество вершин оболочки. \en Get a set of vertices of the shell. 
// ---
template <class VerticesVector>
void MbFaceShell::GetVertices( VerticesVector & vertices ) const
{
  if ( vertices.size() == 0 ) {
    // set label
    ptrdiff_t maxCount = SetVerticesLabel( ls_Used );
    vertices.reserve( vertices.size() + maxCount );

    SPtr<MbVertex> vertex;

    // reset label
    for ( size_t i = 0, fcount = faceSet.size(); i < fcount; ++i ) {
      const MbFace * face = faceSet[i];
      for ( size_t j = 0, lcount = face->GetLoopsCount(); j < lcount; ++j ) {
        const MbLoop * loop = face->_GetLoop( j );

        for ( size_t k = 0, ecount = loop->GetEdgesCount(); k < ecount; k++ ) {
          const MbCurveEdge * edge = &loop->_GetOrientedEdge( k )->GetCurveEdge();

          vertex = const_cast<MbVertex *>(&edge->GetBegVertex());
          if ( vertex->GetLabel() == ls_Used ) {
            vertices.push_back( vertex );
            vertex->SetOwnLabel( ls_Null );
          }
          ::DetachItem( vertex );

          vertex = const_cast<MbVertex *>(&edge->GetEndVertex());
          if ( vertex->GetLabel() == ls_Used ) {
            vertices.push_back( vertex );
            vertex->SetOwnLabel( ls_Null );
          }
          ::DetachItem( vertex );
        }
      }
    }
  }
  else {
    size_t count = faceSet.size();
    vertices.reserve( vertices.size() + count * 2 );
    for ( size_t i = 0; i < count; ++i )
      faceSet[i]->GetVertices( vertices );
  }
}

//------------------------------------------------------------------------------
// \ru Выдать множество вершин и множество ребер оболочки. \en Get a set of vertices and a set of edges of the shell. 
// ---
template <class VerticesVector, class EdgesVector>
void MbFaceShell::GetItems( VerticesVector & vertices, EdgesVector & edges ) const
{
  if ( edges.size() == 0 && vertices.size() == 0 ) {
    size_t maxCount = 1;

    size_t i, fcount;
    // set label
    for ( i = 0, fcount = faceSet.size(); i < fcount; ++i ) {
      const MbFace * face = faceSet[i];
      for ( size_t j = 0, lcount = face->GetLoopsCount(); j < lcount; ++j ) {
        const MbLoop * loop = face->_GetLoop( j );

        size_t ecount = loop->GetEdgesCount();
        for ( size_t k = 0; k < ecount; k++ ) {
          MbCurveEdge * edge = const_cast<MbCurveEdge *>(&loop->_GetOrientedEdge( k )->GetCurveEdge());
          edge->SetOwnLabel( ls_Used );
          edge->GetBegVertex().SetOwnLabel( ls_Used );
          edge->GetEndVertex().SetOwnLabel( ls_Used );
        }
        maxCount += ecount;
      }
    }

    size_t estVertsCnt = maxCount / 3;
    size_t estEdgesCnt = maxCount / 2;
    { // C3D-289
      estVertsCnt = std_max( (size_t)4, estVertsCnt );
      estEdgesCnt = std_max( (size_t)4, estEdgesCnt );
    }
    vertices.reserve( vertices.size() + estVertsCnt );
    edges.reserve( edges.size() + estEdgesCnt );

    // опускаем флаг
    for ( i = 0, fcount = faceSet.size(); i < fcount; ++i ) {
      const MbFace * face = faceSet[i];
      for ( size_t j = 0, lcount = face->GetLoopsCount(); j < lcount; ++j ) {
        const MbLoop * loop = face->_GetLoop( j );

        SPtr<MbCurveEdge> edge;
        SPtr<MbVertex> vertex;
        for ( size_t k = 0, ecount = loop->GetEdgesCount(); k < ecount; ++k ) {
          edge = const_cast<MbCurveEdge *>(&loop->_GetOrientedEdge( k )->GetCurveEdge());

          if ( edge->GetLabel() == ls_Used ) {
            edges.push_back( edge );
            edge->SetOwnLabel( ls_Null );
          }

          vertex = const_cast<MbVertex *>(&edge->GetBegVertex());
          if ( vertex->GetLabel() == ls_Used ) {
            vertices.push_back( vertex );
            vertex->SetOwnLabel( ls_Null );
          }
          ::DetachItem( vertex );

          vertex = const_cast<MbVertex *>(&edge->GetEndVertex());
          if ( vertex->GetLabel() == ls_Used ) {
            vertices.push_back( vertex );
            vertex->SetOwnLabel( ls_Null );
          }
          ::DetachItem( vertex );

          ::DetachItem( edge );
        }
      }
    }
  }
  else {
    size_t count = faceSet.size();
    size_t count2x = count * 2;
    edges.reserve( edges.size() + count2x );
    vertices.reserve( vertices.size() + count2x );

    for ( size_t i = 0; i < count; ++i ) {
      const MbFace * face = faceSet[i];
      face->GetEdges( edges );
      face->GetVertices( vertices );
    }
  }
}

//------------------------------------------------------------------------------
// \ru Для множества граней найти множество их комбинированных номеров. \en For a set of faces find a set of their combined indices. 
// ---
template <class FacesPointersVector, class ItemIndices>
bool MbFaceShell::FindIndexByFaces( const FacesPointersVector & initFaces, ItemIndices & indices, size_t mapThreshold ) const
{
  const size_t initFacesCount = initFaces.size();

  if ( initFacesCount > 0 ) {
    indices.reserve( indices.size() + initFacesCount );
    MbItemIndex index;

    bool directFind = true;

    if ( initFacesCount > mapThreshold ) { // performance
      typedef std::map<const MbFace *, size_t> FaceIndexMap;
      FaceIndexMap fiMap;
      size_t facesCount = faceSet.size();
      for ( size_t i = 0; i < facesCount; ++i )
        fiMap.insert( std::make_pair( faceSet[i], i ) );

      for ( size_t i = 0; i < initFacesCount; ++i ) {
        const MbFace * face = initFaces[i];
        if ( face != NULL ) {
          size_t i0 = SYS_MAX_T;
          FaceIndexMap::iterator it = fiMap.find( face );
          if ( it != fiMap.end() )
            i0 = it->second;
          if ( i0 != SYS_MAX_T ) {
            index.Init( *face, i0 );
            indices.push_back( index );
          }
        }
      }
      directFind = false;
    }
    if ( directFind ) {
      for ( size_t i = 0; i < initFacesCount; ++i ) {
        const MbFace * face = initFaces[i];
        if ( face != NULL ) {
          size_t i0 = GetFaceIndex( *face );
          if ( i0 != SYS_MAX_T ) {
            index.Init( *face, i0 );
            indices.push_back( index );
          }
        }
      }
    }
  }
  return (indices.size() > 0);
}

//------------------------------------------------------------------------------
// \ru Найти множество граней по множеству комбинированных индексов. \en Find a set of faces by a set of combined indices. 
// ---
template <class ItemIndices, class ConstFacesPointersVector>
bool MbFaceShell::FindConstFacesByIndex( const ItemIndices & indices, ConstFacesPointersVector & initFaces ) const
{
  SPtr<const MbFace> findFace;
  initFaces.reserve( initFaces.size() + indices.size() );
  for ( size_t j = 0, indicesCnt = indices.size(); j < indicesCnt; ++j ) {
    MbItemIndex & index = const_cast<MbItemIndex &>(indices[j]); // у stl доступ честный как const, у SArray дает на редактирование
    findFace = FindFaceByIndex( index );
    if ( findFace != NULL ) {
      initFaces.push_back( findFace );
      ::DetachItem( findFace );
    }
  }

  return initFaces.size() > 0;
}

//------------------------------------------------------------------------------
// \ru Найти множество граней по множеству комбинированных индексов. \en Find a set of faces by a set of combined indices. 
// ---
template <class ItemIndices, class FacesPointersVector>
bool MbFaceShell::FindFacesByIndex( const ItemIndices & indices, FacesPointersVector & initFaces )
{
  SPtr<MbFace> findFace;
  initFaces.reserve( initFaces.size() + indices.size() );
  for ( size_t j = 0, indicesCnt = indices.size(); j < indicesCnt; ++j ) {
    MbItemIndex & index = const_cast<MbItemIndex &>(indices[j]); // у stl доступ честный как const, у SArray дает на редактирование
    findFace = const_cast<MbFace *>(FindFaceByIndex( index ));
    if ( findFace != NULL ) {
      initFaces.push_back( findFace );
      ::DetachItem( findFace );
    }
  }

  return initFaces.size() > 0;
}


//------------------------------------------------------------------------------
/** \brief \ru Параметры функции проверки топологии оболочки.
           \en Parameters of validation of the shell. \~
  \details \ru Параметры функции проверки топологии оболочки. \n
           \en Parameters of validation of the shell. \n \~
  \ingroup Data_Structures
*/
//---
struct MATH_CLASS MbCheckTopologyParams {
protected:
  bool                  mergeEdges;        ///< \ru Флаг слияния ребер. \en Merge flag for edges. 
  bool                  addNameAttributes; ///< \ru Добавить атрибут имени с именами слитых ребер. \en Add name attribute with names of merged edges. 
  VERSION               version;           ///< \ru Версия. \en Version. 
  c3d::ConstFacesVector controlFaces;      ///< \ru Грани, по которым может быть взведена ошибка. \en Faces where an error may occur. 
  c3d::ConstEdgesVector boundaryEdges;     ///< \ru Исходные краевые ребра (до операции). \en Initial boundary edges (before an operation). 
public:
  explicit MbCheckTopologyParams( bool doMergingEdges, const MbSNameMaker & nameMaker )
    : mergeEdges       ( doMergingEdges                       )
    , addNameAttributes( nameMaker.GetParentNamesAttributes() )
    , version          ( nameMaker.GetMathVersion()           )
    , controlFaces     (                                      )
    , boundaryEdges    (                                      )
  {}
  explicit MbCheckTopologyParams( bool doMergingEdges, VERSION ver, bool addNameAttrs )
    : mergeEdges       ( doMergingEdges )
    , addNameAttributes( addNameAttrs   )
    , version          ( ver            )
    , controlFaces     (                )
    , boundaryEdges    (                )
  {}
  template <class Faces>
  explicit MbCheckTopologyParams( bool doMergingEdges, const MbSNameMaker & nameMaker, 
                                  const Faces & faces )
    : mergeEdges       ( doMergingEdges                       )
    , addNameAttributes( nameMaker.GetParentNamesAttributes() )
    , version          ( nameMaker.GetMathVersion()           )
    , controlFaces     (                                      )
    , boundaryEdges    (                                      )
  {
    size_t facesCnt = faces.size();
    if ( facesCnt > 0 ) {
      controlFaces.reserve( facesCnt );
      for ( size_t k = 0; k < facesCnt; ++k )
        controlFaces.push_back( faces[k] );
      std::sort( controlFaces.begin(), controlFaces.end() );
    }
  }
  template <class Faces>
  explicit MbCheckTopologyParams( bool doMergingEdges, VERSION ver, bool addNameAttrs, 
                                  const Faces & faces )
    : mergeEdges       ( doMergingEdges )
    , addNameAttributes( addNameAttrs   )
    , version          ( ver            )
    , controlFaces     (                )
    , boundaryEdges    (                )
  {
    size_t facesCnt = faces.size();
    if ( facesCnt > 0 ) {
      controlFaces.reserve( facesCnt );
      for ( size_t k = 0; k < facesCnt; ++k )
        controlFaces.push_back( faces[k] );
      std::sort( controlFaces.begin(), controlFaces.end() );
    }
  }
  template <class Faces>
  explicit MbCheckTopologyParams( bool doMergingEdges, const MbSNameMaker & nameMaker, 
                                  const Faces & faces, const c3d::ConstEdgesVector & edges )
    : mergeEdges       ( doMergingEdges                       )
    , addNameAttributes( nameMaker.GetParentNamesAttributes() )
    , version          ( nameMaker.GetMathVersion()           )
    , controlFaces     (                                      )
    , boundaryEdges    ( edges                                )
  {
    size_t facesCnt = faces.size();
    if ( facesCnt > 0 ) {
      controlFaces.reserve( facesCnt );
      for ( size_t k = 0; k < facesCnt; ++k )
        controlFaces.push_back( faces[k] );
      std::sort( controlFaces.begin(), controlFaces.end() );
    }
    std::sort( boundaryEdges.begin(), boundaryEdges.end() );
  }
  ~MbCheckTopologyParams() {}
public:
  bool      MergeEdges       () const { return mergeEdges; }
  bool      AddNameAttributes() const { return addNameAttributes; }
  VERSION   MathVersion      () const { return version;    }

  void      ClearControlFaces() { controlFaces.clear(); }
  void      SetControlFaces( const c3d::ConstFacesVector & faces )
  { 
    controlFaces = faces;
    std::sort( controlFaces.begin(), controlFaces.end() );
  }
  bool DeleteTheseSortedFaces( const c3d::ConstFacesVector & sortedDelFaces )
  {
    bool res = false;
    if ( controlFaces.size() > 0 && sortedDelFaces.size() > 0 ) {
      for ( size_t k = controlFaces.size(); k--; ) {
        if ( std::binary_search( sortedDelFaces.begin(), sortedDelFaces.end(), controlFaces[k] ) ) {
          controlFaces[k] = NULL;
          res = true;
        }
      }
      if ( res ) {
        std::sort( controlFaces.begin(), controlFaces.end() );
        controlFaces.erase( std::unique( controlFaces.begin(), controlFaces.end() ), controlFaces.end() );
        if ( controlFaces.front() == NULL )
          controlFaces.erase( controlFaces.begin() );
      }
    }
    return res;
  }
  
  const c3d::ConstFacesVector & GetSortedControlFaces() const { return controlFaces; }
  const c3d::ConstEdgesVector & GetSortedBoundaryEdges() const { return boundaryEdges; }
};


//------------------------------------------------------------------------------
/** \brief \ru Структура для передачи ребра и функции.
           \en A structure for edge and function transferring. \~
  \details \ru Структура передаёт информацию о ребре и функции изменения радиуса скругления ребра. 
    Структура используется в алгоритмах скругления ребер переменным радиусом. \n 
    Начальный параметр функции изменения радиуса соответствует начальной вершине ребра.
    Конечный параметр функции изменения радиуса соответствует конечной вершине ребра. \n
           \en A structure transmits an information about an edge and a function of edge fillet radius changing. 
    A structure is used in algorithms of edge fillet by the variable radius. \n 
    The starting parameter of radius changing function corresponds to the starting vertex of the edge.
    The ending parameter of radius changing function corresponds to the ending vertex of the edge. \n \~ 
  \ingroup Data_Structures
*/
// ---
struct MATH_CLASS MbEdgeFunction {
private:
  const MbCurveEdge * edge;     ///< \ru Ребро. \en An edge. 
  const MbFunction  * function; ///< \ru Функция изменения радиуса по относительной длине ребра. \en A function of radius changing by relative edge length. 

public:
  /// \ru Конструктор по умолчанию \en Default constructor 
  MbEdgeFunction  () : edge(NULL), function(NULL) {}
  /// \ru Конструктор по ребру и функции. \en Constructor by an edge and function. 
  MbEdgeFunction  ( const MbCurveEdge * e, const MbFunction * f ) : edge(e), function(f) {}
  /// \ru Конструктор по другому ребру с функцией. \en Constructor by other edge with a function. 
  MbEdgeFunction  ( const MbEdgeFunction & other ) : edge(other.edge), function(other.function) {}
  ~MbEdgeFunction() {}
public:
  /// \ru Функция инициализации по ребру и функции. \en A function of initialization by an edge and a function. 
  void                Init( const MbCurveEdge * e, const MbFunction * f ) { edge = e; function = f; }
  /// \ru Дать ребро. \en Get an edge. 
  const MbCurveEdge * Edge()     const { return edge; }
  /// \ru Дать функцию изменения радиуса. \en Get a function of radius changing. 
  const MbFunction  * Function() const { return function; }
  /// \ru Оператор присваивания. \en Assignment operator. 
  void                operator = ( const MbEdgeFunction & other ) { edge = other.edge; function = other.function; }
}; 


//------------------------------------------------------------------------------
/** \brief \ru Данные минимального расстояния между двумя оболочками.
           \en The data of the minimum distance between two shells. \~
  \details \ru Данные минимального расстояния между двумя оболочками.
           \en The data of the minimum distance between two shells. \~
  \ingroup Model_Items
*/
// ---
class MATH_CLASS MbShellsDistanceData {
public:
  struct ShellDetail {
    size_t      faceIndex;  ///< \ru Номер грани первой оболочки. \en Face index of the first shell. 
    MbCartPoint point;      ///< \ru Параметрическая точка на грани первой оболочки. \en Parametric point on a face of the first shell. ;
    size_t      loopIndex;  ///< \ru Номер цикла грани первой оболочки. \en Face loop index of the first shell. 
    size_t      edgeIndex;  ///< \ru Номер ребра в цикле первой оболочки, если точка на ребре. \en Loop edge index of the first shell if the point on the edge. 
    double      curveParam; ///< \ru Параметр на кривой ребра первой оболочки, если точка лежит на ребре. \en Parameter on the edge curve of the first shell, if the point on the edge. ;
    /// \ru Конструктор по умолчанию. \en Default constructor.
    ShellDetail()
      : faceIndex ( SYS_MAX_T     )
      , point()
      , loopIndex ( SYS_MAX_T     )
      , edgeIndex ( SYS_MAX_T     )
      , curveParam( UNDEFINED_DBL )
    {
    }
    /// \ru Конструктор копирования. \en Copy-constructor.
    ShellDetail( const ShellDetail & obj )
      : faceIndex ( obj.faceIndex  )
      , point     ( obj.point      )
      , loopIndex ( obj.loopIndex  )
      , edgeIndex ( obj.edgeIndex  )
      , curveParam( obj.curveParam )
    {
    }
  };
private:
  double minDist; ///< \ru Минимальное расстояние между оболочками. \en Minimum distance between the shells. 
  std::pair<ShellDetail, ShellDetail> shellDetail; ///< \ru Детализированная информация минимального расстояния между оболочками. \en Detailed information of the minimum distance between the shells. 
public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~
    \details \ru Конструктор данных расстояними между двумя телами.
             \en Constructor of distance date between two solids. \~
  */
  MbShellsDistanceData()
  : minDist ( UNDEFINED_DBL )
  , shellDetail()
{
}
  /// \ru Конструктор копирования. \en Copy-constructor.
  MbShellsDistanceData( const MbShellsDistanceData & obj )
  : minDist    ( obj.minDist     )
  , shellDetail( obj.shellDetail )
{
}
public:
  /// \ru Получить минимальную дистанцию между оболочками. \en Get the minimum distance between the shells.
  double      GetMinDistanse() const { return minDist; }
  /// \ru Получить индекс грани оболочки. \en Get the face index of the shell.
  size_t      GetFaceIndex( size_t i ) const { return ( i == 1 ) ? shellDetail.first.faceIndex : shellDetail.second.faceIndex; }
  /// \ru Получить параметрическую точку на грани оболочки. \en Get the parametric point on a face of the shell.
  MbCartPoint GetPoint( size_t i ) const { return ( i == 1 ) ? shellDetail.first.point : shellDetail.second.point; }
  /// \ru Получить номер цикла грани оболочки. \en Get the face loop index of the shell.
  size_t      GetLoopIndex( size_t i ) const { return ( i == 1 ) ? shellDetail.first.loopIndex : shellDetail.second.loopIndex; }
  /// \ru Получить номер ребра в цикле грани оболочки. \en Get the face loop edge index of the shell.
  size_t      GetEdgeIndex( size_t i ) const { return ( i == 1 ) ? shellDetail.first.edgeIndex : shellDetail.second.edgeIndex; }
  /// \ru Получить параметр на кривой ребра оболочки. \en Get parameter on the edge curve of the shell.
  double      GetCurveParam( size_t i ) const { return ( i == 1 ) ? shellDetail.first.curveParam : shellDetail.second.curveParam; }

  /// \ru Рассчитать данные минимального расстояния. \en Get Calculate the minimum distance.
  void        CalculateDistance( const MbFace & face1, const MbFace & face2 );
  /// \ru Вычислить набор дополнительных данных по расстоянию между гранями. \en Calculate a set of additional data by distance between faces. 
  void        CalculateAdditionData( const MbFace & face1, size_t faceInd1, const MbFace & face2, size_t faceInd2 );
  /// \ru Сбросить все данные. \en Reset all data. 
  void Reset()
  {
    minDist                       = UNDEFINED_DBL;
    shellDetail.first.faceIndex   = SYS_MAX_T;
    shellDetail.second.faceIndex  = SYS_MAX_T;
    shellDetail.first.point       = MbCartPoint( 0.0, 0.0 );
    shellDetail.second.point      = MbCartPoint( 0.0, 0.0 );
    shellDetail.first.loopIndex   = SYS_MAX_T;
    shellDetail.second.loopIndex  = SYS_MAX_T;
    shellDetail.first.edgeIndex   = SYS_MAX_T;
    shellDetail.second.edgeIndex  = SYS_MAX_T;
    shellDetail.first.curveParam  = UNDEFINED_DBL;
    shellDetail.second.curveParam = UNDEFINED_DBL;
  }
  /// \ru Поменять местами данные первой и второй оболочки. \en Switch the data of first and second shells. 
  void SwapDetail()
  {
    std::swap( shellDetail.first, shellDetail.second );
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  MbShellsDistanceData & operator = ( const MbShellsDistanceData & obj )
  {
    minDist                       = obj.minDist;
    shellDetail.first.faceIndex   = obj.shellDetail.first.faceIndex;
    shellDetail.second.faceIndex  = obj.shellDetail.second.faceIndex;
    shellDetail.first.point       = obj.shellDetail.first.point;
    shellDetail.second.point      = obj.shellDetail.second.point;
    shellDetail.first.loopIndex   = obj.shellDetail.first.loopIndex;
    shellDetail.second.loopIndex  = obj.shellDetail.second.loopIndex;
    shellDetail.first.edgeIndex   = obj.shellDetail.first.edgeIndex;
    shellDetail.second.edgeIndex  = obj.shellDetail.second.edgeIndex;
    shellDetail.first.curveParam  = obj.shellDetail.first.curveParam;
    shellDetail.second.curveParam = obj.shellDetail.second.curveParam;
    return (*this);
  }
};

//------------------------------------------------------------------------------
/** \brief \ru Объект с информацией о положении точки относительно оболочки.
           \en An object with information about the point location relative to the shell. \~
  \details \ru Объект содержит необходимую информацию о положении точки относительно оболочки. \n
           \en An object contains necessary information about the point location relative to the shell. \n \~
  \ingroup Data_Structures
*/
// ---
class MATH_CLASS MbPntLoc {
private:
  MbeItemLocation     pntLoc;  ///< \ru Положение точки относительно оболочки. \en The point location relative to the shell. 
  const MbFaceShell * shell;   ///< \ru Оболочка. \en A shell. 
  size_t              ind;     ///< \ru Номер грани. \en A face index. 
  double              dist;    ///< \ru Расстояние до грани. \en Distance to a face. 
  MbCartPoint         uv;      ///< \ru Точка на грани. \en A point on a face. 
  double              n;       ///< \ru Характеристика углового расположения (модульная). \en Characteristic of angular location (modular). 
  MbCartPoint3D       pnt;     ///< \ru Точка на грани. \en A point on a face. 
  MbVector3D          norm;    ///< \ru Нормаль в точке на грани. \en A normal in a face point. 
  MbeItemLocation     loc2d;   ///< \ru Классификация попадания на поверхность грани (не путать с классификацией отн-но оболочки). \en Classification of location on a face surface (do not confuse it with  classification relative to the shell). 
  c3d::IndicesPair    edgeLoc; ///< \ru Ближайшее ребро, на которое попали. \en The nearest edge, where the location is 
  bool                corn;    ///< \ru Попадание в вершину. \en Getting into a vertex. 

public:
  /// \ru Конструктор по умолчанию. \en Default constructor. 
  MbPntLoc()
    : pntLoc  ( iloc_Undefined )
    , shell   ( NULL           )
    , ind     ( SYS_MAX_T      )
    , dist    ( MB_MAXDOUBLE   )
    , n       ( MB_MAXDOUBLE   )
    , loc2d   ( iloc_OutOfItem )
    , edgeLoc ( SYS_MAX_T, SYS_MAX_T )
    , corn    ( false          )
  {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbPntLoc( const MbPntLoc & d )
    : pntLoc  ( d.pntLoc  )
    , shell   ( d.shell   )
    , ind     ( d.ind     )
    , dist    ( d.dist    )
    , n       ( d.n       )
    , loc2d   ( d.loc2d   )
    , edgeLoc ( d.edgeLoc )
    , corn    ( d.corn    )
  {}

public:
  /// \ru Получить положение пространственной точки. \en Get location of spatial point 
  MbeItemLocation       GetLocation() const { return pntLoc; }
  /// \ru Выбрана ли грань? \en Is a face chosen? 
  bool                  IsFaceSelected() const { return ((shell != NULL) && (ind < shell->GetFacesCount()) && (shell->GetFace(ind) != NULL)); }
  /// \ru Выполнена ли классификация по грани? \en Is classification by the face performed? 
  bool                  IsFaceData() const { return (IsFaceSelected() && !shell->IsTemporal(ind)) ? true : false; }
  /// \ru Выполнена ли классификация по грани сопровождения? \en Is classification by the face of maintenance performed? 
  bool                  IsTempData() const { return (IsFaceSelected() &&  shell->IsTemporal(ind)) ? true : false; }

  /// \ru Получить индекс грани. \en Get an index of a face. 
  size_t                GetFaceIndex() const { return ind;     }
  /// \ru Получить грань. \en Get a face. 
  const MbFace *        GetFace()      const { return (IsFaceSelected() ? shell->GetFace(ind) : NULL); }
  /// \ru Получить расстояние до точки проекции. \en Get the distance to projection point. 
  double                GetDistance()  const { return dist;    }
  /// \ru Получить двумерную точку проекции. \en Get two-dimensional projection point. 
  const MbCartPoint &   GetFacePoint() const { return uv;      }
  double                GetNormDisp()  const { return n;       }
  /// \ru Получить точку проекции. \en Get projection point. 
  const MbCartPoint3D & GetPoint()     const { return pnt;     }
  /// \ru Получить нормаль в точке проекции. \en Get the normal in projection point. 
  const MbVector3D &    GetNormal()    const { return norm;    }
  /// \ru Положение двумерной точки проекции относительно границ грани. \en Location of two-dimensional point relative to face boundaries. 
  MbeItemLocation       GetFaceLoc()   const { return loc2d;   }  
  // \ru Получить ближайшее ребро. \en Get the nearest edge. 
  const c3d::IndicesPair & GetEdgeLoc()   const { return edgeLoc; }
  /// \ru Попали на ребро? \en Are we get to an edge? 
  bool                  IsEdge()       const { return (edgeLoc.first != SYS_MAX_T && edgeLoc.second != SYS_MAX_T); }
  /// \ru Попали в вершину? \en Are we get to a vertex? 
  bool                  IsCorner()     const { return corn;    }

  /// \ru Получить поверхности грани. \en Get surfaces of a face. 
  const MbSurface *   GetFaceSurface() const { return (IsFaceSelected() ? &shell->GetFace(ind)->GetSurface() : NULL); }
  /// \ru Получить ориентацию грани относительно поверхности. \en Get face orientation relative a surface. 
  bool                GetFaceSense()   const { return (IsFaceSelected() ? shell->GetFace(ind)->IsSameSense() : true); }
  /// \ru Получить поверхность смежной грани. \en Get a surface of adjacent face. 
  const MbSurface *   GetEdgeSurface( bool getAdjacent ) const;
  /// \ru Попали на граничное ребро? \en Are we get to a boundary edge? 
  bool                IsBorderEdge() const;
  /// \ru Попали на шовное ребро? \en Are we get to a seam edge? 
  bool                IsSeamEdge  () const;
  /// \ru Попали на точное ребро? \en Are we get to an exact edge? 
  bool                IsExactEdge () const;

  /// \ru Сбросить все данные. \en Reset all data. 
  void Reset()
  {
    pntLoc = iloc_Undefined;
    shell  = NULL;
    ind    = SYS_MAX_T;
    dist   = MB_MAXDOUBLE;
    n      = MB_MAXDOUBLE;
    loc2d  = iloc_OutOfItem;
    corn   = false;
    edgeLoc.first  = SYS_MAX_T;
    edgeLoc.second = SYS_MAX_T;
    uv.SetZero();
    pnt.SetZero();
    norm.SetZero();
  }
  /// \ru Установить положение пространственной точки. \en Set location of spatial point 
  void SetLocation( MbeItemLocation pLoc ) { pntLoc = pLoc; }
  /// \ru Установить расстояние. \en Set the distance. 
  void SetDistance( double d )             { dist = d;      }
  /// \ru Установить нормаль. \en Set the normal. 
  void SetNormal  ( const MbVector3D & v ) { norm = v;      }
  /// \ru Функция инициализации. \en Initialization function. 
  void InitData( size_t _ind, const MbFaceShell & _shell, double _dist, const MbCartPoint & _uv, 
                 double _n, const MbCartPoint3D & _pnt, const MbVector3D & _norm,
                 MbeItemLocation _loc2d, const c3d::IndicesPair & _edgeLoc, bool _corn )
  {
    shell    = &_shell;
    ind      = _ind;
    dist     = _dist;
    uv       = _uv;
    n        = _n;
    pnt      = _pnt;
    norm     = _norm;
    loc2d    = _loc2d;
    edgeLoc  = _edgeLoc;
    corn     = _corn;
  }
  /// \ru Оператор присваивания. \en Assignment operator. 
  MbPntLoc & operator = ( const MbPntLoc & d )
  {
    pntLoc   = d.pntLoc;
    shell    = d.shell;
    ind      = d.ind;
    dist     = d.dist;
    uv       = d.uv;
    n        = d.n;
    pnt      = d.pnt;
    norm     = d.norm;
    loc2d    = d.loc2d;
    edgeLoc  = d.edgeLoc;
    corn     = d.corn;
    return (*this);
  }
  /// \ru Вычислить набор дополнительных данных по проецированию точки на грань. \en Calculate a set of additional data by projected point to a face. 
  bool CalculateFaceData( const MbCartPoint3D & pnt, const MbFaceShell & shell, size_t ind );
};


//------------------------------------------------------------------------------
/** \brief \ru Установить главное имя.
           \en Set main name. \~
  \details \ru Установить главное имя mainName для имени name. \n
           \en Set the main name 'mainName' for the name 'name'. \n \~ 
  \param[out] name    - \ru Имя.
                        \en Name. \~
  \param[in] mainName - \ru Главное имя.
                        \en The main name. \~
  \param[in] addOldMainName - \ru При true запомнить заменяемое главное имя в индексе копирования.
                              \en When it is true remember replaced main name in the copying index. \~
  \ingroup Algorithms_3D
*/
// ---
inline
void SetMainName( MbName & name, SimpleName mainName, bool addOldMainName )
{
  if ( !name.IsEmpty() ) {
    if ( addOldMainName )
      name.SetCopyIndex( name.GetMainName() );
    name.SetMainName( mainName );
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Установить заданную метку всем рёбрам оболочки.
           \en Set the specified label to all edges of the shell. \~
  \details \ru Установить заданную метку всем рёбрам оболочки.
           \en Set the specified label to all edges of the shell. \~
  \param[in,out] faceSet - \ru Множество граней.
                           \en A set of faces. \~
  \param[in] label - \ru Метка.
                     \en Label. \~
  \ingroup Algorithms_3D
*/
// ---
template <class FacesVector>
size_t SetEdgesLabel( const FacesVector & faceSet, MbeLabelState label, void * key = NULL )
{
  size_t maxCount = 1;

  // поднимаем флаг
  for ( size_t i = 0, fcount = faceSet.size(); i < fcount; ++i ) {
    const MbFace * face = faceSet[i];
    for ( size_t j = 0, lcount = face->GetLoopsCount(); j < lcount; ++j ) {
      const MbLoop * loop = face->_GetLoop( j );
      size_t ecount = loop->GetEdgesCount();
      for ( size_t k = 0; k < ecount; ++k ) {
        MbCurveEdge * edge = &loop->_GetOrientedEdge( k )->GetCurveEdge();
        edge->SetOwnLabel( label, key );
      }
      maxCount += ecount;
    }
    maxCount++; // reserve for pole edges
  }

  maxCount /= 2; // divide by two because every edge were calculated approximately twice.

  return ++maxCount;
}


//------------------------------------------------------------------------------
/** \brief \ru Выдать множество рёбер.
           \en Get a set of edges. \~
  \details \ru Выдать множество рёбер из множества граней.
           \en Get a set of edges from a set of faces. \~
  \param[in] faceSet - \ru Множество граней.
                       \en A set of faces. \~
  \param[out] edges  - \ru Множество рёбер.
                       \en A set of edges. \~
  \ingroup Algorithms_3D
*/
// ---
template <class FacesVector, class EdgesVector>
void GetEdges( const FacesVector & faceSet, EdgesVector & edges )
{
  // поднимаем флаг
  size_t maxCount = SetEdgesLabel( faceSet, ls_Used );
  edges.reserve( edges.size() + maxCount );

  // опускаем флаг
  for ( size_t i = 0, fcount = faceSet.size(); i < fcount; ++i ) {
    const MbFace * face = faceSet[i];

    SPtr<MbCurveEdge> edge;
    for ( size_t j = 0, lcount = face->GetLoopsCount(); j < lcount; ++j ) {
      const MbLoop * loop = face->_GetLoop( j );
      for ( size_t k = 0, ecount = loop->GetEdgesCount(); k < ecount; k++ ) {
        edge = const_cast<MbCurveEdge *>( &loop->_GetOrientedEdge( k )->GetCurveEdge() );
        if ( edge->GetLabel() == ls_Used ) {
          edge->SetOwnLabel( ls_Null );
          edges.push_back( edge );
        }
        ::DetachItem( edge );
      }
    }
  }
}


#endif // __TOPOLOGY_FACESET_H
