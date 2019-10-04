/**
 * Created by rostami on 28.06.17.
 */
#ifndef EXACT_COLORING_CYCLE_H
#define EXACT_COLORING_CYCLE_H

#include "GeneratorInterface.h"
#include "boost/graph/fruchterman_reingold.hpp"
#include "boost/graph/random_layout.hpp"
#include "boost/graph/topology.hpp"

class Cycle : public GeneratorInterface {
public:
    Cycle(int n) : GeneratorInterface(n) {};
    Graph generate(bool fill_positions = false) {
        Graph g;
        for (int i = 0; i < n; i++)
            add_edge(i, ((i + 1) % n),g);
        if(fill_positions) {
//            std::vector<std::pair<double,double>> pos = position_generators::circle(200,500,500,n);
//            int i=0;
//            for_each_v(g, [&](Ver v) {
//                boost::put(boost::vertex_distance, g, v, pos[i]);
//                i++;
//            });
            PositionVec position_vec(num_vertices(g));
            PositionMap position(position_vec.begin(), boost::get(boost::vertex_index, g));
            minstd_rand gen;
            double width = 500;
            double height = 500;

            int iterations = 10;

            //boost::random_graph_layout(g, position, boost::square_topology<minstd_rand>());
            boost::fruchterman_reingold_force_directed_layout(g, position,boost::square_topology<minstd_rand>());//cooling(progress_cooling(iterations)));
            int i=0;
            for_each_v(g, [&](Ver v) {
                cerr<<i;
                 boost::convex_topology<2>::point res_p = position[i];
                 double px =  0;//res_p.operator[](0);
                 double py =  px;//res_p.operator[](1);
                 cout << " " << px << " " << py << "\n";
                 boost::put(boost::vertex_distance, g, v, std::pair<double,double>(px,py));
                 i++;
            });


        }
        return g;
    }
};

#endif
