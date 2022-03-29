QT += core gui #widgets opengl

# We assume that the compiler is compatible with the C++ 11 standard.
greaterThan(QT_MAJOR_VERSION, 4){
    CONFIG         += c++11
    QT             += widgets
} else {
    QMAKE_CXXFLAGS += -std=c++0x
}

greaterThan(QT_MAJOR_VERSION, 5){
    QT             += openglwidgets
}

win32 {
    message("Windows platform...")

    INCLUDEPATH += $$PWD/Dependencies/Include
    DEPENDPATH += $$PWD/Dependencies/Include

    LIBS += -lopengl32 -lglu32

    CONFIG(release, debug|release): {
        contains(QT_ARCH, i386) {
            message("x86 (i.e., 32-bit) release build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86/" -lglew32
        } else {
            message("x64 (i.e., 64-bit) release build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x64/" -lglew32
        }
    } else: CONFIG(debug, debug|release): {
        contains(QT_ARCH, i386) {
            message("x86 (i.e., 32-bit) debug build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86/" -lglew32
        } else {
            message("x64 (i.e., 64-bit) debug build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x64/" -lglew32
        }
    }

    msvc {
      QMAKE_CXXFLAGS += -openmp -arch:AVX #-D "_CRT_SECURE_NO_WARNINGS"
      QMAKE_CXXFLAGS_RELEASE *= -O2
    }
}

unix: !mac {
    message("Unix/Linux platform...")

    # for GLEW installed into /usr/lib/libGLEW.so or /usr/lib/glew.lib
    LIBS += -lGLEW -lGLU
}

mac {
    message("Macintosh platform...")

    # IMPORTANT: change the letters x, y, z in the next two lines
    # to the corresponding version numbers of the GLEW library
    # which was installed by using the command 'brew install glew'
    INCLUDEPATH += "/usr/local/Cellar/glew/x.y.z/include/"
    LIBS += -L"/usr/local/Cellar/glew/x.y.z/lib/" -lGLEW

    # the OpenGL library has to added as a framework
    LIBS += -framework OpenGL
}


FORMS += \
    GUI/MainWindow.ui \
    GUI/SideWidget.ui

HEADERS += \
    Core/Colors4.h \
    Core/Constants.h \
    Core/CyclicCurves3.h \
    Core/DCoordinates3.h \
    Core/GenericCurves3.h \
    Core/HCoordinates3.h \
    Core/Lights.h \
    Core/LinearCombination3.h \
    Core/Materials.h \
    Core/Matrices.h \
    Core/RealSquareMatrices.h \
    Core/TCoordinates4.h \
    Core/TriangularFaces.h \
    Core/TriangulatedMeshes3.h \
    GUI/GLWidget.h \
    GUI/MainWindow.h \
    GUI/SideWidget.h \
    Core/Exceptions.h \
    Parametric/ParametricCurves3.h \
    Test/TestFunctions.h

SOURCES += \
    Core/Colors4.cpp \
    Core/CyclicCurves3.cpp \
    Core/GenericCurves3.cpp \
    Core/HCoordinates3.cpp \
    Core/Lights.cpp \
    Core/LinearCombination3.cpp \
    Core/Materials.cpp \
    Core/RealSquareMatrices.cpp \
    Core/TCoordinates4.cpp \
    Core/TriangularFaces.cpp \
    Core/TriangulatedMeshes3.cpp \
    GUI/GLWidget.cpp \
    GUI/MainWindow.cpp \
    GUI/SideWidget.cpp \
    Parametric/ParametricCurves3.cpp \
    Test/TestFunctions.cpp \
    main.cpp

DISTFILES += \
    Models/Boats/boat_01.off \
    Models/Boats/boat_02.off \
    Models/Boats/boat_03.off \
    Models/Boats/boat_04.off \
    Models/Boats/boat_05.off \
    Models/Boats/boat_06.off \
    Models/Boats/boat_07.off \
    Models/Building blocks/Benches/bench_01.off \
    Models/Building blocks/Benches/bench_02.off \
    Models/Building blocks/Benches/bench_03.off \
    Models/Building blocks/Benches/bench_04.off \
    Models/Building blocks/Benches/bench_05.off \
    Models/Building blocks/Buildings/building_01.off \
    Models/Building blocks/Buildings/building_02.off \
    Models/Building blocks/Buildings/building_03.off \
    Models/Building blocks/Buildings/building_04.off \
    Models/Building blocks/Buildings/building_05.off \
    Models/Building blocks/Buildings/building_06.off \
    Models/Building blocks/Ornaments/ornament_01.off \
    Models/Building blocks/Ornaments/ornament_02.off \
    Models/Building blocks/Ornaments/ornament_03.off \
    Models/Building blocks/Ornaments/ornament_04.off \
    Models/Building blocks/Ornaments/ornament_05.off \
    Models/Building blocks/Ornaments/ornament_06.off \
    Models/Building blocks/Ornaments/ornament_07.off \
    Models/Building blocks/Ornaments/ornament_08.off \
    Models/Building blocks/Primitives/arc.off \
    Models/Building blocks/Primitives/cone.off \
    Models/Building blocks/Primitives/cube.off \
    Models/Building blocks/Primitives/prism.off \
    Models/Building blocks/Primitives/sphere.off \
    Models/Building blocks/Primitives/square_antiprism.off \
    Models/Building blocks/Stands/stand_01.off \
    Models/Building blocks/Stands/stand_02.off \
    Models/Building blocks/Stands/stand_03.off \
    Models/Building blocks/Stands/stand_04.off \
    Models/Building blocks/Stands/stand_05.off \
    Models/Building blocks/Stands/stand_06.off \
    Models/Building blocks/Statues/Lucy.off \
    Models/Building blocks/Statues/angel.off \
    Models/Building blocks/Statues/dragon.off \
    Models/Building blocks/Statues/liberty.off \
    Models/Building blocks/Street lamps/street_lamp_01.off \
    Models/Building blocks/Street lamps/street_lamp_02.off \
    Models/Building blocks/Street lamps/street_lamp_03.off \
    Models/Building blocks/Trees/tree_01.off \
    Models/Building blocks/Trees/tree_02.off \
    Models/Characters/Spot.off \
    Models/Characters/elephant.off \
    Models/Characters/gangster.off \
    Models/Characters/mouse.off \
    Models/Characters/pig.off \
    Models/Flying objects/Airplanes/airplane_01.off \
    Models/Flying objects/Airplanes/airplane_02.off \
    Models/Flying objects/Airplanes/airplane_03.off \
    Models/Flying objects/Airplanes/airplane_04.off \
    Models/Flying objects/Airplanes/airplane_05.off \
    Models/Flying objects/Airplanes/airplane_06.off \
    Models/Flying objects/Airplanes/airplane_07.off \
    Models/Flying objects/Airplanes/airplane_08.off \
    Models/Flying objects/Airplanes/airplane_09.off \
    Models/Flying objects/Airplanes/airplane_10.off \
    Models/Flying objects/Airplanes/airplane_11.off \
    Models/Flying objects/Airplanes/airplane_12.off \
    Models/Flying objects/Dragon/dragon.off \
    Models/Flying objects/Helicopters/helicopter_01.off \
    Models/Flying objects/Helicopters/helicopter_02.off \
    Models/Flying objects/Helicopters/helicopter_03.off \
    Models/Flying objects/Helicopters/helicopter_04.off \
    Models/Flying objects/Space/Ships/space_ship_01.off \
    Models/Flying objects/Space/Ships/space_ship_02.off \
    Models/Flying objects/Space/Ships/space_ship_03.off \
    Models/Flying objects/Space/Ships/space_ship_04.off \
    Models/Flying objects/Space/Ships/space_ship_05.off \
    Models/Flying objects/Space/Ships/space_ship_06.off \
    Models/Flying objects/Space/Ships/space_ship_07.off \
    Models/Flying objects/Space/Station/station.off \
    Models/Flying objects/Zeppelins/Zeppelin_01.off \
    Models/Flying objects/Zeppelins/Zeppelin_02.off \
    Models/Flying objects/Zeppelins/Zeppelin_03.off
