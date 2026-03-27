//
// Created by rostam on 27.03.26.
//

#ifndef CGTEA_GRAPHENERGY_H
#define CGTEA_GRAPHENERGY_H

#include "ReportInterface.h"

class GraphEnergy : public ReportInterface {
public:
    string report(const Graph& g) override;
    string name() const override { return "Graph Energy"; }
    string description() const override { return "Sum of absolute values of adjacency eigenvalues"; }
    string type() const override { return "double"; }
    string category() const override { return "Spectral"; }
};

#endif //CGTEA_GRAPHENERGY_H
