
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_WEB_H
#define CGTEA_WEB_H

#include "GeneratorInterface.h"

class Web : public GeneratorInterface {
public:
    explicit Web() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for (int j = 1; j < k + 1; j++) {
            for (int i = 0; i < n - 1; i++) {
                add_edge(j * n + i, j * n + i + 1, 1, g);
            }
            add_edge(j * n + n - 1, j * n, 1, g);
        }

        for (int j = 0; j < k; j++) {
            for (int i = 0; i < n; i++) {
                add_edge(j * n + i, j * n + i + n, 1, g);
            }
        }

        for (int i = 0; i < n; i++) {
            add_edge(k * n + i, (k + 1) * n, 1, g);
        }

        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);

        std::vector<cgtea_geometry::Point> pos;
        for (int i = k; i >= 0; i--) {
            std::vector<cgtea_geometry::Point> pos_tmp = position_generators::circle(width, height,(k - (i - 1)) * 50.0, n);
            pos.insert(pos.end(), std::make_move_iterator(pos_tmp.begin()), std::make_move_iterator(pos_tmp.end()));
        }
        pos.emplace_back(cgtea_geometry::Point(width, height));
        for_each_v(g, [&](Ver v) { boost::put(boost::vertex_distance, g, v, pos[v]); });
//        Point[] r = new Point[((t+1)*n)+1];
//
//        for(int i=t; i >=0 ;i--) {
//            Point[] p = PositionGenerators.circle((t-(i-1))*10000, 10000, 10000, n);
//            System.arraycopy(p, 0, r, (i * n), n);
//        }
//
//        r[(t+1)*n] = new Point(10000,10000);
        return g;
    }

    string name() const override {
        return "Web Graph";
    }

    string description() const override {
        return "Generate Web Graph";
    }

    string category() const override {
        return "Web Class Graphs";
    };

    string check_parameters() override {
        return "";
    };
};

#endif

