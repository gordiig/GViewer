//
// Created by 17105727 on 22.10.2021.
//

#include "../../../Basics/Polygon.h++"
#include "../../../Screen/Render/RenderableObjects/3D/RenderablePolygon.h++"

class IRenderable;

void Polygon::setToRender() const {
    Settings& s = Settings::getInstance();
    IRenderer& renderer = s.getRenderer();

    RenderablePolygon renderablePolygon(*this);
    std::shared_ptr<IRenderable> ans = std::make_shared<RenderablePolygon>(renderablePolygon);
    renderer.addToRender(std::move(ans));
}
