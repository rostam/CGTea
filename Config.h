#ifndef CGTEA_CONFIG_H
#define CGTEA_CONFIG_H

#include <wx/config.h>
#include "const_values.h"

class Config {
public:
    static void SaveVertexShape(VertexShape shape) {
        wxConfig::Get()->Write("/Settings/VertexShape", static_cast<int>(shape));
    }

    static void SaveEdgeShape(EdgeShape shape) {
        wxConfig::Get()->Write("/Settings/EdgeShape", static_cast<int>(shape));
    }

    static VertexShape LoadVertexShape() {
        int shape;
        if (wxConfig::Get()->Read("/Settings/VertexShape", &shape)) {
            return static_cast<VertexShape>(shape);
        }
        return VertexShape::Circle; // default
    }

    static EdgeShape LoadEdgeShape() {
        int shape;
        if (wxConfig::Get()->Read("/Settings/EdgeShape", &shape)) {
            return static_cast<EdgeShape>(shape);
        }
        return EdgeShape::Line; // default
    }
};

#endif //CGTEA_CONFIG_H