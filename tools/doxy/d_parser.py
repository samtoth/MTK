import xml.etree.ElementTree as ET


def import_xml(file: str) -> ET.ElementTree:
    tree = ET.parse(file)
    return tree


def get_elem_inner_to_string(elem: ET.Element):
    return "".join([str(ET.tostring(e)) for e in elem])


def print_tree(elem, index: int):
    text = ""
    if index > 1:
        for i in range(0, index - 1):
            text += "   "
        text += "->"

    print(text, elem.text, elem.tag, elem.attrib)

    for child in elem:
        print_tree(child, index + 1)
