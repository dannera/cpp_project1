from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class MyProjectConan(ConanFile):
    name = "my_project"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    exports_sources = "CMakeLists.txt", "src/*"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
