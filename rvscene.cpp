#include "rvscene.h"

RVScene::RVScene()
    :camera()
{
}

void RVScene::setCamera(RVCamera *newCamera)
{
    camera = newCamera;
    foreach (RVBody* body, *this) {
        body->setCamera(camera);
    }
}

void RVScene::translate(QVector3D vec)
{
    foreach (RVBody* body, *this) {
        body->translate(vec);
    }
}

void RVScene::rotate(float angle, QVector3D axis)
{
    foreach (RVBody* body, *this) {
        body->rotate(angle, axis);
    }
}

void RVScene::draw()
{
    foreach (RVBody* body, *this) {
        body->draw();
    }
}

void RVScene::update(float time, bool relative)
{
    foreach (RVBody* body, *this) {
        body->update(time, relative);
    }
}
