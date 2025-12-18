#include <pybind11/pybind11.h>
#include "include/antColony.h"

namespace py = pybind11;

PYBIND11_MODULE(knds, m)
{
    m.doc() = "KNDS Ant Colony solver";

    py::class_<AntColony>(m, "AntColony")
        .def(py::init<>())
        .def("set_graph", &AntColony::setGraph, "Set graph (n, edges) where edges is list of (a,b,weight)")
        .def("set_iterations", &AntColony::setIterations, "Set number of iterations")
        .def("solve", [](AntColony &self) {
            auto res = self.findBestScoreReturn();
            return py::make_tuple(res.cost, res.path);
        }, "Run solver and return (cost, path)")
        .def("run", &AntColony::run, "Run (reads from stdin and prints result)");

    m.def("solve_graph", [](int n, const std::vector<std::tuple<int,int,double>> &edges, int iterations /*=100*/) {
        AntColony a;
        a.setGraph(n, edges);
        a.setIterations(iterations);
        auto res = a.findBestScoreReturn();
        return py::make_tuple(res.cost, res.path);
    }, py::arg("n"), py::arg("edges"), py::arg("iterations") = 100, "Convenience: solve_graph(n, edges, iterations=100)");
}
