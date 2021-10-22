//
// Created by 17105727 on 22.10.2021.
//

#include "../Lights/AmbientLight.h++"
#include "../../../Screen/Render/RenderableObjects/Lights/RenderableAmbientLight.h++"
#include "../../../Screen/Render/IRenderer.h++"

class IRenderableLight;


void AmbientLight::setToRender() const {
    Settings& s = Settings::getInstance();
    IRenderer& r = s.getRenderer();

    RenderableAmbientLight renderableAmbientLight(*this);
    std::shared_ptr<IRenderableLight> ans = std::make_shared<RenderableAmbientLight>(renderableAmbientLight);
    r.addToRender(std::move(ans));
}