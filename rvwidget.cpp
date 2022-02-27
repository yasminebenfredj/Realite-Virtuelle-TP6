#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions(), scene()
{
    timer = new QTimer();
    angleY = 5;

    grabKeyboard();
}

RVWidget::~RVWidget()
{
}

void RVWidget::update()
{
    QTime currentTime = QTime::currentTime();
    float t = lastTime.msecsTo(currentTime);
    lastTime = currentTime;
    float t2 = startTime.msecsTo(currentTime);

    if (animationOn) {
        scene.update(t, true);
        world->setPosition(trajectory->pos(t2*0.001));
    }

    QOpenGLWidget::update();
}

void RVWidget::changeFov(int fov)
{
    camera->setFov(fov);
    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    animationOn = !animationOn;
    if (animationOn)
    {
        lastTime = QTime::currentTime();
        startTime = QTime::currentTime();
    }
}

void RVWidget::changeOpacity(int val)
{
    torus->setOpacity(val * 0.01f);
    QOpenGLWidget::update();
}

void RVWidget::changeSize(int value)
{
    body->setScale(value*0.1f);
    QOpenGLWidget::update();
}

void RVWidget::changeSaturation(int value)
{
    int gris = (int)(2.55f * value);
    plane->setGlobalColor(QColor(gris, gris, gris));
    QOpenGLWidget::update();
}

void RVWidget::changeCulling()
{
    bool culling = !body->getCulling();
    body->setCulling(culling);
    QOpenGLWidget::update();
}

void RVWidget::changeWireframe()
{
    bool wireframe = !world->getWireframe();
    world->setWireframe(wireframe);
    QOpenGLWidget::update();
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    camera = new RVSphericalCamera();
    camera->setFov(45.0f);
    //camera->setPosition(QVector3D(0, 8, 8));
    camera->setTarget(QVector3D(0, 0, 0));
    camera->setZMin(8);
    camera->setZMax(250);

    light = new RVLight();

    //body = new RVTexCube();
    //body = new RVCube();
    body = new RVDice();
    body->setCamera(camera);
    body->setPosition(QVector3D(0, 4, 0));
    body->setTexture(":/textures/dice_texture.jpg", false, false);
    body->setLight(light);
    body->initialize();

    RVBody* c = new RVTexCube();
    c->setCamera(camera);
    c->setPosition(QVector3D(-4, 4, 0));
    c->setLight(light);
    c->setTexture(":/textures/polytech_logo.jpg", false, false);
    c->initialize();
    scene.append(c);

    c = new RVCube();
    c->setCamera(camera);
    c->setPosition(QVector3D(4, 4, 0));
    c->setLight(light);
    c->initialize();
    scene.append(c);

    plane = new RVPlane(40, 40);
    plane->setCamera(camera);
    plane->setPosition(QVector3D(0, -4, 0));
    plane->setTexture(":/textures/wood.png");
    plane->setLight(light);
    plane->initialize();

    world = new RVSphere(2.0);
    world->setCamera(camera);
    world->setPosition(QVector3D(0, -2, 0));
    world->setTexture(":/textures/2k_earth_daymap.jpg", true, true);
    world->setLight(light);
    world->initialize();

    torus = new RVTorus();
    torus->setCamera(camera);
    torus->setPosition(QVector3D(0, 2, 0));
    torus->setFSFileName(":/shaders/FS_lit_checker.fsh");
    torus->setLight(light);
    torus->initialize();

    avion = new RVModel("C:/Users/Jasmine/Desktop/Master 2/B2/Realite virtuelle/Tuto6/model/GeeBee2.x");
    avion->setCamera(camera);
    avion->setLight(light);
    avion->initialize();
    avion->translate(QVector3D(0,1.5,0));

    trajectory = new RVHelix();
    trajectory->setCamera(camera);
    trajectory->setPosition(QVector3D(0, 0, 0));
    trajectory->setScale(2);
    trajectory->initialize();

    scene.append(body);
    scene.append(plane);
    scene.append(world);
    //scene.append(torus);
    //scene.append(trajectory);
    scene.append(avion);
    scene.setCamera(camera);

    skybox = new RVSkyBox();
    skybox->setCubeTexture(":/textures/skybox/left.jpg",
                           ":/textures/skybox/right.jpg",
                           ":/textures/skybox/front.jpg",
                           ":/textures/skybox/back.jpg",
                           ":/textures/skybox/top.jpg",
                           ":/textures/skybox/bottom.jpg"
                           );
    skybox->setCamera(camera);
    skybox->setPosition(QVector3D());
    skybox->setScale(80);
    skybox->initialize();
    scene.append(skybox);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = ((float)w)/h;
    camera->setAspect(aspect);
    glViewport(0, 0, w, h);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene.draw();
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->position();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = (event->position().x() - oldPos.x()) / width();
    float dy = (event->position().y() - oldPos.y()) / height();
    if (event->buttons() & Qt::LeftButton) {
        RVSphericalCamera* cam = (RVSphericalCamera*)camera;
        cam->setPhi(cam->getPhi() + dy);
        cam->setTheta(cam->getTheta() + dx);
        //float xAngle = 180 * dy;
        //float yAngle = 180 * dx;
        //body->rotate(yAngle, QVector3D(0, 1, 0));
        //body->rotate(xAngle, QVector3D(1, 0, 0));
        QOpenGLWidget::update();
    }
    oldPos = event->pos();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = camera->getPosition();
    float delta = 0.2f;
    switch (event->key())
    {
    case Qt::Key_Left:
        camPos.setX(camPos.x() - delta);
        break;
    case Qt::Key_Right:
        camPos.setX(camPos.x() + delta);
        break;
    case Qt::Key_Up:
        camPos.setY(camPos.y() + delta);
        break;
    case Qt::Key_Down:
        camPos.setY(camPos.y() - delta);
        break;
    }
    camera->setPosition(camPos);
    QOpenGLWidget::update();
}


void RVWidget::wheelEvent(QWheelEvent *event)
{
    RVSphericalCamera* cam = (RVSphericalCamera*) camera;
    float rho = cam->getRho() + event->angleDelta().y()*0.1f;
    cam->setRho(rho);
    QOpenGLWidget::update();
}
