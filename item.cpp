#include "item.h"

Item::Item()
{

}

Ball::Ball(QColor color){
    setScaling(QVector3D(0.01f, 0.01f, 0.01f));
    setMeshFile(QStringLiteral(":/mesh/largesphere.obj"));
    QImage pointColor = QImage(2, 2, QImage::Format_ARGB32);
    pointColor.fill(color);
    setTextureImage(pointColor);
}


Arrow::Arrow(){
    setMeshFile(QStringLiteral(":/mesh/narrowarrow.obj"));
    QImage pointColor = QImage(2, 2, QImage::Format_RGB32);
    pointColor.fill(Qt::black);
    setTextureImage(pointColor);
}

Arrow::Arrow(QVector3D vector): Arrow() {
    setVector(vector);
}

void Arrow::setVector(QVector3D vector){
    /* draw an arrow representing the vector (direction and magnitude) */

    // negative 1 because oddly, the default xyz axis
    // in Q3DSurface has Z axis flipped
    direction = vector.normalized();
    vector.setZ(-vector.z());
    QQuaternion rotation = QQuaternion::rotationTo(
                QVector3D(0, 1, 0), vector);
    setRotation(rotation);
    setMagnitude(vector.length());
}

void Arrow::setMagnitude(const float &magnitude){
    // if magnitude is negative, arrow extends in the other direction
    setScaling(QVector3D(0.1, 0.05 * magnitude, 0.1));
    this->magnitude = magnitude;
}

void Arrow::setPosition(const QVector3D &position){
    /* set position relative to the root of the arrow
     * (instead of the center). Should be called after scaling is done
     */

    QCustom3DItem::setPosition(position + direction * magnitude * kArrowOffset);
}