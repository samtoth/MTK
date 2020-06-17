from conans import ConanFile, CMake, tools


class MTKConan(ConanFile):
    name = "MTK"
    version = "0.1.1"
    license = "GPL3"
    author = "Sam Toth sam@toth.co.uk"
    url = "https://github.com/samtoth/MTK"
    description = "A C++ API designed for Music software"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "generator": ['Ninja', 'MinGw Makefiles', None]}
    default_options = {"shared": True, "gtest:build_gmock": False, "generator": 'Ninja'}
    build_requires = ['gtest/1.10.0', 'pybind11/2.4.3', 'doxygen/1.8.17']
    requires = ['eigen/3.3.7',
                'portaudio/v190600.20161030@bincrafters/stable']
    generators = "cmake"


    def source(self):
        self.run("git clone https://github.com/samtoth/MTK.git")

    def build(self):
        self.options['gtest'].shared = True
        print(f" --INFO      Generator used is {'auto' if self.options.generator is None else self.options.generator}")
        cmake = CMake(self, generator=str(self.options.generator))
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libdir = ['lib', 'lib64']
        self.cpp_info.libs = ["MTKCore", "MTKAudio", "MuDa"]
