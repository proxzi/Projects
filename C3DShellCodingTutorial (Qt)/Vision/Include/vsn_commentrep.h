////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru CommentRep - это класс, представляющий текст в рамке на выносной линии.
         \en CommentRep class presents a text in a frame on an extension line. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COMMENTREP_H
#define __VSN_COMMENTREP_H

#include "vsn_global.h"
#include "vsn_geometryrep.h"
#include "vsn_wireframegeometry.h"

#include <string>

VSN_BEGIN_NAMESPACE

class CommentGeometry;
//------------------------------------------------------------------------------
/** \brief \ru CommentRep - это класс, представляющий текст в рамке на выносной линии.
           \en CommentRep class presents a text in a frame on an extension line. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS CommentRep : public GeometryRep
{
    VSN_OBJECT(CommentRep)
public:
    /// \ru Конструктор по умолчанию. \en Default consructor. \~
    CommentRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CommentRep();
public:
    /** \brief \ru Инициализировать объект по двум параметрам. \en Initializes object by two parameters. \~
               \param[in] first  - \ru Положение начала выносной линии. 
                                   \en Position of extension line start. \~
               \param[in] second - \ru Положение текста. 
                                   \en Text position. \~
    */
    void Init(const MbCartPoint3D& first, const MbCartPoint3D& second);
    /// \ru Задать текст. \en Sets text. \~
    void SetText(const WString & text);
    /// \ru Задать текст. \en Sets text. \~
    void SetText(const std::wstring & text);
    /// \ru Очистить текст. \en Clears text. \~
    void ClearText();
    /// \ru Изменить размер шрифта текста. \en Changes text font size. \~
    void SetFontSize(int size);
    // \ru Установить направление текста. \en Set text direction.
    void SetTextDirection(TextDirection dir);
    // \ru Получить направление текста. \en Get text direction.
    TextDirection GetTextDirection() const;
    /// \ru Скрыть линии. \en Hide lines. \~
    void HideLines();
    /// \ru Показать линии. \en Show lines. \~
    void ShowLines();
    /// \ru Получить пересечения текста комментария с экраном. \en Get text intersection with screen. \~
    int GetViewportIntersection(const Viewport & viewport);
private:
    VSN_DISABLE_COPY(CommentRep)
};

VSN_END_NAMESPACE

#endif /* __VSN_COMMENT_H */
