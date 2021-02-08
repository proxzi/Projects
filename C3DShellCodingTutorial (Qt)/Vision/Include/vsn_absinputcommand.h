////////////////////////////////////////////////////////////////////////////////
/**
  \file
    \brief \ru AbsInputCommand является базовым классом для ввода определенных команд.
           \en AbsInputCommand class is a base class for input of certain comands. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ABSINPUTCOMMAND_H
#define __VSN_ABSINPUTCOMMAND_H

#include "vsn_node.h"

VSN_BEGIN_NAMESPACE

class AbsInputCommandPrivate;
//------------------------------------------------------------------------------
/** \brief   \ru AbsInputCommand является базовым классом для ввода определенных команд.
             \en AbsInputCommand class is a base class for input of certain comands. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS AbsInputCommand : public Node
{
    VSN_OBJECT(AbsInputCommand)  
public:
    /// \ru Деструктор. \en Destructor. \~
    ~AbsInputCommand();
protected:
    /// \ru Конструктор для наследников. \en Constructor for inheritors. \~
    explicit AbsInputCommand(AbsInputCommandPrivate& dd, Node* pParent = nullptr);
};

VSN_END_NAMESPACE

#endif // __VSN_ABSINPUTCOMMAND_H
