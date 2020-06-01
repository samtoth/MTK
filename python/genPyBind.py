import tools.doxy
import sys

if len(sys.argv) < 3:
    print("Usage: python genPyBind <xmlDir> <cppFile>")
    exit(0)

xmlDir = sys.argv[1]
cppFile = sys.argv[2]

project = tools.doxy.import_doxy(xmlDir, "MusicToolKit project")
print(project)

f = open(cppFile, "w")
f.write("""#include <pybind11/pybind11.h>

{0}

namespace py = pybind11;

{1}""".format(project.all_includes(), project.members[0].py_bindings()))
f.close()
