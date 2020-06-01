import tools.doxy
import markdown
from mako.lookup import TemplateLookup
from mdx_gfm import GithubFlavoredMarkdownExtension as GFM
import sys


def render_markdown(file: str) -> str:
    f = open(file, "r")
    md = f.read()
    f.close()
    return markdown.markdown(md, extensions=[GFM(), 'toc'], output="xhtml")


def process_file(file: str, _lookup: TemplateLookup, **_data):
    template = _lookup.get_template(file)
    result = template.render(**_data)
    f = open(_lookup.directories[0] + "/" + file, "w")
    f.write(result)
    f.close()


# =================================================================== #

if len(sys.argv) < 3:
    print("Usage: python doxyToHTML <xmlDir> <HTMLDir>")
    exit(0)

xmlDir = sys.argv[1]
htmlDir = sys.argv[2]

project = tools.doxy.import_doxy(xmlDir, "MusicToolKit project")
print(project)

lookup = TemplateLookup(directories=[htmlDir], module_directory='/tmp/mako_modules')

data = {'PROJECT_NAME': "@CMAKE_PROJECT_NAME@", 'PROJECT_VERSION': "@CMAKE_PROJECT_VERSION@",
        'render_markdown': render_markdown, 'project': project}

process_file("index.xhtml", lookup, **data)
process_file("classes.xhtml", lookup, **data)
process_file("MuDaSpec.xhtml", lookup, **data)