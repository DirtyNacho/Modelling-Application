#pragma once

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <Core/Exceptions.h>
#include "Parametric/ParametricCurves3.h"
#include "Test/TestFunctions.h"
#include "Core/RealSquareMatrices.h"
#include "Core/TriangulatedMeshes3.h"
#include <QTimer>
#include "Core/Materials.h"
#include "Core/Constants.h"
#include "Core/Lights.h"

namespace cagd
{
    class GLWidget: public QOpenGLWidget
    {
        Q_OBJECT

    private:

        // variables defining the projection matrix
        double       _aspect;            // aspect ratio of the rendering window
        double       _fovy;              // field of view in direction y
        double       _z_near, _z_far;    // distance of near and far clipping planes

        // variables defining the model-view matrix
        double       _eye[3], _center[3], _up[3];

        // variables needed by transformations
        int         _angle_x, _angle_y, _angle_z;
        double      _zoom;
        double      _trans_x, _trans_y, _trans_z;

        // your other declarations
        // declarations for rendering parametric curves
        GLuint _pc_count = 7;
        RowMatrix<ParametricCurve3*> _pc;
        RowMatrix<GenericCurve3*> _image_of_pc;
        int _selected_pc = 0;
        bool _show_tangents=false;
        bool _show_acceleration_vectors=false;
        GLuint _div_point_count = 200;
        GLenum _usage_flag = GL_STATIC_DRAW;
        double _scale = 1.0;

        bool _createAllParametricCurvesAndTheirImages();
        void _destroyAllExistingParametricCurvesAndTheirImages();
        bool _renderSelectedParametricCurve();

        //declarations for rendering 3D Models
        QTimer *_timer;
        GLfloat _angle;
        TriangulatedMesh3 _mouse;
        void _create3DModel();
        DirectionalLight *_dl = nullptr;


        // used for homework test cases
        int _homework_id = 3;
        void _privateTestFunction();

    public:
        // special and default constructor
        // the format specifies the properties of the rendering window
        GLWidget(QWidget* parent = 0);

        // redeclared virtual functions
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
        virtual ~GLWidget();

    public slots:
        // public event handling methods/slots
        void set_angle_x(int value);
        void set_angle_y(int value);
        void set_angle_z(int value);

        void set_zoom_factor(double value);

        void set_trans_x(double value);
        void set_trans_y(double value);
        void set_trans_z(double value);

        //slots for parametric curves
        void setParametricCurveIndex(int index);
        void setVisibilityOfTangents(int visibility);
        void setVisibilityOfAccelerationVectors(int visibility);
        void setTheNumberOfSubdivisionPointsAlongTheSelectedParametricCurve(int div_point_count);
        void setParametricCurveScale(double scale);

        //slots for animating 3D Models
        void _animate();
    };
}
