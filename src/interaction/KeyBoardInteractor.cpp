#include "interaction/KeyBoardInteraction.h"
#include <SFML/Window/Keyboard.hpp>

namespace Render3D {
    void KeyBoardInteracor::moveCamera(Camera& camera) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            camera.moveForward();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camera.moveBackward();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            camera.moveLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            camera.moveRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            camera.rotateUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            camera.rotateDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            camera.rotateRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            camera.rotateLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            camera.moveUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            camera.moveDown();
        }
    }
}