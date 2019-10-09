//
// Created by rostam on 07.10.19.
//

#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <boost/random/linear_congruential.hpp>
#include <boost/progress.hpp>
#include <boost/shared_ptr.hpp>
#include "datatypes.h"
#include "compute_force_directed.h"

std::vector<cgtea_geometry::Point> compute_force_directed(double width, double height, const Graph &g) {
    int iterations = 100;
    typedef std::vector<point_type> PositionVec;
    PositionVec position_vec(num_vertices(g));
    typedef boost::iterator_property_map<PositionVec::iterator,
            property_map<Graph, boost::vertex_index_t>::type>
            PositionMap;
    PositionMap position(position_vec.begin(), get(boost::vertex_index, g));
    boost::minstd_rand gen;
    topology_type topo(gen, 0, 0, width, height);
//    random_graph_layout(g, position, topo);
    fruchterman_reingold_force_directed_layout(g, position, topo);
    std::vector<cgtea_geometry::Point> ret;
    for_each_v_const(g, [&](Ver v) {
//        std::cerr << position[v][0] << " " << position[v][1] << endl;
        ret.emplace_back(cgtea_geometry::Point(position[v][0],position[v][1]));
    });
    return ret;
//    graph_traits<Graph>::vertex_iterator vi, vi_end;
//    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
//        std::cerr << *vi << "  : ";
//        std::cerr << position[*vi][0] << " " << position[*vi][1] << endl;
//        boost::put(boost::vertex_distance, g, *vi, pair(position[*vi][0], position[*vi][1]));
//    }
}
