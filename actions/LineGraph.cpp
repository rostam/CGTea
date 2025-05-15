//
// Created by rostam on 05.07.20.
//

#include "LineGraph.h"
using namespace  cgtea_geometry;
Graph LineGraph::action(Graph g) {
    Graph g2;
    int cnt = 0;
    for_each_e(g, [&](const Edge& e) {
        Ver v = cnt;
        boost::add_vertex(v, g2);
        EdgeToVertexMapper[e] = v;
        VertexToEdgeMapper[v] = e;
        cnt++;
        Ver src = boost::source(e, g);
        Ver tgt = boost::target(e, g);
        cgtea_geometry::Point srcPoint = boost::get(boost::vertex_distance, g, src);
        cgtea_geometry::Point tgtPoint = boost::get(boost::vertex_distance, g, tgt);
        boost::put(boost::vertex_distance, g2, v, (srcPoint + tgtPoint) / 2);
    });

    for_each_v(g, [&](Ver v) {
        for_each_out_edges(v, g, [&](const Edge& e) {
            for_each_out_edges(v, g, [&](const Edge& e2) {
                if (e != e2) {
                    boost::add_edge(EdgeToVertexMapper[e], EdgeToVertexMapper[e2], 1, g2);
                }
            });
        });
    });
    return g2;
}