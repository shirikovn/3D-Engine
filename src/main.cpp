#include "Application.h"

int main() {
    try {
        Render3D::Application app;
        app.run();
    } catch (...) {
    }

    return 0;
}
