from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "knds",
        ["_pybind.cpp", "src/antColony.cpp"],
        include_dirs=["include"],
    )
]

setup(
    name="knds",
    version="0.1.0",
    description="Ant Colony solver bindings",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
