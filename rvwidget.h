#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QTime>

#include "rvbody.h"
#include "rvcamera.h"
#include "rvcube.h"
#include "rvplane.h"
#include "rvsphere.h"
#include "rvplanet.h"
#include "rvtorus.h"
#include "rvtexcube.h"
#include "rvdice.h"
#include "rvscene.h"
#include "rvsphericalcamera.h"
#include "rvskybox.h"
#include "rvlight.h"
#include "rvcurve.h"
#include "rvhelix.h"
#include "rvmodel.h"


class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT


public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget();

    // Attributs pour le rendu
private:
    RVBody* body;
    RVBody* plane;
    RVBody* world;
    RVBody* torus;

    RVSkyBox* skybox;
    RVScene scene;
    RVCamera* camera;

    RVLight* light;

    RVBody* avion;

    QTime startTime;
    QTime lastTime;
    RVCurve* trajectory;

    QTimer* timer;
    float angleY;
    bool animationOn = false;
    float angleX;
    QPointF oldPos;

protected slots:
    void update();

public slots:
    void startAnimation();
    void changeFov(int);
    void changeOpacity(int);
    void changeSize(int value);
    void changeSaturation(int value);
    void changeCulling();
    void changeWireframe();

    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
};
#endif // RVWIDGET_H
