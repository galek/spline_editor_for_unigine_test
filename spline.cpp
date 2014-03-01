#include "spline.h"
#include "pointitem.h"

Spline::Spline(const QPointF &prev, const QPointF &cur, const QPointF &next, const PointItem *curitem, const PointItem *nextitem) : cur_(cur), next_(next), bSplineBuilded(0) {
    d1_=0.5*(1-curitem->tension())*((1+curitem->bias())*(1-curitem->continuity())*(cur-prev)+ (1-curitem->bias())*(1+curitem->continuity())*(next-cur));
    d2_=0.5*(1-nextitem->tension())*((1+nextitem->bias())*(1+nextitem->continuity())*(cur-prev)+ (1-nextitem->bias())*(1-nextitem->continuity())*(next-cur));
}

QPointF interpolate(double t, const QPointF& p1, const QPointF& p2, const QPointF& d1, const QPointF& d2) {
    return p1 * (2*t*t*t - 3*t*t + 1) + d1 * (t*t*t - 2*t*t + t) + p2 * (-2*t*t*t + 3*t*t) + d2 * (t*t*t - t*t);
}

const int MAX_POINTS = 50;
QList<QPointF> Spline::getPoints()
{
    if (!bSplineBuilded) {
        for (int k=0; k<MAX_POINTS; k++)
        {
            double t = (double)k / (double)(MAX_POINTS-1);
            list_.append(interpolate(t,cur_,next_,d1_,d2_));
        }
    }
    bSplineBuilded = 1;
    return list_;
}
