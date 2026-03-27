# CGTea
## A Graph Theory Exploration and Analysis Tool in C++

![CGTea](https://github.com/rostam/CGTea/blob/master/doc/images/image.png)

CGTea is a C++ implementation of [GTea (Graph Theory Exploration and Analysis)](https://github.com/rostam/GraphTea), a desktop application for constructing, visualizing, and analyzing graphs. The GUI is built with wxWidgets; graph algorithms use the Boost Graph Library; spectral computations use Eigen.

---

## Features

### Graph Generators
| Generator | Description |
|-----------|-------------|
| Antiprism | Two interlocked cycles |
| Banana | Banana graph |
| Cmn | C(m,n) graph |
| CocktailParty | Complete bipartite minus perfect matching |
| Complete | K_n complete graph |
| Crown | Crown graph |
| Cycle | Simple cycle C_n |
| Flower | Flower graph |
| Gear | Gear graph |
| Generalized Peterson | GP(n,k), includes the Petersen graph GP(5,2) |
| Heawood | Heawood graph (14 vertices, 3-regular, girth 6) |
| Path | Path graph P_n |
| Prism | Prism graph |
| Regular | k-regular circulant graph |
| Star | Star graph S_n |
| Web | Web graph |
| Wheel | Wheel graph W_n |

### Graph Reports
| Report | Description |
|--------|-------------|
| Number of Vertices | \|V\| |
| Number of Edges | \|E\| |
| Max / Min Degree | Maximum and minimum vertex degree |
| Diameter | Longest shortest path (Floyd–Warshall) |
| Girth | Length of the shortest cycle (0 if acyclic) |
| Max / Min / Sum Eigenvalue | Spectral properties of the adjacency matrix |
| Number of Triangles | Triangle count |

### Graph Actions
| Action | Description |
|--------|-------------|
| Heuristic Coloring | Greedy sequential vertex coloring |
| Line Graph | Transforms G into its line graph L(G) |

### Layout Algorithms
- **Circular layout** — default for most generators
- **Force-directed layout** — Fruchterman–Reingold (via Boost)
- **Fit to width** — rescales the current layout to fill the panel

### File Formats
- **Graph6 (`.g6`)** — read and write
- **CGTea (`.tea`)** — planned
- **MTX (`.mtx`)** — planned

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

**Generating a graph:** `Generate` menu → pick a generator → enter parameters as `n,k`.

**Computing a report:** `Report` menu → pick a metric → result appears in the sidebar.

**Applying an action:** `Action` menu → Coloring or Line Graph → graph is updated in place.

**Loading / saving:** `File → Open` or `File → Save` supports `.g6` (Graph6 format).

**Settings:** `File → Settings` to choose vertex shape (circle, square, triangle, diamond) and edge style (line, curve, dashed, double-arrow).

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
├── CGTeaApp.cpp/h          Application entry point
├── CGTeaFrame.cpp/h        Main window and menu wiring
├── BasicDrawPane.cpp/h     Canvas (draw vertices, edges, shapes)
├── CGTeaSidebar.cpp/h      Statistics panel
├── SettingsDialog.cpp/h    Settings dialog (shapes, edge styles)
├── Config.h                Persistent settings (vertex/edge shape)
├── datatypes.h             Graph typedef and iterator helpers
├── const_values.h          VertexShape / EdgeShape enums
├── generators/             Graph generator classes + force-directed layout
├── reports/                Graph metric classes + Floyd-Warshall utility
├── actions/                Graph transformation classes
├── G6Format/               Graph6 encoder/decoder
├── ConjectureCheck/        Batch conjecture verification over graph databases
├── BoostTestSrc/           Boost.Test unit tests
└── Eigen/                  Eigen headers (place here manually)
```

---

## Contributing

The project is under active development. Areas that welcome contributions:

- Completing `.tea` and `.mtx` file format support
- Mouse-based graph editing (drag vertices, add edges by clicking)
- Additional generators and reports
- Expanding test coverage

