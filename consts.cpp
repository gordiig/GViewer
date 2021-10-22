//
// Created by 17105727 on 22.10.2021.
//

#include "Graphics/Screen/Render/RenderableObjects/Lights/IRenderableLight.h++"
const unsigned short IRenderableLight::MAX_INTENSITY = 255;

#include "Graphics/Scene/ISceneObject.h++"
unsigned long long ISceneObject::idCounter = 0;

#include "Graphics/Screen/Render/RenderableObjects/IRenderable.h++"
const Screen IRenderable::EMPTY_SCREEN = {0, 0, {0, 0}};

#include "Graphics/Screen/Render/Shaders/IShader.h++"
const Screen IShader::EMPTY_SCREEN = {0, 0, {0, 0}};
