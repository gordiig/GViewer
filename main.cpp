#include <QApplication>
//#include <QPushButton>
#include <iostream>

#include "Exceptions/Exception.h++"
#include "Exceptions/Math.h++"
#include "Exceptions/Memory.h++"
#include "Exceptions/Range.h++"

#include "Settings/Settings.h++"

#include "Geometry/Basics/Point2.h++"
#include "Geometry/Basics/Point3.h++"
#include "Geometry/Basics/Angle.h++"
#include "Geometry/Basics/Vector.h++"

#include "Geometry/Transform/PointTransformer.h++"

#include "Graphics/Basics/ShadingCoefficients.h++"
#include "Graphics/Basics/Vertex.h++"
#include "Graphics/Basics/RGBA.h++"
#include "Graphics/Basics/Polygon.h++"

#include "Graphics/Scene/ISceneObject.h++"
#include "Graphics/Scene/CompositeSceneObject.h++"
#include "Graphics/Scene/BaseSceneObject.h++"

#include "Graphics/Scene/ConcreteObjects/SingleSidePlane.h++"
#include "Graphics/Scene/ConcreteObjects/Box.h++"

#include "Graphics/Scene/ConcreteObjects/Lights/ILight.h++"
#include "Graphics/Scene/ConcreteObjects/Lights/DotLight.h++"
#include "Graphics/Scene/ConcreteObjects/Lights/AmbientLight.h++"

#include "Graphics/Scene/ConcreteObjects/Cameras/ICamera.h++"

#include "Graphics/Screen/Screen.h++"
#include "Graphics/Screen/CameraPyramid.h++"

#include "Graphics/Screen/Render/IRenderer.h++"
#include "Graphics/Screen/Render/Renderer.h++"

#include "Graphics/Screen/Render/RenderableObjects/IRenderable.h++"

#include "Graphics/Screen/Render/RenderableObjects/3D/RenderablePolygon.h++"
#include "Graphics/Screen/Render/RenderableObjects/3D/Renderable3DObject.h++"

#include "Graphics/Screen/Render/RenderableObjects/Lights/IRenderableLight.h++"
#include "Graphics/Screen/Render/RenderableObjects/Lights/RenderableDotLight.h++"

#include "Graphics/Screen/Render/Shaders/IShader.h++"
#include "Graphics/Screen/Render/Shaders/LambertShader.h++"
#include "Graphics/Screen/Render/Shaders/GouraudShader.h++"
#include "Graphics/Screen/Render/Shaders/PhongShader.h++"

#include "Graphics/Materials/IMaterial.h++"
#include "Graphics/Materials/ColorMaterial.h++"

#include "Utils/Interpolator.h++"
#include "Utils/LineInterpolator.h++"

#include "Utils/Containers/DynArray.h++"
#include "Utils/Containers/Matrix.h++"
#include "Utils/Containers/Pair.h++"

#include "GUI/MainWindow.h++"
#include "GUI/ScreenView.h++"
#include "GUI/RightMenu.h++"
#include "GUI/CoordsRow.h++"



int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w(1280, 720, 900, 700);

    w.show();
    return QApplication::exec();

//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return QApplication::exec();
}
