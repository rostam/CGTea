//
// Created by rostam on 08.10.19.
//

#ifndef CGTEA_POINT_H
#define CGTEA_POINT_H
namespace cgtea_geometry {
    struct Point {
        Point( double X, double Y ): x(X), y(Y) {};
        double x;
        double y;
    };//Simple Point structure
}

#endif //CGTEA_POINT_H
