//
// Created by rostam on 27.03.26.
//

#ifndef CGTEA_ALGEBRAICCONNECTIVITY_H
#define CGTEA_ALGEBRAICCONNECTIVITY_H

#include "ReportInterface.h"

class AlgebraicConnectivity : public ReportInterface {
public:
    string report(const Graph& g) override;
    string name() const override { return "Algebraic Connectivity"; }
    string description() const override { return "Second smallest Laplacian eigenvalue (Fiedler value)"; }
    string type() const override { return "double"; }
    string category() const override { return "Spectral"; }
};

#endif //CGTEA_ALGEBRAICCONNECTIVITY_H
