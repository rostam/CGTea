//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_REPORTINTERFACE_H
#define CGTEA_REPORTINTERFACE_H


#include "../datatypes.h"

class ReportInterface {
public:
    virtual string report(const Graph& g) {};
    virtual string name() {};
    virtual string description() {};
};


#endif //CGTEA_REPORTINTERFACE_H
