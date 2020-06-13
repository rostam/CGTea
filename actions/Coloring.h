//
// Created by rostam on 18.10.19.
//

#ifndef CGTEA_COLORING_H
#define CGTEA_COLORING_H

#include "ActionInterface.h"

class Coloring : public ActionInterface {
    Graph action(Graph g) override {
        typedef graph_traits<Graph>::vertices_size_type vertices_size_type;
        typedef property_map<Graph, boost::vertex_index_t>::const_type vertex_index_map;
        std::vector<vertices_size_type> color_vec(num_vertices(g));
        boost::iterator_property_map<vertices_size_type*, vertex_index_map> color(&color_vec.front(), get(boost::vertex_index, g));
        auto num_colors = boost::sequential_vertex_coloring(g, color);
        for_each_v_const(g, [&](Ver v){
           boost::put(vertex_color, g, v, color[v]);
        });
        cerr << num_colors;
        return g;
    }

    string name() const override {
        return "Heuristic Coloring";
    }

    string description() const override {
        return "Graph Heuristic Coloring.";
    }

};


#endif //CGTEA_COLORING_H
