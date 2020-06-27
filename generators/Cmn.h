 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_CMN_H
#define CGTEA_CMN_H

#include "GeneratorInterface.h"

class Cmn : public GeneratorInterface {
public:
    explicit Cmn() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        unsigned int &m = k;
        Graph g;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j > m - 2)
                    add_edge(i * m + j, i * m, 1, g);
                else
                    add_edge(i * m + j, i * m + j + 1, 1, g);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i > n - 2)
                    add_edge(i * m + j, j, 1, g);
                else
                    add_edge(i * m + j, (i + 1) * m + j, 1, g);

            }
        }
        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        unsigned int &m = k;
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> centerPoints = position_generators::circle(width, height, 150.0, n);
        for(int i=0;i < n;i++) {
            std::vector<cgtea_geometry::Point> pos2 = position_generators::circle(centerPoints[i].x, centerPoints[i].y,40, m);
            for (int j = 0; j < m; j++) {
                boost::put(boost::vertex_distance, g, i * m + j, pos2[j]);
            }
        }
        return g;
    }

    string name() const override {
        return "Cm * Cn";
    }

    string description() const override {
        return "Generate Cm*Cn";
    }

    string category() const override {
        return "General Graphs";
    };

    string check_parameters() override {
        return "";
    };
};

#endif

