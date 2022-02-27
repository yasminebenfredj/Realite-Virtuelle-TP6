#include "rvsphericalcamera.h"

RVSphericalCamera::RVSphericalCamera()
{
    rho = 20;
    theta = 0;
    phi = M_PI_4;
    updatePosition();
}

void RVSphericalCamera::updatePosition()
{
    QVector3D cible = this->getTarget();
    float xcamera = cible.x() + rho*qCos(phi)*qCos(theta);
    float ycamera = cible.y() + rho*qSin(phi);
    float zcamera = cible.z() + rho*qCos(phi)*qSin(theta);
    this->setPosition(QVector3D(xcamera, ycamera, zcamera));
}

float RVSphericalCamera::getPhi() const
{
    return phi;
}

void RVSphericalCamera::setPhi(float newPhi)
{
    phi = qMin(M_PI_2, qMax(newPhi, -M_PI_2));
    updatePosition();
}

float RVSphericalCamera::getTheta() const
{
    return theta;
}

void RVSphericalCamera::setTheta(float newTheta)
{
    theta = newTheta;
    updatePosition();
}

float RVSphericalCamera::getRho() const
{
    return rho;
}

void RVSphericalCamera::setRho(float newRho)
{
    rho = qMax(newRho, 0.1);
    updatePosition();
}
