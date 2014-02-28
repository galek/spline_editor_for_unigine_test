#include "pointitem.h"
#include <QBrush>

PointItem::PointItem(const QPointF& point, int index) :
    QGraphicsEllipseItem(point.x(),point.y(),8,8), index_(index) {
    setBrush(Qt::red);
    for (int i=0; i<3; i++)
        param_[i] = 0;
}

void PointItem::setParams_slot(double par[]) {
    for (int i=0; i<3; i++)
        param_[i] = par[i];
}