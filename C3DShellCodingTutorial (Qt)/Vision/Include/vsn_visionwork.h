////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Базовый класс для выполнения работ в Vision.
           \en NOT TRANSLATED. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_VISIONWORK_H
#define __VSN_VISIONWORK_H

#include <memory>
#include <vector>
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class VisionWorkPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Базовый класс для выполнения работ в Vision.
            \en NOT TRANSLATED. \~
    \ingroup Vision_Core
*/
// ---
class VisionWork
{
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION. \~
    VisionWork();
    /// \ru Деструктор. \en Destructor. \~
    virtual ~VisionWork();
public:
    /// \ru Вернуть вектор зависимых заданий. \en NO TRANSLATION. \~
    std::vector<std::weak_ptr<VisionWork> > GetDependencies() const;
    /// \ru Добавляет зависимость к заданию. \en NO TRANSLATION. \~
    void AppendDependency(std::weak_ptr<VisionWork> dependency);
    /// \ru Удаляет данную зависимость из задания аспекта. \en NO TRANSLATION. \~
    void RemoveDependency(std::weak_ptr<VisionWork> dependency);
public:
    virtual void DoWork() = 0;
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION. \~
    explicit VisionWork(VisionWorkPrivate& dd);
protected:
    VSN_DECLARE_PRIVATE(VisionWork)
private:
    VSN_DISABLE_COPY(VisionWork)
};

typedef std::shared_ptr<VisionWork> VisionWorkPtr;

VSN_END_NAMESPACE

#endif /* __VSN_VISIONWORK_H */
