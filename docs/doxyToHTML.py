import html
import sys
import xml.etree.ElementTree as ET
import markdown
from mako.lookup import TemplateLookup
from mdx_gfm import GithubFlavoredMarkdownExtension as GFM


def element_to_string(element: ET.Element) -> str:
    return "".join([element.text or ""] + [e.text or "" for e in element])


def render_markdown(file: str) -> str:
    f = open(file, "r")
    md = f.read()
    f.close()
    return markdown.markdown(md, extensions=[GFM(), 'toc'], output="xhtml")


class Member:
    def __init__(self, memberXML: ET.Element):
        self.name = memberXML.find('name').text
        try:
            self.type = html.escape(memberXML.find('type').text)
        except:
            self.type = ""

        try:
            self.argsstring = (html.escape(memberXML.find('argsstring').text or ""))
        except:
            self.argsstring = ""
        self.brief = element_to_string(memberXML.find('briefdescription'))


names = {"attrib": "attributes", "func": "functions"}


class Section:
    def __init__(self, sectionXML: ET.Element):
        self.kind = sectionXML.attrib['kind']
        self.name = "".join(
            [self.kind.split("-")[0].capitalize()] + [(" " + (names[str(a)] if a in names.keys() else a.capitalize()))
                                                      for a in self.kind.split("-")[1:]])
        self.members = []
        mem: ET.Element
        for mem in sectionXML.findall('memberdef'):
            self.members.append(Member(mem))


class Namespace:
    def __init__(self, namespaceXMLTree: ET.ElementTree=None):
        self.data = None
        self.name = "global"
        if namespaceXMLTree is not None:
            self.data = namespaceXMLTree.getroot()[0]
            self.name = self.data.find('compoundname').text or ""
        self.members = []


class Class:
    def __init__(self, classXMLTree: ET.ElementTree, namespaces):
        self.data = classXMLTree.getroot()[0]
        self.fullName: list[str] = self.data.find('compoundname').text.split("::")
        self.name = self.fullName[-1]
        self.url = self.name + ".xhtml"
        self.brief: str = element_to_string(self.data.find('briefdescription'))
        self.includes = {}
        self.namespace = namespaces[self.fullName[0]] if len(self.fullName) > 1 else namespaces['none']
        self.namespace.members.append(self)

        include: ET.Element
        for include in self.data.findall('includes'):
            self.includes[include.text] = include.get('refid')
        self.sections = []
        section: ET.Element
        for section in self.data.findall('sectiondef'):
            self.sections.append(Section(section))


def import_xml(file: str) -> ET.ElementTree:
    tree = ET.parse(file)
    return tree


def print_tree(elem, index: int):
    text = ""
    if index > 1:
        for i in range(0, index - 1):
            text += "    "
        text += "->"

    print(text, elem.text, elem.tag, elem.attrib)

    for child in elem:
        print_tree(child, index + 1)


def get_namespaces(_xml_dir, index: ET.Element) -> dict:
    namespaces: dict = {'none': Namespace()}
    compound: ET.Element
    for compound in index.findall('compound'):
        if "kind" in compound.attrib:
            if compound.attrib["kind"] == "namespace":
                namespaces[compound.find('name').text] = (
                    Namespace(import_xml(_xml_dir + "/" + compound.get('refid') + ".xml")))
    return namespaces


def get_classes(_xml_dir: str, index: ET.Element, namespaces) -> list:
    classes: list = []
    compound: ET.Element
    for compound in index.findall('compound'):
        if "kind" in compound.attrib:
            if compound.attrib["kind"] == "class":
                classes.append(Class(import_xml(_xml_dir + "/" + compound.get('refid') + ".xml"), namespaces))
    return classes


def process_file(file: str, _lookup: TemplateLookup, **data):
    template = _lookup.get_template(file)
    result = template.render(**data)
    f = open(_lookup.directories[0] + "/" + file, "w")
    f.write(result)
    f.close()


def generate_classes(_classes, _lookup, **data):
    template = _lookup.get_template("class-template.xhtml")
    for _class in _classes:
        result = template.render(currentClass=_class, **data)
        f = open(_lookup.directories[0] + "/" + _class.url, "w")
        f.write(result)
        f.close()


# ============================================================================ #

if len(sys.argv) < 3:
    print("Usage: python doxyToHTML <xmlDir> <HTMLDir>")
    exit(0)

xmlDir = sys.argv[1]
htmlDir = sys.argv[2]

index = import_xml(xmlDir + "/index.xml")
indexRoot = index.getroot()

_namespaces = get_namespaces(xmlDir, indexRoot)
_classes = get_classes(xmlDir, indexRoot, _namespaces)

lookup = TemplateLookup(directories=[htmlDir], module_directory='/tmp/mako_modules')

data = {'PROJECT_NAME': "@CMAKE_PROJECT_NAME@", 'PROJECT_VERSION': "@CMAKE_PROJECT_VERSION@",
        'render_markdown': render_markdown, 'namespaces': _namespaces}

process_file("index.xhtml", lookup, **data)
process_file("classes.xhtml", lookup, classes=_classes, **data)
process_file("MuDaSpec.xhtml", lookup, **data)
generate_classes(_classes, lookup, **data)
