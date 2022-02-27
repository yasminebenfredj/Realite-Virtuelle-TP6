#ifndef RVSKYBOX_H
#define RVSKYBOX_H

#include "rvbody.h"

class RVSkyBox : public RVBody
{
public:
    RVSkyBox();

    // RVBody interface
public:
    void draw() override;
    void initializeBuffer() override;
    void initializeVAO() override;
    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);
};

#endif // RVSKYBOX_H
