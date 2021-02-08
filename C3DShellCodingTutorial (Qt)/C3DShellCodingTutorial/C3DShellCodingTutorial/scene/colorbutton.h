#pragma once

#include <QPushButton>

enum class ColorFor {
    Model,
    SOrH
};

class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    ColorButton(QWidget* parent = nullptr);
    void setColorFor(ColorFor ColorFor);
public slots:
    void chooseColor();
    void setColor(const QColor& clr);
signals:
    void colorChangedForModel(const QColor& color);
    void colorChanged(const QColor& color);
private:
    QColor m_color;
    ColorFor m_colorFor;
};