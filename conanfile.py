from conan import ConanFile
from conan.tools.cmake import cmake_layout


class BallSortRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("gtest/1.14.0")
        self.requires("fmt/10.2.1")

    def build_requirements(self):
        self.tool_requires("cmake/3.28.1")

    def layout(self):
        cmake_layout(self)
