#ifndef __VSN_VISIONENGINE_H
#define __VSN_VISIONENGINE_H

#include "vsn_object.h"
#include "vsn_essence.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class SceneContent;
class AbsVisionComponent;
class VisionEnginePrivate;
//------------------------------------------------------------------------------
/** \brief   \ru NO TRANSLATION.
             \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION. \n
             \en NO TRANSLATION. \n \~
    \ingroup NO GROUP
*/
class VSN_CLASS VisionEngine : public Object
{
    VSN_OBJECT(VisionEngine)
public:
    explicit VisionEngine(Object* pParent = nullptr);
    virtual ~VisionEngine();
public:    
    /// \ru Вернуть топовый объект механизма Vision. \en NO TRANSLATION. \~
    EssencePtr GetTopEssence() const;
    void SetTopEssence(EssencePtr ptrEssence);
    std::vector<AbsVisionComponent*> GetComponents() const;
public:
    void ComponentInstallation(AbsVisionComponent* pComponent);
    void ComponentUninstallation(AbsVisionComponent* pComponent);
private:
    VSN_DECLARE_EX_PRIVATE(VisionEngine);
};

typedef std::shared_ptr<VisionEngine> VisionEnginePtr;

VSN_END_NAMESPACE

#endif /* __VSN_VISIONENGINE_H */
