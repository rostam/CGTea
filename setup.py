"""
Build and install the cgtea Python extension module.

Usage:
    pip install .            # build + install into the current environment
    pip install -e .         # editable / development install
    pip install . --verbose  # show compiler output

Requires:
    - CMake >= 3.10
    - A C++17 compiler (GCC >= 7 or Clang >= 5)
    - Boost (headers + compiled libraries)
    - Eigen (headers placed at CGTea/Eigen/)
    - pybind11 (installed automatically via pip dependency)
"""

import os
import subprocess
import sys
from pathlib import Path

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name: str, source_dir: str = ".") -> None:
        super().__init__(name, sources=[])
        self.source_dir = str(Path(source_dir).resolve())


class CMakeBuild(build_ext):
    def build_extension(self, ext: CMakeExtension) -> None:
        ext_fullpath = Path(self.get_ext_fullpath(ext.name)).resolve()
        ext_dir = ext_fullpath.parent

        # Pass the pybind11 cmake directory found in the active Python env
        import pybind11
        pybind11_dir = pybind11.get_cmake_dir()

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={ext_dir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            f"-Dpybind11_DIR={pybind11_dir}",
            "-DBUILD_PYTHON_BINDINGS=ON",
            # Suppress the wxWidgets requirement – not needed for the bindings
            "-DwxWidgets_FIND_REQUIRED=FALSE",
            f"-DCMAKE_BUILD_TYPE={'Debug' if self.debug else 'Release'}",
        ]

        build_args = ["--target", "cgtea_py", "--", "-j4"]

        build_temp = Path(self.build_temp) / ext.name
        build_temp.mkdir(parents=True, exist_ok=True)

        subprocess.run(
            ["cmake", ext.source_dir, *cmake_args],
            cwd=build_temp,
            check=True,
        )
        subprocess.run(
            ["cmake", "--build", ".", *build_args],
            cwd=build_temp,
            check=True,
        )


setup(
    name="cgtea",
    version="1.0.0",
    author="Ali Rostami",
    description="CGTea – Graph Theory Exploration and Analysis (Python bindings)",
    long_description=Path("README.md").read_text(encoding="utf-8") if Path("README.md").exists() else "",
    long_description_content_type="text/markdown",
    ext_modules=[CMakeExtension("cgtea")],
    cmdclass={"build_ext": CMakeBuild},
    python_requires=">=3.8",
    install_requires=["pybind11>=2.12"],
    extras_require={
        "numpy": ["numpy>=1.20"],
        "networkx": ["networkx>=2.6"],
    },
    zip_safe=False,
)
