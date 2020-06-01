import xml.etree.ElementTree as ET
import tools.doxy.d_parser as d_parser


def __find_base_namespace_refs(index: ET.Element):
    base_namespaces: [str] = []
    compound: ET.Element
    for compound in index.findall('compound'):
        if "kind" in compound.attrib:
            if compound.attrib["kind"] == "namespace":
                if not (compound.find('name').text.__contains__("::")):
                    base_namespaces.append(compound.get('refid'))
    return base_namespaces


class Object:
    def __init__(self, name=None):
        self.members: [Object] = []
        self.brief = ""
        self.kind = self.__class__.__name__
        if name is not None:
            self.name = name

    def __str__(self):
        rep = "-> " + self.kind + ": " + self.name + "\n"
        for member in self.members:
            for line in str(member).splitlines():
                rep += "   " + line + "\n"
        return rep

    def py_bindings(self, parent_ref):
        return "".join((ob.py_bindings(parent_ref)) for ob in self.members)

    def all_includes(self):
        ret: str = ""
        for member in self.members:
            ret += member.all_includes()
        return ret

class Member(Object):
    def __init__(self, xml_dir, member: ET.Element, context: str):
        super().__init__(member.find('name').text)
        self.context = context
        self.kind = member.get('kind')
        self.data = member
        self.type = self.data.find('type').text or ""
        self.prot = self.data.get('prot')
        self.static = self.data.get('static') == "yes"
        self.brief: str = d_parser.get_elem_inner_to_string(self.data.find('briefdescription'))


class Function(Member):
    def __init__(self, xml_dir, member: ET.Element, context: str):
        super().__init__(xml_dir, member, context)
        self.virtual = member.get('virt')
        self.const = member.get('const') == "yes"
        self.explicit = member.get('explicit') == "yes"
        self.inline = member.get('inline') == "yes"


class Variable(Member):
    def __init__(self, xml_dir, member: ET.Element, context: str):
        super().__init__(xml_dir, member, context)


class Container(Object):
    def __init__(self, xml_dir: str, refid: str, context: str):
        super().__init__(xml_dir)
        self.data = d_parser.import_xml(xml_dir + "/" + refid + ".xml").getroot().find('compounddef')
        self.context = "".join((item + "::") for item in self.data.find('compoundname').text.split("::")[:-1])
        self.name = self.data.find('compoundname').text.split("::")[-1]
        self.brief: str = d_parser.get_elem_inner_to_string(self.data.find('briefdescription'))
        section: ET.Element
        for section in self.data.findall('sectiondef'):
            for member in section.findall('memberdef'):
                if member.get('kind') == 'function':
                    self.members.append(Function(xml_dir, member, self.context + self.name))
                elif member.get('kind') == 'variable':
                    self.members.append(Variable(xml_dir, member, self.context + self.name))
                else:
                    self.members.append(Member(xml_dir, member, self.context + self.name))

        def py_bindings(self, parent_ref: str):
            return super(self).py_bindings(parent_ref)


class Class(Container):
    def __init__(self, xml_dir: str, refid: str, context: str):
        super().__init__(xml_dir, refid, context)
        self.includes = {}
        include: ET.Element
        for include in self.data.findall('includes'):
            self.includes[include.text] = include.get('refid')
        self.location = self.data.find('location').get('file')

    def py_bindings(self, parent_ref: str):
        return """auto {0} = py::class_<{1}>({2}, "{0}");
        
    {3}""".format(self.name, self.context + self.name, parent_ref, super().py_bindings(self.name))

    def all_includes(self):
        return "#include <{0}>\n".format(self.location)

class Namespace(Container):
    def __init__(self, xml_dir: str, refid: str, context: str = ""):
        super().__init__(xml_dir, refid, context)
        for elem in self.data.findall('innerclass'):
            self.members.append(
                Class(xml_dir, elem.get('refid'), self.context + self.name))
        for elem in self.data.findall('innernamespace'):
            self.members.append(Namespace(xml_dir, elem.get('refid'), self.context + self.name))

    def py_bindings(self, parent_ref: str = None):
        if parent_ref is None:
            return """PYBIND11_MODULE({0}, m) {{
    m.doc() = "{1}";
    {2}
}}""".format(self.name, self.brief, super().py_bindings("m"))
        else:
            return """py::module {0} = {1}.def_submodule("{0}", "{2}");
    {{
        {3}
    }}""".format(self.name, parent_ref, self.brief, super().py_bindings(self.name))

