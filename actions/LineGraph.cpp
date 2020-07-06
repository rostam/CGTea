//
// Created by rostam on 05.07.20.
//

#include "LineGraph.h"

Graph LineGraph::action(Graph g) {
    Graph g2;
    int cnt = 0;
    for_each_e(g, [&](Edge e) {
        Ver v = cnt;
        boost::add_vertex(v, g2);
        EdgeToVertexMapper[e] = v;
        VertexToEdgeMapper[v] = e;
        cnt++;
//        Vertex v = new Vertex();
//        v.setLabel(e.getLabel());
//        GPoint loc = new GPoint(e.source.getLocation());
//        loc.add(e.target.getLocation());
//        loc.multiply(0.5);
//        loc.add(e.getCurveControlPoint());
//        v.setLocation(loc);
//        e.getProp().obj = v;
//        v.getProp().obj = e;
//        g2.insertVertex(v);
    });

    for_each_v(g, [&](Ver v) {
        for_each_out_edges(v, g, [&](Edge e) {
            for_each_out_edges(v, g, [&](Edge e2) {
                if (e != e2) {
                    boost::add_edge(EdgeToVertexMapper[e], EdgeToVertexMapper[e2], 1, g2);
                }
            });
        });
    });
    return g2;
}