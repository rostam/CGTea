//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_MAXEIGENVALUE_H
#define CGTEA_MAXEIGENVALUE_H

#include "ReportInterface.h"

class MaxEigenValue : public ReportInterface{
public:
    string report(const Graph& g) override;
    string name() const override {
        return "Maximum eigen value";
    };
    string description() const override {
        return "Maximum eigen value";
    };
    string type() const override {
        return "int";
    };
};

#endif //CGTEA_MAXEIGENVALUE_H
