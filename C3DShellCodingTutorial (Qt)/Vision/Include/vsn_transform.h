////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Общий узел 3D геометрического преобразования.
           \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_TRANSFORM_H
#define __VSN_TRANSFORM_H

#include "vsn_feature.h"

VSN_BEGIN_NAMESPACE

class TransformPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Общий узел 3D геометрического преобразования.
            \en NO TRANSLATION. \~
    \details  \ru  Этот узел определяет геометрическое трехмерное преобразование 
                   в основе которого лежит математическая матрица преобразование. \n.
              \en  NO TRANSLATION. \n \~
    \ingroup Vision_Transforms
*/
// ---
class VSN_CLASS Transform : public Feature
{
    VSN_OBJECT(Transform);
    VSN_PROP_READ_WRITE_NOTIFY(matrix, GetMatrix, SetMatrix, MatrixModified)
public:
    /// \ru Конструктор по умолчанию. \en Constructor.
    explicit Transform(Node* pParent = nullptr);
    /// \ru Конструктор с параметрами перемещения
    Transform( const MbCartPoint3D & origin, Node* pParent = nullptr);
    /// \ru Конструктор с параметрами преобразования
    Transform(const MbCartPoint3D & origin, double angleX, double angleY, double angleZ, Node* pParent = nullptr);
    /// \ru Конструктор с параметрами преобразования
    Transform(double angleX, double angleY, double angleZ, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~Transform();
public:
    /// \ru Вернуть математическую матрицу. \en NO TRANSLATION.
    MbMatrix3D GetMatrix() const;
public:
    VSN_SLOT(Public, SetMatrix, void SetMatrix(const MbMatrix3D& matrix))
    VSN_SLOT(Public, Move,   void Move(const MbVector3D& v))
    VSN_SLOT(Public, Scale,  void Scale(double x, double y, double z))
    VSN_SLOT(Public, Rotate, void Rotate(double x, double y, double z))
public:
    VSN_SIGNAL(Public, MatrixModified, void MatrixModified())
protected:
    /// \ru Приватный конструктор для наследников. \en Private construсtor for inheritors.
    explicit Transform(TransformPrivate& dd, Node* pParent = nullptr);
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(Transform);
};

VSN_END_NAMESPACE

#endif // __VSN_TRANSFORM_H
