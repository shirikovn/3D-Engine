#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <string>

#include "Renderer.h"
#include "core/primitives/Color.h"
#include "interaction/KeyBoardInteraction.h"
#include "interaction/WindowManager.h"
#include "scene/Camera.h"
#include "scene/PointLight.h"
#include "scene/Scene.h"
#include "parser/SimpleParser.h"
#include "stages/SceneLoaderStage/SceneLoader.h"

namespace Render3D {
class Application {
public:
    void run(const std::string test_input) {
        // Configure scene
        constexpr unsigned int height = 800;
        constexpr unsigned int width = 800;

        Color base_color{210, 180, 140};
        
        float dist = 3;
        Render3D::Camera camera{Render3D::Vector3(-1 * dist, -1 * dist, 0 * dist),
                                Render3D::Vector3(0, 0, 0), 2, 10, 10};

        Scene scene{.camera{camera}};
        scene.lights.push_back(PointLight{.intensity = 1, .position = {-1 * dist, -1 * dist, 1.5 * dist}});

        Parser::OBJParser parser;
        Parser::ParsedMesh parsed_mesh = parser.parse(test_input);

        SceneLoader scene_loader;
        scene_loader.addMeshOnScene(scene, std::move(parsed_mesh), base_color);
            
        
        // Main class
        Renderer renderer;
        KeyBoardInteracor interactor;

        WindowManger manager;
        manager.manage(width, height, scene, renderer, interactor);
    }
};
}
