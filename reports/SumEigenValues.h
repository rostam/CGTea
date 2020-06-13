//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_SUMEIGENVALUES_H
#define CGTEA_SUMEIGENVALUES_H

#include "ReportInterface.h"
#include "MaxEigenValue.h"

class SumEigenValues : public ReportInterface{
public:
    string report(const Graph& g) override {
        std::tuple<double,double,double> t = MaxEigenValue::eigen_values(g);
        return std::to_string(std::get<2>(t));
    };
    string name() const override {
        return "Sum of eigen values";
    };
    string description() const  override {
        return "Sum of eigen values";
    };
    string type() const override {
        return "int";
    };
};

#endif //CGTEA_SUMEIGENVALUES_H
