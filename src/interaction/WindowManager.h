#pragma once

#include "Renderer.h"
#include "interaction/KeyBoardInteraction.h"
#include "scene/Scene.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace Render3D {
class WindowManger {
public:
    void manage(unsigned width, unsigned height, Scene& scene, Renderer& renderer, KeyBoardInteracor interactor);
};
}
