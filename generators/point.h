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
}

#endif //CGTEA_POINT_H
