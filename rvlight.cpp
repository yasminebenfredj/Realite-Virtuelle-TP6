#include "rvlight.h"

RVLight::RVLight()
{
    ambient = QColor(100, 100, 100);
    diffuse = QColor(255, 255, 255);
    specular = QColor(255, 255, 255);
    position = QVector3D(10, 0, 10);
}

const QVector3D &RVLight::getPosition() const
{
    return position;
}

void RVLight::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}

const QColor &RVLight::getAmbient() const
{
    return ambient;
}

void RVLight::setAmbient(const QColor &newAmbient)
{
    ambient = newAmbient;
}

const QColor &RVLight::getDiffuse() const
{
    return diffuse;
}

void RVLight::setDiffuse(const QColor &newDiffuse)
{
    diffuse = newDiffuse;
}

const QColor &RVLight::getSpecular() const
{
    return specular;
}

void RVLight::setSpecular(const QColor &newSpecular)
{
    specular = newSpecular;
}
