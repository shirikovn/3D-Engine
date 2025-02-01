#include <Eigen/Dense>
#include <iostream>

#include "objects/camera.h"
#include "renderer.h"
#include "world.h"

using namespace Eigen;

int main() {
    // test camera
    Camera camera;
    camera.eye = Vector3f(0, -10, 0);
    camera.up = Vector3f(0, 0, 1);
    camera.target = Vector3f(0, 0, 0);
    camera.near = 1.0f;
    camera.window_width = 60;
    camera.window_height = 120;

    World world;
    world.main_camera = camera;

    // Add test mesh here

    Renderer renderer;
    DumbFrameBuffer res = renderer.Render(world);

    // Output frame with sfml

    return 0;
}
