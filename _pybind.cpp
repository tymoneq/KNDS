#include <pybind11/pybind11.h>
#include "include/antColony.h"

// fix pybind
namespace py = pybind11;

PYBIND11_MODULE(AntColony, handle)
{
    handle.doc() = "KNDS Ant Colony solver";
    py::class_<AntColony>(
        handle, "Ant Colony Class")
        .def(py::init</*ctor args*/>())
        .def("solve", &AntColony::run);
}
