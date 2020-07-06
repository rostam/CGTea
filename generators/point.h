//
// Created by rostam on 08.10.19.
//

#ifndef CGTEA_POINT_H
#define CGTEA_POINT_H
namespace cgtea_geometry {
    struct Point {
        Point(): x(0), y(0) {};
        Point( double X, double Y ): x(X), y(Y) {};
        double x;
        double y;
    };

    static Point operator+(const Point& p1, const Point& p2) {
         return Point(p1.x + p2.x, p1.y + p2.y);
    }

    static Point operator/(const Point& p1, double value) {
        return Point(p1.x/2, p1.y/2);
    }
}

#endif //CGTEA_POINT_H
