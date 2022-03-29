#include "GLWidget.h"


#if !defined(__APPLE__)
#include <GL/glu.h>
#endif

#include <iostream>
#include <fstream>
using namespace std;

namespace cagd
{
    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent): QOpenGLWidget(parent)
    {
        _timer = new QTimer(this);
        _timer->setInterval(0);

        connect(_timer,SIGNAL(timeout()),this,SLOT(_animate()));
    }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(width()) / static_cast<double>(height());
        _z_near = 1.0;
        _z_far  = 1000.0;
        _fovy   = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0; _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0; _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        // ...

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            //Creating a white directional light source
            HCoordinate3 direction(0.0,0.0,1.0,0.0);
            Color4 ambient(0.4,0.4,0.4,1.0);
            Color4 diffuse(0.8,0.8,0.8,1.0);
            Color4 specular(1.0,1.0,1.0,1.0);

            _dl = new (nothrow) DirectionalLight(GL_LIGHT0,direction,ambient,diffuse,specular);

            if(!_dl){
                throw Exception("Could not create the directional light object!");
            }

            glEnable(GL_LIGHTING);
            glEnable(GL_NORMALIZE);


            switch(_homework_id){
                case 2:
                    if(!_createAllParametricCurvesAndTheirImages()){
                        throw Exception("Could not create all parametric curves!");
                    }
                    break;
                case 3:
                    _create3DModel();
                     break;
            }


            // create and store your geometry in display lists or vertex buffer objects
            // ...

        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH,GL_NICEST);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

        glEnable(GL_DEPTH_TEST);
        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)

            switch(_homework_id){
                case 2:
                    _renderSelectedParametricCurve();
                    break;
                case 3:
                if(_dl){
                    _dl->Enable();
                    MatFBPearl.Apply();
                    _mouse.Render();
                    _dl->Disable();
                }
                    break;
            }
            // render your geometric objects (you can also use a switch-block)


        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
        glPopMatrix();
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = static_cast<double>(w) / static_cast<double>(h);

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        update();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            update();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            update();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            update();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            update();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            update();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            update();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            update();
        }
    }

    void GLWidget::setParametricCurveIndex(int index){
        _selected_pc=index;
        update();
    }

    void GLWidget::setVisibilityOfTangents(int value){
        if(value)_show_tangents=true;
        else _show_tangents=false;
        update();
    }

    void GLWidget::setVisibilityOfAccelerationVectors(int value){
        if(value)_show_acceleration_vectors=true;
        else _show_acceleration_vectors=false;
        update();
    }

    void GLWidget::setTheNumberOfSubdivisionPointsAlongTheSelectedParametricCurve(int div_point_count){
        try{
            if(_pc[_selected_pc] && _image_of_pc[_selected_pc] && div_point_count != _image_of_pc[_selected_pc]->GetPointCount()){

                //regi kep torlese
                delete _image_of_pc[_selected_pc];

                _image_of_pc[_selected_pc] = _pc[_selected_pc]->GenerateImage(div_point_count,_usage_flag);
                if(!_image_of_pc[_selected_pc]){
                    throw Exception("Failed to recreate the image when changing div_points!");
                }

                if(!_image_of_pc[_selected_pc]->UpdateVertexBufferObjects(_scale,_usage_flag)){
                    throw Exception("Failed to update the vertex buffer when changing div_points!");
                    _destroyAllExistingParametricCurvesAndTheirImages();
                }
            }
            update();
        }
        catch(Exception e){
            cout<<e<<endl;
        }
    }

    void GLWidget::setParametricCurveScale(double value){
        _scale = value;
        if(!_image_of_pc[_selected_pc]->UpdateVertexBufferObjects(_scale,_usage_flag)){
            throw Exception("Failed to update the vertex buffer when changing div_points!");
            _destroyAllExistingParametricCurvesAndTheirImages();
        }
        update();
    }

    bool GLWidget::_createAllParametricCurvesAndTheirImages()
    {
        _pc.ResizeColumns(_pc_count);

        //spiral_on_cone
        RowMatrix<ParametricCurve3::Derivative> spiral(3);
        spiral[0]=spiral_on_cone::d0;
        spiral[1]=spiral_on_cone::d1;
        spiral[2]=spiral_on_cone::d2;

        _pc[0]= nullptr;
        _pc[0] = new (nothrow) ParametricCurve3(spiral,spiral_on_cone::u_min,spiral_on_cone::u_max) ;

        if(!_pc[0]){
            _destroyAllExistingParametricCurvesAndTheirImages();
            throw Exception("Failed creating the parametric curve!");
            return false;
        }

        //torus_knot
        RowMatrix<ParametricCurve3::Derivative> torus(3);
        torus[0]=torus_knot::d0;
        torus[1]=torus_knot::d1;
        torus[2]=torus_knot::d2;

        _pc[1]= nullptr;
        _pc[1]= new (nothrow) ParametricCurve3(torus,torus_knot::u_min,torus_knot::u_max) ;

        if(!_pc[1]){
            _destroyAllExistingParametricCurvesAndTheirImages();
            throw Exception("Failed creating the parametric curve!");
            return false;
        }

        //ellipsoid_curve
        RowMatrix<ParametricCurve3::Derivative> ellip(3);
        ellip[0]=ellipsoid_curve::d0;
        ellip[1]=ellipsoid_curve::d1;
        ellip[2]=ellipsoid_curve::d2;

        _pc[2]= nullptr;
        _pc[2]= new (nothrow) ParametricCurve3(ellip,ellipsoid_curve::u_min,ellipsoid_curve::u_max) ;

        if(!_pc[2]){
            _destroyAllExistingParametricCurvesAndTheirImages();
            throw Exception("Failed creating the parametric curve!");
            return false;
        }

        //cylinder_curve
        RowMatrix<ParametricCurve3::Derivative> cyl(3);
        cyl[0]=cylinder_curve::d0;
        cyl[1]=cylinder_curve::d1;
        cyl[2]=cylinder_curve::d2;

        _pc[3]= nullptr;
        _pc[3]= new (nothrow) ParametricCurve3(cyl,cylinder_curve::u_min,cylinder_curve::u_max) ;

        if(!_pc[3]){
            _destroyAllExistingParametricCurvesAndTheirImages();
            throw Exception("Failed creating the parametric curve!");
            return false;
        }

        //hypocycloid_curve
        RowMatrix<ParametricCurve3::Derivative> hypo(3);
        hypo[0]=hypocycloid_curve::d0;
        hypo[1]=hypocycloid_curve::d1;
        hypo[2]=hypocycloid_curve::d2;

        _pc[4]= nullptr;
        _pc[4]= new (nothrow) ParametricCurve3(hypo,hypocycloid_curve::u_min,hypocycloid_curve::u_max) ;

        if(!_pc[4]){
            _destroyAllExistingParametricCurvesAndTheirImages();
            throw Exception("Failed creating the parametric curve!");
            return false;
        }

        //lissajous_curve
        RowMatrix<ParametricCurve3::Derivative> liss(3);
        liss[0]=lissajous_curve::d0;
        liss[1]=lissajous_curve::d1;
        liss[2]=lissajous_curve::d2;

        _pc[5]= nullptr;
        _pc[5]= new (nothrow) ParametricCurve3(liss,lissajous_curve::u_min,lissajous_curve::u_max) ;

        if(!_pc[5]){
            _destroyAllExistingParametricCurvesAndTheirImages();
            throw Exception("Failed creating the parametric curve!");
            return false;
        }

        //ellipse_curve
        RowMatrix<ParametricCurve3::Derivative> ellipse(3);
        ellipse[0]=ellipse_curve::d0;
        ellipse[1]=ellipse_curve::d1;
        ellipse[2]=ellipse_curve::d2;

        _pc[6]= nullptr;
        _pc[6]= new (nothrow) ParametricCurve3(ellipse,ellipse_curve::u_min,ellipse_curve::u_max) ;

        if(!_pc[6]){
            _destroyAllExistingParametricCurvesAndTheirImages();
            throw Exception("Failed creating the parametric curve!");
            return false;
        }
        _image_of_pc.ResizeColumns(_pc_count);
        for(unsigned int i=0 ;i<_pc_count;i++){
            _image_of_pc[i]=_pc[i]->GenerateImage(_div_point_count,_usage_flag);

            if(!_image_of_pc[i] || !_image_of_pc[i]->UpdateVertexBufferObjects(_scale,_usage_flag)){
                _destroyAllExistingParametricCurvesAndTheirImages();
                return false;
            }
        }

        return true;


    }

    void GLWidget::_destroyAllExistingParametricCurvesAndTheirImages()
    {
        for(unsigned int i=0;i<_pc_count;i++){
            if(_pc[i]){
                delete _pc[i];
                _pc[i]=nullptr;
            }
            if(_image_of_pc[i]){
                delete _image_of_pc[i];
                _image_of_pc[i]=nullptr;
            }
        }
    }


    bool GLWidget::_renderSelectedParametricCurve(){

        if(!_image_of_pc[_selected_pc]){
            return false;
        }

        glColor3f(1.0f,0.0f,0.0f);
        _image_of_pc[_selected_pc]->RenderDerivatives(0,GL_LINE_STRIP);
        glPointSize(5.0f);

        if(_show_tangents){
            glColor3f(0.0f,0.5f,0.0f);
            _image_of_pc[_selected_pc]->RenderDerivatives(1,GL_LINES);
            _image_of_pc[_selected_pc]->RenderDerivatives(1,GL_POINTS);
        }

        if(_show_acceleration_vectors){
            glColor3f(0.1f,0.5f,0.9f);
            _image_of_pc[_selected_pc]->RenderDerivatives(2,GL_LINES);
            _image_of_pc[_selected_pc]->RenderDerivatives(2,GL_POINTS);
        }

        glPointSize(1.0f);
        return true;
    }

    void GLWidget::_privateTestFunction()
    {
        fstream input("input.txt", ios_base::in);
        fstream output("log.txt", ios_base::out);
        DCoordinate3 v;
        Matrix<int>  M,N;

        input >> v >> M;
        M.ResizeRows(4);
        M.ResizeColumns(6);
        M(3,2)=22;

        RowMatrix<int> rM;
        input >> rM;
        if(!M.SetRow(3,rM)){
            output<<"Nem megfelelo a matrix meret!"<<std::endl;
        }

        ColumnMatrix<int> cM;
        input >> cM;
        M.SetColumn(5,cM);

        TriangularMatrix<int> tM;
        input >> tM;
        tM.ResizeRows(6);
        tM(5,5)=99;

        RealSquareMatrix sM;
        input >> sM;

        output << M << std::endl << v <<std::endl << tM<<std::endl<<sM;
        input.close();
        output.close();

    }

    void GLWidget::_create3DModel(){

        if(!_mouse.LoadFromOFF("Models/Characters/gangster.off",GL_TRUE)){
            throw Exception("Could not load the model file!");
        }

        if(!_mouse.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)){
            throw Exception("Could not update vertex buffer objects of the triangulated mesh!");
        }
        _angle = 0.0;
        _timer->start();
    }

    void GLWidget::_animate(){
        GLfloat *vertex = _mouse.MapVertexBuffer(GL_READ_WRITE);
        GLfloat *normal = _mouse.MapNormalBuffer(GL_READ_ONLY);

        _angle += DEG_TO_RADIAN;
        if(_angle >= TWO_PI) _angle -= TWO_PI;

        GLfloat scale = sin(_angle) / 3000.0;
        for(GLuint i=0; i<_mouse.VertexCount(); ++i){
            for(GLuint coordinate=0; coordinate <3; ++coordinate, ++vertex, ++normal){
                *vertex += scale * (*normal);
            }
        }

        _mouse.UnmapVertexBuffer();
        _mouse.UnmapNormalBuffer();
        update();
    }

    GLWidget::~GLWidget(){
        if(_homework_id == 2){
         _destroyAllExistingParametricCurvesAndTheirImages();
        }
        if(_dl){
            delete _dl;
            _dl = nullptr;
        }
     }

}
