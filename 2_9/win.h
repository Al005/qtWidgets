#ifndef win_h
#define win_h
#include <QtWidgets>
#include "area.h"
class Window : public QWidget
{
protected:
    QTextCodec *codec;
    Area * area; // область отображения рисунка
    QPushButton * btn;
public:
    Window();
};
#endif
