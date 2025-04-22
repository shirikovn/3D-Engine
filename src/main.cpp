#include "Applicaton.h"

int main(int argc, char* argv[]) {
    try {
        Render3D::Application app;
        app.run(argv[1]);
    } catch (...) {
    }

    return 0;
}
