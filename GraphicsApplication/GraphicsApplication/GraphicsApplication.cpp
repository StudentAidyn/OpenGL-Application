#include "glad.h"
#include "Application.h"
#include "Application3D.h"

int main()
{
    Application3D* app = new Application3D();
    if (app->startup() == true) {
        while (app->update() == true)
            app->draw();
        app->shutdown();
    }

    delete app;
    return 0;
}


