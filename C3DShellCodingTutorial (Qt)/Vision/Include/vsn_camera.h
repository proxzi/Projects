////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Камера для отрисовки 3D сцены.
       \en Camera for 3D scene rendering. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_CAMERA_H
#define __VSN_CAMERA_H

#include <mb_vector3d.h>
#include <mb_cart_point3d.h>
#include <mb_matrix3d.h>

#include "vsn_essence.h"
#include "vsn_namespace.h"

#include "vsn_global.h"


VSN_BEGIN_NAMESPACE

class CameraPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс виртуальной камеры для отрисовки 3D сцены.
           \en A class for 3D scene rendering, using virtual camera. \~
    \details \ru Класс виртуальной камеры для отрисовки 3D сцены. Он представляет много разных методов для позиционирования, ориентации камеры,
                 а также точку взгляда на сцену и.т.д. При отрисовке сцены камера расчитывает как матрицу проецирования, так и матрицу вида.
                 Камера может позиционироваться перед любым сегментом сцены для правильного его отображения. Положение и ориентация камеры
                 по умолчанию равны (0,0,1) по направлению взгляда вдоль отрицательной оси.\n.
             \en A virtual camera class for 3D scene rendering. It represents a lot of different methods for positioning, camera orientation,
                and also gives a point of scene view. When rendering a scene the camera initializes matrix of projection and view matrix.
                Camera can be positioned in front of any scene segment for its right rendering.
                The default position and orientation of the camera are (0,0,1) with a view direction along negative axis.\n \~
    \ingroup Vision_Viewport
*/
// ---
class VSN_CLASS Camera : public Essence
{
    VSN_OBJECT(Camera)
public:
    /** \brief \ru Конструктор по умолчанию.
               \en Default constructor. \~
        \details \ru Конструктор по умолчанию. Позиция взгляда (0, 0, 1), up-вектор инициализирован по оси y (0, 1, 0).
                     Угол обзора составляет 30 градусов и диапазон отсечения составляет (0.1, 1000.0).\n
                 \en Default constructor. The position of view is (0, 0, 1), up vector is initialized by y-axis (0, 1, 0). View angle is 30 degrees, clipping range is (0.1, 1000.0). \n \~
    */
    Camera();
    /** \brief \ru Конструктор по параметрам.
               \en Constructor by parameters. \~
    */
    Camera(const MbCartPoint3D&, const MbCartPoint3D&, const MbVector3D &);
    /// \ru Конструктор копирования. \en Copy constructor. \~
    Camera(const Camera& other);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~Camera();
public:
    /// \ru Инициализация камеры по параметрам. \en Initializes the camera by parameters. \~ 
    void Init(const MbCartPoint3D & position, const MbCartPoint3D & targetPosition, const MbVector3D & up);
    /// \ru Инициализация камеры по параметрам. \en Initializes the camera by parameters. \~
    void Init(const MbCartPoint3D & position, const MbVector3D & up);
    /// \ru Инициализация камеры по параметру. \en Initializes the camera by parameter. \~ 
    void Init(const MbCartPoint3D & position);
    /// \ru Инициализация камеры по параметру. \en Initializes the camera by parameter. \~ 
    void InitTarget(const MbCartPoint3D & targetPosition);
    /// \ru Инициализация камеры по другой камере. \en Initializes the camera by other camera. \~ 
    void Init(const Camera & other);
public:
    /// \ru Вернуть реальное расстояние между объектом и камерой. \en Returns a real distance between target and camera. \~ 
    double DistanceCameraToTarget() const;
    /// \ru Установить новое расстояние между камерой и объектом, т.е. переместить камеру. Эта величина должна быть положительная. \en Sets new distance between target and camera, i.e. replace the camera. This value must be positive. \~
    void SetDistanceCameraToTarget(double dis);
    /// \ru Установить новое расстояние между объектом и камерой, т.е. переместить объект. Эта величина должна быть положительная. \en Sets new distance between target and camera, i.e. replace the camera. This value must be positive. \~ 
    void SetDistanceTargetToCamera(double dis);

    /// \ru Вернуть позицию камеры. \en Returns camera position. \~ 
    const MbCartPoint3D & GetPosition() const;
    /// \ru Установить новую позицию камеры. По умолчанию позиция (0, 0, 1). \en Sets new position for the camera. The default position is (0, 0, 1). \~   
    void SetPosition(const MbCartPoint3D & position);

    /// \ru Вернуть позицию объекта сцены. По умолчанию в качестве позиции объекта берется его центр. \en Returns position of scene target. The default position of target is the origin. \~  
    const MbCartPoint3D & GetTargetPosition() const;
    /// \ru Установить позицию объекта. По умолчанию в качестве позиции объекта берется его центр. \en Sets position of target. The default position of target is the origin. \~
    void SetPositionTarget(const MbCartPoint3D & targetPosition);

    /// \ru Вернуть up-вектор камеры. По умолчанию значение (0, 1, 0). \en Returns up vector of the camera. The default value is (0, 1, 0). \~ 
    const MbVector3D & GetUpVector() const;
    /// \ru Установить up-вектор камеры. По умолчанию значение (0, 1, 0). \en Sets up vector of the camera. The default value is (0, 1, 0). \~ 
    void SetUpVector(const MbVector3D & up);

    /// \ru Вернуть вектор взгляда от камеры до цели. \en Returns view vector from camera to target. \~ 
    MbVector3D GetForward() const;
    /// \ru Вернуть вектор со стороны камеры. \en Returns vector from the camera. \~ 
    MbVector3D GetSideVector() const;
    /// \ru Получить видовую матрицу (матрицу камеры). \en Returns view matrix (camera matrix). \~ 
    const MbMatrix3D & GetViewMatrix() const;

    /// \ru Вернуть up вектор камеры по умолчанию. \en Returns the default up vector of the camera. \~ 
    const MbVector3D & GetDefaultUpVector() const;
    /// \ru Установить up вектор камеры по умолчанию. \en Sets the default up vector of the camera. \~ 
    void SetDefaultUpVector(const MbVector3D& vecUp);

    /// \ru Установить стандартный вид ориентации. \en Sets standard view of orientation. \~ 
    void SetViewOrientation(Orientation orientation);
    /// \ru Вернуть матрицу вида камеры. \en Returns view matrix of the camera. \~ 
    MbMatrix3D GetModelViewMatrix() const;
    MbMatrix3D GetWordTransform() const;
public:
    /// \ru Вращение вокруг начала координат мира(по орбите). \en Rotates around the world origin (by orbit). \~ 
    void RotateSpherical(const MbVector3D& vectOld, const MbVector3D& vectCur);
    /// \ru Панорамирование вида. \en View panning. \~ 
    void Pan(const MbVector3D& vectShift);
    /// \ru Cдвиг вектора камеры вдоль вектора взгляда (фактор должен быть больше 0). \en Moves vector of the camera along view vector(factor must be more 0). \~ 
    void SetZoom(double factor);

    /// \ru Поменять положение камеры согласно заданной матрице. \en Changes the camera position by the defined matrix. \~ 
    void Transform(const MbMatrix3D& matMove);
    /// \ru Повернуть вокруг оси. \en Rotates about the axis. \~ 
    void RotateAbout(const MbVector3D& axis, double angle, const MbCartPoint3D& pnt);
    /// \ru Повернуть вокруг объекта (его позиции). \en Rotates about the target( its origin). \~ 
    void RotateAboutTarget(const MbVector3D& vec, double angle);
    /// \ru Перемещение камеры по вектору. \en Moves the camera by vector. \~
    void Translate(const MbVector3D& vecTrans);

    /** \brief \ru Перемещение камеры вокруг объекта сцены.
               \en Moves the camera about scene target. \~
        \param[in] angle1 - \ru Расстояние в радианах, которое камера обойдет вокруг объекта(Target) слева на право. Может быть отрицательным.
                            \en The distance, in radians, that camera passes around the target from left to right. Can be negative. \~

        \param[in] angle2 - \ru Расстояние в радианах, которое камера обойдет вокруг объекта(Target) снизу вверх. Может быть отрицательным.
                            \en The distance, in radians, that camera passes around the target from bottom to top. Can be negative. \~
    */
    void Orbit(double angle1, double angle2);

    /** \brief \ru Вращение камеры вокруг оси взгляда.
               \en Rotates camera about view axis. \~
        \param[in] angle - \ru Угол поворота камеры вокруг оси взгляда в радианах.
                           \en Rotation angle of the camera, in radians, about view axis. \~
    */
    void Roll(double angle);
public:
    /// \ru Настроить OpenGL камеру перед отрисовкой всей сцены. \en Sets OpenGL camera before the whole scene rendering. \~ 
    void oglMultMatrix();
public:
    /// \ru Оператор равенства. \en Equality operator. \~ 
    bool operator == (const Camera & other) const;
private:
    VSN_DECLARE_EX_PRIVATE(Camera);
};

VSN_END_NAMESPACE

#endif /* __VSN_CAMERA_H */
