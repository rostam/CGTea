//
// Created by rostam on 27.03.26.
//

#ifndef CGTEA_RADIUS_H
#define CGTEA_RADIUS_H

#include "ReportInterface.h"

class GraphRadius : public ReportInterface {
public:
    string report(const Graph& g) override;
    string name() const override { return "Graph Radius"; }
    string description() const override { return "Minimum eccentricity over all vertices"; }
    string type() const override { return "int"; }
    string category() const override { return "General"; }
};

#endif //CGTEA_RADIUS_H
