//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_MINEIGENVALUE_H
#define CGTEA_MINEIGENVALUE_H

#include "ReportInterface.h"
#include "MaxEigenValue.h"

class MinEigenValue : public ReportInterface{
public:
    string report(const Graph& g) override;
    string name() const override {
        return "Minimum eigen value";
    };
    string description() const override {
        return "Minimum eigen value";
    };
    string type() const override {
        return "int";
    };
};

#endif //CGTEA_MINEIGENVALUE_H
