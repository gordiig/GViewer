//
// Created by 17105727 on 22.10.2021.
//

#include "../Lights/DotLight.h++"
#include "../../../Screen/Render/RenderableObjects/Lights/RenderableDotLight.h++"
#include "../../../Screen/Render/IRenderer.h++"

class IRenderableLight;


void DotLight::setToRender() const {
    Settings& s = Settings::getInstance();
    IRenderer& r = s.getRenderer();

    RenderableDotLight renderableDotLight(*this);
    std::shared_ptr<IRenderableLight> ans = std::make_shared<RenderableDotLight>(renderableDotLight);
    r.addToRender(std::move(ans));
}
