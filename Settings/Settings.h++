//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_SETTINGS_H
#define GVIEWER_SETTINGS_H

#include <sstream>
#include "../Utils/BaseObject.h++"
#include "../Graphics/Screen/IRenderer.h++"
#include "../Graphics/Screen/Renderer.h++"

class Settings: public BaseObject {
protected:
    Settings() noexcept = default;

    std::unique_ptr<IRenderer> renderer;

public:
    Settings(const Settings &copy) noexcept = delete;
    Settings(Settings &&move) noexcept = delete;
    Settings& operator = (const Settings &copy) = delete;
    Settings& operator = (Settings &&move) = delete;

    static Settings& getInstance() noexcept {
        static Settings instance;
        return instance;
    }

    ~Settings() noexcept override = default;

    [[nodiscard]] IRenderer& getRenderer() const { return *renderer; };

    void setRenderer(std::unique_ptr<IRenderer> &&newRenderer) { this->renderer = std::move(newRenderer); }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[Settings]";
        return sst.str();
    }
};

#endif //GVIEWER_SETTINGS_H
