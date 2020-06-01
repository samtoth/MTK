import tools.doxy.structure as structs

def import_doxy(xml_dir: str, projectName: str):
    index = structs.d_parser.import_xml(xml_dir + "/index.xml")
    indexRoot = index.getroot()
    project: structs.Object = structs.Object(name=projectName)
    refs = structs.__find_base_namespace_refs(indexRoot)
    for ref in refs:
        project.members.append(structs.Namespace(xml_dir, ref))
    return project
