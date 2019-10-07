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
            std::vector<std::pair<double,double>> pos = position_generators::circle(200,500,500,n);
            int i=0;
            for_each_v(g, [&](Ver v) {
                boost::put(boost::vertex_distance, g, v, pos[i]);
                i++;
            });
            PositionVec position_vec(num_vertices(g));
            PositionMap position(position_vec.begin(), boost::get(boost::vertex_index, g));
            minstd_rand gen;
            double width = 500;
            double height = 500;

//            int iterations = 10;
//            typedef boost::rectangle_topology<> topology_type;
            //boost::random_graph_layout(g, position, boost::square_topology<minstd_rand>());
//            topology_type topo(gen, -width/2, -height/2, width/2, height/2);
//            boost::fruchterman_reingold_force_directed_layout(g, position,boost::square_topology<minstd_rand>());//cooling(progress_cooling(iterations)));
//           ` graph_traits<Graph>::vertex_iterator vi, vi_end;
//            for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
//                std::cout <<
//                          << position[*vi][0] << '\t' << position[*vi][1] << std::endl;
//            }
//            return 0;``
//
//            int i=0;
            for_each_v(g, [&](Ver v) {
//                cerr << v << endl;
//                cerr << position[v][0] << '\t' << position[v][1] << endl;
//                boost::put(boost::vertex_distance, g, v, std::pair<double,double>(position[v][0],position[v][1]));
            });
//                 boost::convex_topology<2>::point res_p = position[i];
//                 double px =  0;//res_p.operator[](0);
//                 double py =  px;//res_p.operator[](1);
//                 cout << " " << px << " " << py << "\n";
//                 boost::put(boost::vertex_distance, g, v, std::pair<double,double>(px,py));
//                 i++;
//            });


        }
        return g;
    }
};

#endif
