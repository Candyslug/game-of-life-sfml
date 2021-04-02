//======WIPPY ENGINE======//
//========================//
#include "sdk.h"
#include "Window.h"

int main()
{
    int windowSize = 1000;
    Window myWindow("WIPPYENGINE->Cellular Automota", sf::Vector2i(windowSize, windowSize + 100));
    myWindow.update();
    return 0;
}