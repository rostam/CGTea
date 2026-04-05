// CGTea Python Bindings
// Exposes the CGTea graph library to Python via pybind11.
// Build with: cmake -DBUILD_PYTHON_BINDINGS=ON ..
//             cmake --build . --target cgtea_py

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// --- Core datatypes (no wxWidgets dependency) ---
#include "../datatypes.h"
#include "../G6Format/G6Format.h"

// --- Generators (header-only, working implementations) ---
#include "../generators/Antiprism.h"
#include "../generators/Banana.h"
#include "../generators/Cmn.h"
#include "../generators/CocktailParty.h"
#include "../generators/Complete.h"
#include "../generators/Crown.h"
#include "../generators/Cycle.h"
#include "../generators/Flower.h"
#include "../generators/FriendshipGraph.h"
#include "../generators/Gear.h"
#include "../generators/GeneralizedPeterson.h"
#include "../generators/Heawood.h"
#include "../generators/Helm.h"
#include "../generators/Kmn.h"
#include "../generators/Lollipop.h"
#include "../generators/Path.h"
#include "../generators/Pmn.h"
#include "../generators/Prism.h"
#include "../generators/Regular.h"
#include "../generators/Star.h"
#include "../generators/Tadpole.h"
#include "../generators/Web.h"
#include "../generators/Wheel.h"

// --- Reports (header-only) ---
#include "../reports/NumOfVertices.h"
#include "../reports/NumOfEdges.h"
#include "../reports/MaxDegree.h"
#include "../reports/MinDegree.h"
#include "../reports/AverageDegree.h"
#include "../reports/Density.h"
#include "../reports/NumConnectedComponents.h"
#include "../reports/NumOfTriangles.h"
#include "../reports/NumOfQuadrangle.h"
#include "../reports/NumOfStars.h"
#include "../reports/EdgeDegree.h"
#include "../reports/WienerIndex.h"
#include "../reports/HyperWienerIndex.h"
#include "../reports/Harary.h"
#include "../reports/AdditiveHarary.h"
#include "../reports/GutmanIndex.h"
#include "../reports/SzegedIndex.h"
#include "../reports/TotalEccentricityIndex.h"
#include "../reports/WienerPolarityIndex.h"

// --- Reports with separate .h declarations (implementations in .cpp TUs) ---
#include "../reports/Diameter.h"
#include "../reports/Radius.h"
#include "../reports/GirthSize.h"
#include "../reports/MaxEigenValue.h"
#include "../reports/MinEigenValue.h"
#include "../reports/SumEigenValues.h"
#include "../reports/GraphEnergy.h"
#include "../reports/AlgebraicConnectivity.h"

// --- Reports whose full class is defined in the .cpp file (all inline) ---
// Including the .cpp directly is correct here: all member functions are
// defined inside the class body (implicitly inline), so there is no ODR
// violation when the .cpp is also compiled as a separate translation unit.
#include "../reports/MostarIndex.cpp"
#include "../reports/MWienerIndex.cpp"
#include "../reports/MultiplicativeHarary.cpp"

// --- Actions ---
#include "../actions/Coloring.h"
#include "../actions/LineGraph.h"

namespace py = pybind11;

// ---------------------------------------------------------------------------
// PyGraph: thin wrapper around the Boost Graph to provide a clean Python API
// ---------------------------------------------------------------------------

struct PyGraph {
    Graph g;

    PyGraph() = default;
    explicit PyGraph(Graph g_) : g(std::move(g_)) {}

    // Construction helpers
    static PyGraph from_edges(const std::vector<std::pair<int,int>>& edges, int n = -1) {
        PyGraph pg;
        if (n > 0)
            for (int i = 0; i < n; i++) boost::add_vertex(pg.g);
        for (auto [u, v] : edges)
            boost::add_edge(u, v, 1, pg.g);
        return pg;
    }

    // Mutation
    int add_vertex() {
        return (int)boost::add_vertex(g);
    }

    void add_edge(int u, int v, int weight = 1) {
        boost::add_edge(u, v, weight, g);
    }

    void remove_edge(int u, int v) {
        boost::remove_edge(u, v, g);
    }

    // Queries
    int num_vertices() const { return (int)boost::num_vertices(g); }
    int num_edges()    const { return (int)boost::num_edges(g); }

    std::vector<int> vertices() const {
        std::vector<int> vs;
        vs.reserve(boost::num_vertices(g));
        auto [vi, vend] = boost::vertices(g);
        for (; vi != vend; ++vi) vs.push_back((int)*vi);
        return vs;
    }

    std::vector<std::pair<int,int>> edges() const {
        std::vector<std::pair<int,int>> es;
        es.reserve(boost::num_edges(g));
        auto [ei, eend] = boost::edges(g);
        for (; ei != eend; ++ei)
            es.push_back({(int)boost::source(*ei, g), (int)boost::target(*ei, g)});
        return es;
    }

    std::vector<int> neighbors(int v) const {
        std::vector<int> ns;
        auto [ai, aend] = boost::adjacent_vertices(v, g);
        for (; ai != aend; ++ai) ns.push_back((int)*ai);
        return ns;
    }

    bool has_edge(int u, int v) const {
        return boost::edge(u, v, g).second;
    }

    int degree(int v) const {
        return (int)boost::out_degree(v, g);
    }

    // Adjacency matrix as nested list (usable with numpy.array(...))
    std::vector<std::vector<int>> adjacency_matrix() const {
        int n = (int)boost::num_vertices(g);
        std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
        auto [ei, eend] = boost::edges(g);
        for (; ei != eend; ++ei) {
            int u = (int)boost::source(*ei, g);
            int v = (int)boost::target(*ei, g);
            mat[u][v] = 1;
            mat[v][u] = 1;
        }
        return mat;
    }

    // Vertex color (set by Coloring action)
    std::vector<int> vertex_colors() const {
        int n = (int)boost::num_vertices(g);
        std::vector<int> colors(n);
        for (int i = 0; i < n; i++)
            colors[i] = boost::get(boost::vertex_color, g, i);
        return colors;
    }

    int get_vertex_color(int v) const {
        return boost::get(boost::vertex_color, g, v);
    }

    PyGraph copy() const { return PyGraph(g); }

    std::string repr() const {
        return "Graph(n=" + std::to_string(boost::num_vertices(g)) +
               ", m=" + std::to_string(boost::num_edges(g)) + ")";
    }
};

// ---------------------------------------------------------------------------
// Module definition
// ---------------------------------------------------------------------------

PYBIND11_MODULE(cgtea, m) {
    m.doc() = "CGTea: Graph Theory Exploration and Analysis\n\n"
              "Exposes graph generators, metrics, and transformations from the\n"
              "CGTea C++ library.\n\n"
              "Example::\n\n"
              "    import cgtea\n"
              "    g = cgtea.generators.cycle(6)\n"
              "    print(cgtea.reports.wiener_index(g))\n"
              "    print(cgtea.reports.diameter(g))\n";

    // -----------------------------------------------------------------------
    // Graph class
    // -----------------------------------------------------------------------

    py::class_<PyGraph>(m, "Graph",
        "An undirected graph backed by Boost.Graph.\n\n"
        "Vertices are non-negative integers. Multiple edges between the same\n"
        "pair are not supported (set-based edge container).")
        .def(py::init<>(), "Construct an empty graph.")
        .def_static("from_edges",
            &PyGraph::from_edges,
            py::arg("edges"),
            py::arg("n") = -1,
            "Construct a graph from an edge list.\n\n"
            "Parameters\n----------\n"
            "edges : list of (int, int)\n    Pairs (u, v) of vertex indices.\n"
            "n     : int, optional\n    Pre-allocate n labelled vertices (default: inferred).")
        .def("add_vertex", &PyGraph::add_vertex,
            "Add a new vertex and return its index.")
        .def("add_edge", &PyGraph::add_edge,
            py::arg("u"), py::arg("v"), py::arg("weight") = 1,
            "Add edge (u, v) with the given weight (default 1).")
        .def("remove_edge", &PyGraph::remove_edge,
            py::arg("u"), py::arg("v"), "Remove edge (u, v) if it exists.")
        .def_property_readonly("n", &PyGraph::num_vertices,
            "Number of vertices.")
        .def_property_readonly("m", &PyGraph::num_edges,
            "Number of edges.")
        .def("num_vertices", &PyGraph::num_vertices, "Number of vertices.")
        .def("num_edges",    &PyGraph::num_edges,    "Number of edges.")
        .def("vertices",  &PyGraph::vertices,  "Return list of all vertex indices.")
        .def("edges",     &PyGraph::edges,     "Return list of (u, v) edge tuples.")
        .def("neighbors", &PyGraph::neighbors,
            py::arg("v"), "Return list of neighbours of vertex v.")
        .def("has_edge",  &PyGraph::has_edge,
            py::arg("u"), py::arg("v"), "Check whether edge (u, v) exists.")
        .def("degree",    &PyGraph::degree,
            py::arg("v"), "Degree of vertex v.")
        .def("adjacency_matrix", &PyGraph::adjacency_matrix,
            "Return the adjacency matrix as a list-of-lists (0/1 integers).\n"
            "Pass to numpy.array() for matrix operations.")
        .def("vertex_colors", &PyGraph::vertex_colors,
            "Return vertex color vector (set by cgtea.actions.color).")
        .def("get_vertex_color", &PyGraph::get_vertex_color,
            py::arg("v"), "Return the color of vertex v.")
        .def("copy", &PyGraph::copy, "Return a deep copy of the graph.")
        .def("__len__", &PyGraph::num_vertices)
        .def("__repr__", &PyGraph::repr);

    // -----------------------------------------------------------------------
    // Generators submodule
    // -----------------------------------------------------------------------

    py::module_ gen = m.def_submodule("generators",
        "Graph generator functions.\n\n"
        "Each function returns a Graph instance. Parameters n and k follow the\n"
        "mathematical convention for the corresponding graph family.");

    gen.def("antiprism", [](int n) { return PyGraph{Antiprism().generate(n, 0)}; },
        py::arg("n"), "Antiprism graph A_n (two n-cycles connected by a band of triangles).");

    gen.def("banana", [](int n, int k) { return PyGraph{Banana().generate(n, k)}; },
        py::arg("n"), py::arg("k") = 3,
        "Banana graph B(n,k): n copies of the complete graph K_k sharing one vertex.");

    gen.def("circulant_product", [](int n, int k) { return PyGraph{Cmn().generate(n, k)}; },
        py::arg("n"), py::arg("m"),
        "Cartesian product C_n ✕ C_m of two cycle graphs.");

    gen.def("cocktail_party", [](int n) { return PyGraph{CocktailParty().generate(n, 0)}; },
        py::arg("n"),
        "Cocktail party graph K_{n×2}: complete multipartite graph with n parts of size 2.");

    gen.def("complete", [](int n) { return PyGraph{Complete().generate(n, 0)}; },
        py::arg("n"), "Complete graph K_n.");

    gen.def("crown", [](int n) { return PyGraph{Crown().generate(n, 0)}; },
        py::arg("n"), "Crown graph S_n^0: K_{n,n} minus a perfect matching.");

    gen.def("cycle", [](int n) { return PyGraph{Cycle().generate(n, 0)}; },
        py::arg("n"), "Cycle graph C_n.");

    gen.def("flower", [](int n) { return PyGraph{Flower().generate(n, 0)}; },
        py::arg("n"), "Flower graph.");

    gen.def("friendship", [](int n) { return PyGraph{FriendshipGraph().generate(n, 0)}; },
        py::arg("n"), "Friendship graph F_n: n triangles sharing a single common vertex.");

    gen.def("gear", [](int n) { return PyGraph{Gear().generate(n, 0)}; },
        py::arg("n"), "Gear graph G_n: wheel W_n with an extra vertex on each outer edge.");

    gen.def("generalized_petersen", [](int n, int k) {
            return PyGraph{GeneralizedPeterson().generate(n, k)};
        }, py::arg("n"), py::arg("k"),
        "Generalized Petersen graph GP(n,k).\n"
        "The classic Petersen graph is GP(5,2).");

    gen.def("petersen", [](){ return PyGraph{GeneralizedPeterson().generate(5, 2)}; },
        "The Petersen graph GP(5,2).");

    gen.def("heawood", [](){ return PyGraph{Heawood().generate(0, 0)}; },
        "The Heawood graph (14-vertex cage).");

    gen.def("helm", [](int n) { return PyGraph{Helm().generate(n, 0)}; },
        py::arg("n"), "Helm graph H_n: wheel W_n with a pendant edge at each outer vertex.");

    gen.def("complete_bipartite", [](int n, int k) { return PyGraph{Kmn().generate(n, k)}; },
        py::arg("n"), py::arg("k"),
        "Complete bipartite graph K_{n,k}.");

    gen.def("lollipop", [](int n, int k) { return PyGraph{Lollipop().generate(n, k)}; },
        py::arg("n"), py::arg("k"),
        "Lollipop graph L(n,k): K_n connected by a single edge to a path P_k.");

    gen.def("path", [](int n) { return PyGraph{Path().generate(n, 0)}; },
        py::arg("n"), "Path graph P_n.");

    gen.def("grid", [](int n, int k) { return PyGraph{Pmn().generate(n, k)}; },
        py::arg("n"), py::arg("m"),
        "Grid graph P_n ✕ P_m (n rows, m columns).");

    gen.def("prism", [](int n) { return PyGraph{Prism().generate(n, 0)}; },
        py::arg("n"), "Prism graph Y_n: two n-cycles connected by n edges.");

    gen.def("regular", [](int n, int k) { return PyGraph{Regular().generate(n, k)}; },
        py::arg("n"), py::arg("k"),
        "k-regular circulant graph on n vertices.");

    gen.def("star", [](int n) { return PyGraph{Star().generate(n, 0)}; },
        py::arg("n"), "Star graph S_n: K_{1,n}.");

    gen.def("tadpole", [](int n, int k) { return PyGraph{Tadpole().generate(n, k)}; },
        py::arg("n"), py::arg("k"),
        "Tadpole graph T(n,k): cycle C_n with a path P_k attached.");

    gen.def("web", [](int n, int k) { return PyGraph{Web().generate(n, k)}; },
        py::arg("n"), py::arg("k") = 3,
        "Web graph W(n,k).");

    gen.def("wheel", [](int n) { return PyGraph{Wheel().generate(n, 0)}; },
        py::arg("n"), "Wheel graph W_n: cycle C_n with a central hub connected to all vertices.");

    // -----------------------------------------------------------------------
    // Reports submodule
    // -----------------------------------------------------------------------

    py::module_ rep = m.def_submodule("reports",
        "Graph metric functions.\n\n"
        "Each function accepts a Graph and returns a numeric value.");

    // Basic counts
    rep.def("num_vertices", [](const PyGraph& g) {
            return std::stoi(NumOfVertices().report(g.g));
        }, py::arg("g"), "Number of vertices.");

    rep.def("num_edges", [](const PyGraph& g) {
            return std::stoi(NumOfEdges().report(g.g));
        }, py::arg("g"), "Number of edges.");

    rep.def("max_degree", [](const PyGraph& g) {
            return std::stoi(MaxDegree().report(g.g));
        }, py::arg("g"), "Maximum vertex degree.");

    rep.def("min_degree", [](const PyGraph& g) {
            return std::stoi(MinDegree().report(g.g));
        }, py::arg("g"), "Minimum vertex degree.");

    rep.def("average_degree", [](const PyGraph& g) {
            return std::stod(AverageDegree().report(g.g));
        }, py::arg("g"), "Average vertex degree (2m/n).");

    rep.def("density", [](const PyGraph& g) {
            return std::stod(Density().report(g.g));
        }, py::arg("g"), "Edge density 2m / (n*(n-1)).");

    rep.def("num_connected_components", [](const PyGraph& g) {
            return std::stoi(NumConnectedComponents().report(g.g));
        }, py::arg("g"), "Number of connected components.");

    rep.def("num_triangles", [](const PyGraph& g) {
            return std::stoll(NumberOfTriangles().report(g.g));
        }, py::arg("g"), "Number of triangles (3-cycles).");

    rep.def("num_quadrangles", [](const PyGraph& g) {
            return std::stoll(NumberOfQuadrangles().report(g.g));
        }, py::arg("g"), "Number of quadrangles (4-cycles).");

    rep.def("num_stars", [](const PyGraph& g) {
            return std::stoll(NumberOfStars().report(g.g));
        }, py::arg("g"), "Number of induced star subgraphs.");

    rep.def("edge_degree", [](const PyGraph& g) {
            return std::stoll(EdgeDegree().report(g.g));
        }, py::arg("g"), "Sum of (deg(u)+deg(v)) over all edges (u,v).");

    // Distance-based topological indices
    rep.def("wiener_index", [](const PyGraph& g) {
            return std::stoll(WienerIndex().report(g.g));
        }, py::arg("g"), "Wiener index: sum of all pairwise shortest-path distances.");

    rep.def("hyper_wiener_index", [](const PyGraph& g) {
            return std::stoll(HyperWienerIndex().report(g.g));
        }, py::arg("g"), "Hyper-Wiener index.");

    rep.def("harary_index", [](const PyGraph& g) {
            return std::stod(HararyIndex().report(g.g));
        }, py::arg("g"), "Harary index: sum of 1/d(u,v) over all pairs.");

    rep.def("additive_harary", [](const PyGraph& g) {
            return std::stod(AdditiveHararyIndex().report(g.g));
        }, py::arg("g"), "Additive Harary index.");

    rep.def("gutman_index", [](const PyGraph& g) {
            return std::stoll(GutmanIndex().report(g.g));
        }, py::arg("g"), "Gutman index: sum of deg(u)*deg(v)*d(u,v) over all pairs.");

    rep.def("szeged_index", [](const PyGraph& g) {
            return std::stoll(SzegedIndex().report(g.g));
        }, py::arg("g"), "Szeged index.");

    rep.def("total_eccentricity", [](const PyGraph& g) {
            return std::stoll(TotalEccentricityIndex().report(g.g));
        }, py::arg("g"), "Total eccentricity index: sum of eccentricities.");

    rep.def("wiener_polarity_index", [](const PyGraph& g) {
            return std::stoi(WienerPolarityIndex().report(g.g));
        }, py::arg("g"), "Wiener polarity index: number of pairs at distance 3.");

    rep.def("mostar_index", [](const PyGraph& g) {
            return std::stoll(MostarIndex().report(g.g));
        }, py::arg("g"), "Mostar index: sum of |n_u(e)-n_v(e)| over all edges.");

    rep.def("multiplicative_wiener_index", [](const PyGraph& g) {
            return std::stod(MultiplicativeWienerIndex().report(g.g));
        }, py::arg("g"),
        "Multiplicative Wiener index (log scale to avoid overflow): ln∏d(u,v).");

    rep.def("multiplicative_harary_index", [](const PyGraph& g) {
            return std::stod(MultiplicativeHararyIndex().report(g.g));
        }, py::arg("g"),
        "Multiplicative Harary index (log scale): ln∏(1/d(u,v)).");

    // Graph distances
    rep.def("diameter", [](const PyGraph& g) {
            return std::stoi(GraphDiameter().report(g.g));
        }, py::arg("g"), "Graph diameter (longest shortest path).");

    rep.def("radius", [](const PyGraph& g) {
            return std::stoi(GraphRadius().report(g.g));
        }, py::arg("g"), "Graph radius (minimum eccentricity).");

    rep.def("girth", [](const PyGraph& g) {
            return std::stoi(GraphGirthSize().report(g.g));
        }, py::arg("g"),
        "Girth of the graph (length of shortest cycle). Returns 0 if acyclic.");

    // Spectral indices
    rep.def("max_eigenvalue", [](const PyGraph& g) {
            return std::stod(MaxEigenValue().report(g.g));
        }, py::arg("g"), "Largest eigenvalue of the adjacency matrix (spectral radius).");

    rep.def("min_eigenvalue", [](const PyGraph& g) {
            return std::stod(MinEigenValue().report(g.g));
        }, py::arg("g"), "Smallest eigenvalue of the adjacency matrix.");

    rep.def("sum_eigenvalues", [](const PyGraph& g) {
            return std::stod(SumEigenValues().report(g.g));
        }, py::arg("g"), "Sum of absolute eigenvalues (equals twice the graph energy).");

    rep.def("graph_energy", [](const PyGraph& g) {
            return std::stod(GraphEnergy().report(g.g));
        }, py::arg("g"), "Graph energy: sum of |λ_i| over all adjacency eigenvalues.");

    rep.def("algebraic_connectivity", [](const PyGraph& g) {
            return std::stod(AlgebraicConnectivity().report(g.g));
        }, py::arg("g"),
        "Algebraic connectivity (Fiedler value): second-smallest Laplacian eigenvalue.\n"
        "Zero iff the graph is disconnected.");

    // -----------------------------------------------------------------------
    // Actions submodule
    // -----------------------------------------------------------------------

    py::module_ act = m.def_submodule("actions",
        "Graph transformation functions. Each returns a new Graph.");

    act.def("color", [](PyGraph g) {
            return PyGraph{Coloring().action(g.g)};
        }, py::arg("g"),
        "Apply sequential greedy vertex coloring.\n\n"
        "Returns a copy of g with vertex colors set. Retrieve them with\n"
        "graph.vertex_colors() or graph.get_vertex_color(v).");

    act.def("line_graph", [](PyGraph g) {
            return PyGraph{LineGraph().action(g.g)};
        }, py::arg("g"),
        "Compute the line graph L(G).\n\n"
        "Vertices of L(G) correspond to edges of G; two vertices in L(G)\n"
        "are adjacent iff the corresponding edges in G share an endpoint.");

    // -----------------------------------------------------------------------
    // Graph6 I/O
    // -----------------------------------------------------------------------

    m.def("to_g6", [](PyGraph& g) {
            G6Format fmt;
            return fmt.graphToG6(g.g);
        }, py::arg("g"),
        "Encode a graph to Graph6 format string.");

    m.def("from_g6", [](const std::string& s) {
            G6Format fmt;
            return PyGraph{fmt.stringToGraph2(s)};
        }, py::arg("s"),
        "Decode a Graph6 format string into a Graph.");

    // -----------------------------------------------------------------------
    // Convenience: list available generators / reports
    // -----------------------------------------------------------------------

    m.def("list_generators", []() {
            return std::vector<std::string>{
                "antiprism", "banana", "circulant_product", "cocktail_party",
                "complete", "complete_bipartite", "crown", "cycle", "flower",
                "friendship", "gear", "generalized_petersen", "grid",
                "heawood", "helm", "lollipop", "path", "petersen",
                "prism", "regular", "star", "tadpole", "web", "wheel"
            };
        }, "Return the list of available generator function names.");

    m.def("list_reports", []() {
            return std::vector<std::string>{
                "num_vertices", "num_edges", "max_degree", "min_degree",
                "average_degree", "density", "num_connected_components",
                "num_triangles", "num_quadrangles", "num_stars", "edge_degree",
                "wiener_index", "hyper_wiener_index", "harary_index",
                "additive_harary", "gutman_index", "szeged_index",
                "total_eccentricity", "wiener_polarity_index", "mostar_index",
                "multiplicative_wiener_index", "multiplicative_harary_index",
                "diameter", "radius", "girth",
                "max_eigenvalue", "min_eigenvalue", "sum_eigenvalues",
                "graph_energy", "algebraic_connectivity"
            };
        }, "Return the list of available report function names.");
}
