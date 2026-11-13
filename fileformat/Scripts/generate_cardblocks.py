#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
generate_cardblocks.py
Génère des CardBlock .h / .cpp à partir de DataDefinitions.xml
Mode: rétro-compatible (style readesm / Qt)
Usage:
  python3 generate_cardblocks.py path/to/DataDefinitions.xml outdir
"""

import sys
import os
import xml.etree.ElementTree as ET
from textwrap import dedent

if len(sys.argv) != 3:
    print("Usage: generate_cardblocks.py DataDefinitions.xml outdir")
    sys.exit(2)

xml_path = sys.argv[1]
outdir = sys.argv[2]
os.makedirs(outdir, exist_ok=True)

def cpp_ident(name):
    return name[0].upper() + name[1:]

def safe_name(n):
    return n.replace("-", "_")

def field_cpp_type(tag, attrs):
    # map xml tag to C++ type (simple mapping, extend if needed)
    if tag == "RawData":
        return "RawData"
    if tag == "int":
        return "int"
    if tag == "TimeReal":
        return "TimeReal"
    if tag == "Subblocks":
        return "Subblocks"  # placeholder type if you have it
    # for named DataType -> assume <name> type exists as DataType class
    return cpp_ident(tag)

def field_member_name(attrs):
    # prefer 'name' attribute, otherwise derive
    return attrs.get("name") or attrs.get("type") or "field"

def generate_header(block_name, block_type, fields):
    class_name = block_name
    guard = f"FILEFORMAT_{class_name.upper()}_H"
    includes = set()
    includes.add('#include "CardBlock.h"')
    includes.add('#include "../Reporter/Reporter.h"')
    # add types that require special include
    for t, n, attrs in fields:
        if t == "RawData":
            includes.add('#include "../DataTypes/RawData.h"')
        elif t == "TimeReal":
            includes.add('#include "../DataTypes/TimeReal.h"')
        elif t == "Subblocks":
            includes.add('#include "../DataTypes/Subblocks.h"')
        else:
            # assume DataTypes in ../DataTypes/<Type>.h
            includes.add(f'#include "../DataTypes/{t}.h"')

    includes_text = "\n".join(sorted(includes))

    # members
    members = []
    for t, name, attrs in fields:
        cpp_t = field_cpp_type(t, attrs)
        mem = f"    {cpp_t} {name};"
        members.append(mem)
    members_text = "\n".join(members) if members else "    // no fields"

    # header template
    h = dedent(f'''\
    #pragma once
    #ifndef {guard}
    #define {guard}

    {includes_text}
    #include <QString>

    namespace FileFormat {{

    class {class_name} : public CardBlock {{
    public:
        {class_name}(int offset, int blockSize);

        QString className() const override;
        QString title() const override;
        void printOn(Reporter& report) const override;

    private:
{members_text}
    }};

    }} // namespace FileFormat

    #endif // {guard}
    ''')
    return h

def generate_cpp(block_name, block_type, fields):
    class_name = block_name
    # includes
    includes = [
        f'#include "{class_name}.h"',
        '#include "../Reporter/Reporter.h"',
    ]
    includes_text = "\n".join(includes)

    # init list: initialize members that are DataPointer-based as (offset + 5, blockSize - 5)
    init_lines = []
    for t, name, attrs in fields:
        if t == "RawData":
            init_lines.append(f"      , {name}(offset + 5, /*len*/ {attrs.get('length','0')})")
        elif t in ("TimeReal", "Subblocks"):
            # these classes likely have constructor DataPointer or (start)
            init_lines.append(f"      , {name}(DataPointer(offset + 5))")
        else:
            # assume DataType has ctor (DataPointer)
            init_lines.append(f"      , {name}(DataPointer(offset + 5))")

    init_block = "\n".join(init_lines)
    if init_block.startswith("      ,"):
        init_block = init_block[6:]  # remove first comma spacing and add proper init

    # printOn body: call appropriate report methods
    print_lines = []
    for t, name, attrs in fields:
        if t == "RawData":
            print_lines.append(f'    report.writeBlock({name}, QObject::tr("{name}"));')
        elif t == "int":
            print_lines.append(f'    report.tagValuePair("{name}", {name});')
        else:
            print_lines.append(f'    report.writeBlock({name}, QObject::tr("{name}"));')

    print_body = "\n".join(print_lines) if print_lines else "    // no fields to print"

    cpp = dedent(f'''\
    {includes_text}

    namespace FileFormat {{

    {class_name}::{class_name}(int offset, int blockSize)
        : CardBlock(offset, blockSize)
    ''')
    # add member initializers if any (use simpler initializer style to avoid comma issues)
    if fields:
        # create body that assigns members inside constructor
        cpp += "{\n"
        for t, name, attrs in fields:
            if t == "RawData":
                length = attrs.get("length", "0")
                cpp += f"    {name} = RawData(offset + 5, {length});\n"
            else:
                cpp += f"    {name} = {field_cpp_type(t, attrs)}(DataPointer(offset + 5));\n"
        cpp += "}\n\n"
    else:
        cpp += "{ }\n\n"

    cpp += dedent(f'''\
    QString {class_name}::className() const {{
        return "{class_name}";
    }}

    QString {class_name}::title() const {{
        return QObject::tr("{class_name}");
    }}

    void {class_name}::printOn(Reporter& report) const {{
    {print_body}
    }}

    }} // namespace FileFormat
    ''')
    return cpp

# parse xml
tree = ET.parse(xml_path)
root = tree.getroot()

# find all CardBlock elements
for cb in root.findall("CardBlock"):
    name = cb.get("name")
    type_attr = cb.get("type", "")
    content = cb.find("content")
    fields = []
    if content is not None:
        for field in content:
            tag = field.tag  # e.g. 'RawData', 'int', 'TimeReal', 'Subblocks', etc.
            attrs = field.attrib.copy()
            # normalize tag name: if tag is like 'int' keep it; if tag is element referencing DataType, tag might be the name itself
            if tag.lower() == "int":
                tname = "int"
            elif tag.lower() == "rawdata":
                tname = "RawData"
            elif tag.lower() == "subblocks":
                tname = "Subblocks"
            elif tag.lower() == "timerreal" or tag == "TimeReal":
                tname = "TimeReal"
            else:
                # If tag is an element whose tag is a DataType name (like FullCardNumber),
                # some xmls use the DataType name as the tag (ET yields it directly).
                tname = tag
            member = field_member_name(attrs)
            member = safe_name(member)
            fields.append((tname, member, attrs))

    # generate and write files
    header = generate_header(name, type_attr, fields)
    cpp = generate_cpp(name, type_attr, fields)

    hpath = os.path.join(outdir, f"{name}.h")
    cpath = os.path.join(outdir, f"{name}.cpp")
    with open(hpath, "w", encoding="utf-8") as fh:
        fh.write(header)
    with open(cpath, "w", encoding="utf-8") as fc:
        fc.write(cpp)

    print(f"Generated {hpath} and {cpath}")

print("Done.")
