//
// Created by 17105727 on 05.10.2021.
//

#ifndef GVIEWER_SETTINGS_H
#define GVIEWER_SETTINGS_H

#include <sstream>
#include "../Utils/BaseObject.h++"
#include "../Graphics/Screen/CameraPyramid.h++"

// For reduction of circular imports
class IRenderer;
class ICamera;
class IShader;

class Settings: public BaseObject {
protected:
    Settings() noexcept = default;

    std::unique_ptr<IRenderer> renderer;
    std::shared_ptr<ICamera> currentCamera;
    std::unique_ptr<CameraPyramid> cameraPyramid;
    std::unique_ptr<IShader> currentShader;

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

    [[nodiscard]] IRenderer& getRenderer() const { return *renderer; }
    [[nodiscard]] ICamera& getCamera() const { return *currentCamera; }
    [[nodiscard]] IShader& getShader() const { return *currentShader; }
    [[nodiscard]] CameraPyramid& getCameraPyramid() { return *cameraPyramid; };

    void setRenderer(std::unique_ptr<IRenderer> &&newRenderer) { this->renderer = std::move(newRenderer); }
    void setCamera(std::shared_ptr<ICamera> &&newCamera) {
        this->cameraPyramid = std::make_unique<CameraPyramid>(CameraPyramid(*newCamera));
        this->currentCamera = std::move(newCamera);
    }
    void setShader(std::unique_ptr<IShader> &&newShader) { this->currentShader = std::move(newShader); }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[Settings]";
        return sst.str();
    }
};

#endif //GVIEWER_SETTINGS_H
