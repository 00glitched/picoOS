import os
import re
import networkx as nx
from tree_sitter_language_pack import get_parser

parser_c = get_parser("c")
parser_bash = get_parser("bash")

G_calls = nx.DiGraph()
G_files = nx.DiGraph()
G_build = nx.DiGraph()

IGNORE_DIRS = {
    ".git",
    "build",
    "pico-sdk",
    "external",
    "lib",
    "third_party"
}

PROJECT_ROOT = os.path.abspath(".")

def inside_project(path):
    return os.path.abspath(path).startswith(PROJECT_ROOT)

def text(src, node):
    return src[node.start_byte:node.end_byte].decode()

def parse_c(path):
    with open(path, "rb") as f:
        src = f.read()

    tree = parser_c.parse(src)
    root = tree.root_node

    current_func = None

    def walk(node):
        nonlocal current_func


        if node.type == "function_definition":
            decl = node.child_by_field_name("declarator")
            name = text(src, decl).split("(")[0].strip()
            current_func = name
            G_calls.add_node(name)


        if node.type == "call_expression" and current_func:
            callee = text(src, node.child_by_field_name("function"))

            if not callee.startswith("stdio") and not callee.startswith("gpio"):
                G_calls.add_edge(current_func, callee)


        if node.type == "preproc_include":
            inc = text(src, node)
            if '"' in inc:
                G_files.add_edge(path, inc)

        for c in node.children:
            walk(c)

    walk(root)

def parse_bash(path):
    with open(path, "rb") as f:
        src = f.read()

    tree = parser_bash.parse(src)
    root = tree.root_node

    def walk(node):
        if node.type == "command":
            cmd = text(src, node.children[0])
            G_build.add_edge(path, cmd)

        for c in node.children:
            walk(c)

    walk(root)

def parse_cmake(path):
    with open(path) as f:
        for line in f:
            m = re.search(r"target_link_libraries\((\w+)\s+(.+)\)", line)
            if m:
                target = m.group(1)
                libs = m.group(2).split()
                for lib in libs:
                    if "pico" not in lib:
                        G_build.add_edge(target, lib)

for root, dirs, files in os.walk("."):

    dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]

    for file in files:
        path = os.path.join(root, file)

        if file.endswith((".c", ".h")):
            parse_c(path)

        elif file.endswith(".sh"):
            parse_bash(path)

        elif "CMakeLists.txt" in file or file.endswith(".cmake"):
            parse_cmake(path)

nx.drawing.nx_pydot.write_dot(G_calls, "graphs/calls.dot")
nx.drawing.nx_pydot.write_dot(G_files, "graphs/includes.dot")
nx.drawing.nx_pydot.write_dot(G_build, "graphs/build.dot")

os.system("dot -Tpng graphs/calls.dot -o graphs/calls.png")
os.system("dot -Tpng graphs/includes.dot -o graphs/includes.png")
os.system("dot -Tpng graphs/build.dot -o graphs/build.png")
