#include <QColorDialog>
#include <QPainter>

#include "colorbutton.h"
#include "globaldef.h"

/*ColorButton*/
ColorButton::ColorButton(QWidget* parent)
    : QPushButton(parent)
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

    setMinimumHeight(g_kIconSize + 4);
    QFontMetrics fm(font());
    QRect rc = fm.boundingRect("XXXXXX");
    //QSize sz(50, rc.height() + 4);
    QSize sz(g_kIconSize, g_kIconSize);

    setIconSize(sz);
    QObject::connect(this, SIGNAL(released()), this, SLOT(chooseColor()));
}

void ColorButton::setColorFor(ColorFor ColorFor)
{
    m_colorFor = ColorFor;
}

void ColorButton::chooseColor()
{
    QColor newCol = QColorDialog::getColor(m_color, this);
    if (newCol.isValid())
        setColor(newCol);
}

void ColorButton::setColor(const QColor& clr)
{
    if (m_color != clr)
    {
        m_color = clr;

        QFontMetrics fm(font());
        QRect rc = fm.boundingRect(text());

        QSize sz = iconSize();
        QPixmap px(sz);
        QPainter p(&px);
        p.fillRect(QRect(QPoint(0, 0), sz), m_color);
        QIcon icon; icon.addPixmap(px);
        setIcon(icon);
        switch (m_colorFor) {
        case ColorFor::Model:
            emit colorChangedForModel(m_color);
            break;
        case ColorFor::SOrH:
            emit colorChanged(m_color);
            break;
        }
    }
}