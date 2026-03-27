# CGTea
## A Graph Theory Exploration and Analysis Tool in C++

![CGTea](https://github.com/rostam/CGTea/blob/master/doc/images/image.png)

CGTea is a C++ implementation of [GTea (Graph Theory Exploration and Analysis)](https://github.com/rostam/GraphTea), a desktop application for constructing, visualizing, and analyzing graphs. The GUI is built with wxWidgets; graph algorithms use the Boost Graph Library; spectral computations use Eigen.

---

## Features

### Graph Generators

| Generator | Parameters | Description |
|-----------|------------|-------------|
| Antiprism | n | Two interlocked n-cycles |
| Banana | n | Banana graph |
| Complete Bipartite K(n,k) | n, k | Complete bipartite graph with parts of size n and k |
| Cmn | n, m | C(m,n) graph |
| CocktailParty | n | Complete bipartite minus a perfect matching |
| Complete | n | K_n complete graph |
| Crown | n | Crown graph |
| Cycle | n | Simple cycle C_n |
| Flower | n | Flower graph |
| Friendship Graph | n | n triangles sharing a common central vertex (2n+1 vertices total) |
| Gear | n | Gear graph |
| Generalized Peterson | n, k | GP(n,k); GP(5,2) is the Petersen graph |
| Grid Graph P(n)×P(k) | n, k | n×k rectangular grid |
| Heawood | — | Fixed: 14 vertices, 3-regular, girth 6 |
| Helm | n | Wheel W_n with a pendant vertex on each outer vertex |
| Lollipop | n, k | Complete graph K_n with a path P_k attached |
| Path | n | Path graph P_n |
| Prism | n | Prism graph |
| Regular | n, k | k-regular circulant graph on n vertices |
| Star | n | Star graph S_n |
| Tadpole | n, k | Cycle C_n with path P_k attached at one vertex |
| Web | n, k | Web graph (n-cycle inner ring, k layers) |
| Wheel | n | Wheel graph W_n |

### Graph Reports

#### General
| Report | Formula / Description |
|--------|-----------------------|
| Number of Vertices | \|V\| |
| Number of Edges | \|E\| |
| Max Degree | Maximum vertex degree |
| Min Degree | Minimum vertex degree |
| Average Degree | 2\|E\| / \|V\| |
| Density | 2\|E\| / (\|V\|(\|V\|−1)) |
| Number of Connected Components | BGL connected-components |
| Diameter | Longest shortest path (Floyd–Warshall) |
| Radius | Minimum eccentricity |
| Girth | Length of the shortest cycle (0 if acyclic) |
| Number of Triangles | Triangle count |
| Number of 4-Cycles | C4 count via common-neighbor formula |
| Number of Stars | Σ_v C(deg(v), 2) — cherries centered at each vertex |
| Edge Degree Sum | Σ_{uv ∈ E} (deg(u) + deg(v)) |

#### Spectral
| Report | Description |
|--------|-------------|
| Max Eigenvalue | Spectral radius of the adjacency matrix |
| Min Eigenvalue | Smallest eigenvalue |
| Sum of Eigenvalues | Sum of all eigenvalues |
| Graph Energy | Σ \|λ_i\| |
| Algebraic Connectivity | Second smallest Laplacian eigenvalue (Fiedler value) |

#### Topological Indices
| Report | Formula |
|--------|---------|
| Wiener Index | Σ_{u<v} d(u,v) |
| Hyper Wiener Index | ½ Σ_{u<v} [d(u,v) + d(u,v)²] |
| Harary Index | Σ_{u<v} 1/d(u,v) |
| Additive Harary Index | Σ_{uv ∈ E} 1/(deg(u)+deg(v)) |
| Reciprocal Degree Distance | Σ_{u<v} (deg(u)+deg(v)) / d(u,v) |
| Degree Distance | Σ_{u<v} (deg(u)+deg(v)) · d(u,v) |
| Gutman Index | Σ_{u<v} deg(u)·deg(v)·d(u,v) |
| Szeged Index | Σ_{uv ∈ E} n_u(e) · n_v(e) |
| Mostar Index | Σ_{uv ∈ E} \|n_u(e) − n_v(e)\| |
| Total Eccentricity Index | Σ_v ecc(v) |
| Wiener Polarity Index | # pairs {u,v} with d(u,v) = 3 |
| Multiplicative Wiener Index | ln Π_{u<v} d(u,v) |
| Multiplicative Harary Index | ln Π_{u<v} 1/d(u,v) |

> **Note on Szeged / Mostar:** n_u(e) is the number of vertices strictly closer to u than to v for edge e = (u,v).

### Graph Actions

| Action | Description |
|--------|-------------|
| Heuristic Coloring | Greedy sequential vertex coloring |
| Line Graph | Transforms G into its line graph L(G) |

### Layout Algorithms

- **Circular layout** — default for most generators
- **Force-directed layout** — Fruchterman–Reingold (`Layout` menu)
- **Fit to Width** — rescales the current layout to fill the canvas

---

## Conjecture Checker

The **Conjecture Checker** (`Analysis → Conjecture Checker`, or `Ctrl+J`) lets you compute multiple graph reports across a collection of graphs and compare the results in a table. This is useful for testing conjectures of the form "does property A always dominate property B?"

### Opening the Dialog

Go to **Analysis → Conjecture Checker** (or press `Ctrl+J`).

### Building the Graph Collection

The left panel manages the list of graphs to analyze.

#### Add from Generator

1. Click **Add Graph**.
2. Choose a generator from the dropdown.
3. Enter a range for each parameter:
   - **n from / to** — the parameter n will be swept over this range.
   - **k from / to** — (if the generator has a second parameter) k will be swept.
4. Click **OK**. All combinations of (n, k) in the Cartesian product of the two ranges are added. If the total exceeds 200, you are asked to confirm.

Each graph is labelled with its generator name and parameters, e.g. `Cycle(n=8)` or `Grid Graph P(n)*P(k)(n=3, k=4)`.

#### Add from G6 File

1. Click **Add from G6 File...**.
2. Select one or more `.g6` files. Each line (that is not a comment starting with `#`) is parsed as a separate graph and added to the list, labelled `filename.g6 #1`, `filename.g6 #2`, etc.

#### Remove a Graph

Select a graph in the list and click **Remove Selected**.

### Selecting Reports

The right panel shows all available reports as a checklist. By default all are checked. Use **Select All** / **Deselect All** to change the selection quickly.

### Computing the Table

Click **Compute**. A table appears below with:
- One row per graph
- One column per selected report
- The first column shows the graph label

### Saving Results

Click **Save CSV...** to export the table to a comma-separated file that can be opened in any spreadsheet application.

---

## File Formats

| Format | Read | Write |
|--------|------|-------|
| Graph6 (`.g6`) | ✓ | ✓ |
| CGTea (`.tea`) | planned | planned |
| MTX (`.mtx`) | planned | planned |

---

## Dependencies

| Library | Purpose | Install |
|---------|---------|---------|
| [wxWidgets](https://wxwidgets.org/) | GUI | `sudo apt-get install libwxgtk3.2-dev` |
| [Boost](https://www.boost.org/) | Graph algorithms, unit tests | `sudo apt-get install libboost-all-dev` |
| [Eigen](https://eigen.tuxfamily.org/) | Spectral / eigenvalue computation | Copy `Eigen/` directory into the project root |

> The Eigen headers must be placed at `<project-root>/Eigen/`. They are not installed system-wide.

---

## Building

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target CGTea
```

To build the test suite:

```bash
cmake --build . --target BoostTest
```

---

## Running

```bash
./CGTea
```

**Generating a graph:** `Generate` menu → pick a generator → enter parameters.

**Computing a single report:** `Report` menu → pick a metric → result appears in the sidebar table.

**Computing all reports:** Click **Compute Statistics** in the sidebar — all reports run sequentially and fill in the table one by one.

**Applying an action:** `Action` menu → Coloring or Line Graph → graph is updated in place.

**Loading / saving:** `File → Open` or `File → Save` supports `.g6` (Graph6 format).

**Settings:** `File → Settings` to choose vertex shape (circle, square, triangle, diamond) and edge style (line, curve, dashed, double-arrow).

### Mouse Editing on the Canvas

| Interaction | Effect |
|-------------|--------|
| Double-click on empty space | Create a new vertex at that position |
| Click on a vertex | Select it (orange ring highlight) |
| Click on an edge | Select it (blue highlight) |
| Drag a selected vertex | Move the vertex |
| Drag a selected edge | Move both endpoints of the edge together |
| Shift + drag from a vertex to another vertex | Draw a new edge between the two vertices; a dotted preview line follows the cursor while dragging |
| Release on empty space during Shift+drag | Cancel edge creation |

---

## Testing

```bash
cd build
./BoostTest
```

The test suite covers:
- **Generators** — vertex/edge counts, max/min degree, diameter, girth for 13 generators
- **Reports** — basic metrics, triangle count, diameter, girth
- **Actions** — proper coloring invariant, chromatic number for known graphs, line graph degree formula
- **I/O** — Graph6 encoding, `graphsize` round-trip, encode→decode round-trip for multiple graph families

---

## Project Structure

```
CGTea/
├── CGTeaApp.cpp/h               Application entry point
├── CGTeaFrame.cpp/h             Main window and menu wiring
├── BasicDrawPane.cpp/h          Canvas (draw vertices, edges, shapes)
├── CGTeaSidebar.cpp/h           Statistics panel with live-updating table
├── ConjectureCheckerDialog.cpp/h  Conjecture Checker dialog
├── SettingsDialog.cpp/h         Settings dialog (shapes, edge styles)
├── Config.h                     Persistent settings (vertex/edge shape)
├── datatypes.h                  Graph typedef and iterator helpers
├── const_values.h               VertexShape / EdgeShape enums
├── generators/                  Graph generator classes + force-directed layout
├── reports/                     Graph metric classes + Floyd-Warshall utility
├── actions/                     Graph transformation classes
├── G6Format/                    Graph6 encoder/decoder
├── ConjectureCheck/             Batch conjecture verification over graph databases
├── BoostTestSrc/                Boost.Test unit tests
└── Eigen/                       Eigen headers (place here manually)
```

---

## Contributing

The project is under active development. Areas that welcome contributions:

- Completing `.tea` and `.mtx` file format support
- Additional generators and reports
- Expanding test coverage
