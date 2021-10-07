cmake_minimum_required(VERSION 3.20)
project(GViewer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(
        GViewer
        main.cpp
        Utils/Containers/DynArray.h++
        Utils/BaseObject.h++
        Utils/Containers/Matrix.h++
        Exceptions/Exception.h++
        Exceptions/Memory.h++
        Exceptions/Range.h++
        Exceptions/Math.h++
        Geometry/Basics/Point2.h++
        Geometry/Basics/Point3.h++
        Geometry/Basics/Angle.h++
        Geometry/Basics/Vector.h++
        Graphics/Basics/ShadingCoefficients.h++
        Graphics/Basics/Vertex.h++
        Graphics/Scene/ISceneObject.h++
        Geometry/Utils/ScaleFactor.h++
        Geometry/Utils/AngleSystem.h++
        Graphics/Basics/RGBA.h++
        Graphics/Screen/Screen.h++
        Exceptions/Graphics.h++
        Graphics/Basics/Polygon.h++
        Geometry/Transform/PointTransformer.h++
        Graphics/Screen/Renderer.h++
        Graphics/Screen/IRenderer.h++
        Settings/Settings.h++
        Graphics/Scene/CompositeSceneObject.h++
        Utils/Containers/Pair.h++ Graphics/Scene/BaseSceneObject.h++ Graphics/Scene/ConcreteObjects/SingleSidePlane.h++ Graphics/Materials/IMaterial.h++ Graphics/Materials/ColorMaterial.h++ Graphics/Scene/ConcreteObjects/Box.h++)

target_link_libraries(GViewer
        PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

