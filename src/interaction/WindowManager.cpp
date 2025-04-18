#include "WindowManager.h"

namespace Render3D {
void WindowManger::manage(unsigned int width, unsigned int height, Scene &scene, Renderer &renderer, KeyBoardInteracor interactor) {
    sf::RenderWindow window(sf::VideoMode({width, height}), "My window");
    sf::Image image({width, height}, sf::Color::Transparent);
    sf::Texture texture(image);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        auto output = renderer.render({width, height}, scene);

        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                image.setPixel({i, j}, {output(i, j).red, output(i, j).green, output(i, j).blue});
            }
        }

        texture.update(image);
        sf::Sprite sprite(texture);

        window.draw(sprite);
        window.display();

        interactor.moveCamera(scene.camera);

        // FIXME should be somewhere else
        scene.lights.back().position = scene.camera.eye_;
    }
}
}