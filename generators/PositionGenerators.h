/**
 * User: Ali
 */

#include <vector>
#include <cmath>
#include "point.h"

class position_generators {
//    public static Point[] line(int xOffset, int yOffset, int w, int h, int n) {
//        Point[] ret = new Point[n];
//        int dx = w / n;
//        int dy = h / n;
//        for (int i = 0; i < n; i++) {
//            ret[i] = new Point(xOffset + i * dx, yOffset + i * dy);
//        }
//        return ret;
//    }
//
//    public static GPoint[] convert(Point[] ps) {
//        GPoint[] ret = new GPoint[ps.length];
//        for(int i=0;i<ps.length;i++) {
//            ret[i] = new GPoint(ps[i].x,ps[i].y);
//        }
//        return ret;
//    }

public:

    static std::vector<cgtea_geometry::Point> circle(double w, double h, double r, unsigned int n) {
        std::vector<cgtea_geometry::Point> ret;
        for(unsigned int i=0;i < n;i++) {
            double deg = 2 * M_PI / n * i;
            ret.emplace_back( w + r*cos( deg ), h + r*sin( deg ) );
        }
        return ret;
    }
//
//    static std::vector<std::pair<double, double>> circle(int xOffset, int yOffset, int w, int h, unsigned int n) {
//        std::vector<std::pair<double, double>> ret;
//        w = w / 2;
//        h = h / 2;
//        w -= xOffset;
//        h -= yOffset;
//        for (unsigned int i = 0; i < n; i++) {
//            double deg = 2 * M_PI / n * i;
//            double x = sin(deg);
//            double y = cos(deg);
//            x *= w;
//            y *= h;
//            x += w;
//            y += h;
//            x += xOffset;
//            y += yOffset;
//            ret.push_back(std::pair((int) x, (int) y));
//        }
//        return ret;
//    }

//
//    public static Point[] circle(int xOffset, int yOffset, int w, int h, int n, double degree) {
//        Point[] ret = new Point[n];
//        w = w / 2;
//        h = h / 2;
//        w -= xOffset;
//        h -= yOffset;
//        for (int i = 0; i < n; i++) {
//            double deg = 2 * Math.PI / n * i;
//            deg += degree;
//            double x = Math.sin(deg);
//            double y = Math.cos(deg);
//            x *= w;
//            y *= h;
//            x += w;
//            y += h;
//            x += xOffset;
//            y += yOffset;
//            ret[i] = new Point((int) x, (int) y);
//        }
//        return ret;
//    }
//
    static std::vector<std::pair<double, double>>
    shift(std::vector<std::pair<double, double>> input, int xOffset, int yOffset) {
        for (std::pair<double, double> p : input) {
            p.first += xOffset;
            p.second += yOffset;
        }
        return input;
    }
//
//    static std::vector<std::pair<double, double>> circle(int r, int x, int y, unsigned int n) {
//        std::vector<std::pair<double, double>> ret = circle(0, 0, r, r, n);
//        shift(ret, x, y);
//        return ret;
//    }
//
//    public static Point[] rotate(Point[] input, double degree) {
//
//        for (Point p : input) {
//            int x = (int) (p.x * Math.cos(degree) - p.y * Math.sin(degree));
//            int y = (int) (p.x * Math.sin(degree) + p.y * Math.cos(degree));
//            p.x = x;p.y = y;
//        }
//
//        return input;
//    }
//
//    public static GPoint rotate(GPoint input, double degree) {
//
//        double x =  (input.x * Math.cos(degree) - input.y * Math.sin(degree));
//        double y =  (input.x * Math.sin(degree) + input.y * Math.cos(degree));
//        input.x = x;input.y = y;
//        return input;
//    }
};
