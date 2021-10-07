//#include <QApplication>
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

#include "Graphics/Screen/Screen.h++"
#include "Graphics/Screen/IRenderer.h++"
#include "Graphics/Screen/Renderer.h++"

#include "Graphics/Materials/IMaterial.h++"
#include "Graphics/Materials/ColorMaterial.h++"

#include "Utils/Containers/DynArray.h++"
#include "Utils/Containers/Matrix.h++"
#include "Utils/Containers/Pair.h++"


int main(int argc, char *argv[]) {

//    DynArray<std::unique_ptr<ISceneObject>> vec;
//    auto c = CompositeSceneObject();
//    std::unique_ptr<ISceneObject> p = std::unique_ptr<CompositeSceneObject>(new CompositeSceneObject());
//    vec.append(std::move(p));


    return 0;

//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return QApplication::exec();
}
