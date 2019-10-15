//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_MYAPP_H
#define CGTEA_MYAPP_H

#include "BasicDrawPane.h"

class MyApp: public wxApp {
    BasicDrawPane *drawPane;
public:
    virtual bool OnInit();
};

#endif //CGTEA_MYAPP_H
