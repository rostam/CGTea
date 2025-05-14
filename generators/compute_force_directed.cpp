//
// Created by rostam on 07.10.19.
//

#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/gursoy_atun_layout.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <vector>
#include <boost/random/linear_congruential.hpp>
#include "../datatypes.h"
#include "compute_force_directed.h"

typedef topology_type::point_type point_type;

std::vector<cgtea_geometry::Point> compute_force_directed(double x, double y, double width, double height, const Graph &g) {
    int iterations = 150;
    typedef std::vector<point_type> PositionVec;
    PositionVec position_vec(num_vertices(g));
    typedef boost::iterator_property_map<PositionVec::iterator,
            property_map<Graph, boost::vertex_index_t>::type>
            PositionMap;
    PositionMap position(position_vec.begin(), get(boost::vertex_index, g));
    boost::minstd_rand gen;
    topology_type topo(gen, x, y, width, height);
    random_graph_layout(g, position, topo);
    fruchterman_reingold_force_directed_layout(g, position, topo);
    std::vector<cgtea_geometry::Point> ret;
    for_each_v_const(g, [&](Ver v) {
        ret.emplace_back(position[v][0] + 50,position[v][1] + 20);
    });
    return ret;
}
