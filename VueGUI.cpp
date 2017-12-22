#include <VueGUI.h>

VueGUI::VueGUI() : QWidget()
{
    setFixedSize(300,150);

    button = new QPushButton("hello",this);
 
}
