#ifndef RVSCENE_H
#define RVSCENE_H

#include <QList>

#include "rvbody.h"
#include "rvcamera.h"

class RVScene : public QList<RVBody*>
{
public:
    RVScene();

    void setCamera(RVCamera *newCamera);
    void translate(QVector3D vec);
    void rotate(float angle, QVector3D axis);
    void draw();
    void update(float time, bool relative = true);

private:
    RVCamera* camera;
};

#endif // RVSCENE_H
