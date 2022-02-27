#ifndef RVLIGHT_H
#define RVLIGHT_H

#include <QVector3D>
#include <QColor>

class RVLight
{
public:
    RVLight();

    const QVector3D &getPosition() const;
    void setPosition(const QVector3D &newPosition);
    const QColor &getAmbient() const;
    void setAmbient(const QColor &newAmbient);
    const QColor &getDiffuse() const;
    void setDiffuse(const QColor &newDiffuse);
    const QColor &getSpecular() const;
    void setSpecular(const QColor &newSpecular);

private:
    QVector3D position;
    QColor ambient;
    QColor diffuse;
    QColor specular;
};

#endif // RVLIGHT_H
