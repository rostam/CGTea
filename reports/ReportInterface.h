//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_REPORTINTERFACE_H
#define CGTEA_REPORTINTERFACE_H


#include "../datatypes.h"

class ReportInterface {
public:
    virtual string report(const Graph& g) = 0;
    [[nodiscard]] virtual string name() const = 0;
    [[nodiscard]] virtual string description() const = 0;
    [[nodiscard]] virtual string type() const = 0 ;
    [[nodiscard]] virtual string category() const {
        return "General";
    };
};


#endif //CGTEA_REPORTINTERFACE_H
