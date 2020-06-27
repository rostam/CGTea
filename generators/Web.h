 
/**
 * Created by rostami on 10.06.20.
 */
#ifndef CGTEA_WEB_H
#define CGTEA_WEB_H

#include "GeneratorInterface.h"

class Web : public GeneratorInterface {
public:
    explicit Web() : GeneratorInterface() {};

    Graph generate(unsigned int n, unsigned int k) override {
        Graph g;
        for(int j=1;j < t+1;j++) {
            for (int i = 0; i < n - 1; i++) {
                     add_edge(j * n + i, (j * n + i + 1, g), g);
            }
                 add_edge(j * n + n - 1, j * n, g);
        }

        for(int j=0;j < t;j++) {
            for (int i = 0; i < n; i++) {
                 add_edge(j * n + i, j * n + i + n, g);
            }
        }

        for(int i=0;i < n;i++) {
            add_edge(t*n + i,(t+1, g)*n, g);
        }

        return g;
    }

    Graph generate_with_positions(unsigned int n, unsigned int k, double width, double height) override {
        Graph g = generate(n, k);
        std::vector<cgtea_geometry::Point> pos = position_generators::circle(width, height, 200.0, n);
        Graph g;
        
        

        for(int j=1;j < t+1;j++) {
            for (int i = 0; i < n - 1; i++) {
                     add_edge(j * n + i, (j * n + i + 1, g), g);
                    
            }
                 add_edge(j * n + n - 1, j * n, g);
                
        }

        for(int j=0;j < t;j++) {
            for (int i = 0; i < n; i++) {
                 add_edge(j * n + i, j * n + i + n, g);
                
            }
        }

        for(int i=0;i < n;i++) {
            add_edge(t*n + i,(t+1, g)*n, g);
            
        }

        

    }

    string name() const override {
        return "Web Graph";
    }

    string description() const override {
        return "Generate Web Graph";
    }
    
    string category() const override {
        return "Web Class Graphs";
    };
    
    string check_parameters() override {
        return "";
    };
};

#endif

