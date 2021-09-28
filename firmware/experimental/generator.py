# Copyright (c) 2021 Alethea Katherine Flowers.
# Published under the standard MIT License.
# Full text available at: https://opensource.org/licenses/MIT

import ast
import os
import sys

HERE = os.path.abspath(os.path.dirname(__file__))

class NodeInst:
    def __init__(self, name, id, fn, args):
        self.name = name
        self.id = id
        self.fn = fn
        self.args = args

    def __str__(self):
        return f"{self.id}: {self.name} = {self.fn}({self.args})"


class Connection:
    def __init__(self, src, src_port, dst, dst_port):
        self.src = src
        self.src_port = src_port
        self.dst = dst
        self.dst_port = dst_port

    def __str__(self):
        return f"{self.src.name}[{self.src_port}] -> {self.dst.name}[{self.dst_port}]"


class FlowVisitor(ast.NodeVisitor):
    def __init__(self):
        super().__init__()
        self.nodes = {}
        self.connections = []

    def generic_visit(self, node):
        super().generic_visit(node)

    def visit_Assign(self, node):
        name = node.targets[0].id

        id = len(self.nodes)
        fn = node.value.func.id
        args = {
            kwarg.arg: ast.literal_eval(kwarg.value) for kwarg in node.value.keywords
        }

        assert name not in self.nodes
        self.nodes[name] = NodeInst(name, id, fn, args)

    def visit_Compare(self, node):
        source_node_name = node.left.value.id
        source_port = ast.literal_eval(node.left.slice)
        dest_node_name = node.comparators[0].value.id
        dest_port = ast.literal_eval(node.comparators[0].slice)

        source_node = self.nodes[source_node_name]
        dest_node = self.nodes[dest_node_name]

        self.connections.append(
            Connection(source_node, source_port, dest_node, dest_port)
        )


def parse(source):
    tree = ast.parse(source)

    visitor = FlowVisitor()
    visitor.visit(tree)

    return list(visitor.nodes.values()), visitor.connections


def generate_c(nodes, connections, fh):
    print("#include \"generated_flow.h\"", file=fh)
    print("void generated_flow_init(struct CurrentsFlow* flow, struct FlowNodeState* states) {", file=fh)

    nodes.sort(key=lambda x: x.id)

    # Sort the connections to build a perfect hash map so the C code
    # can efficiently look up connections.
    connections_by_src_id = sorted(
        [(cxn.src.id, cxn.src_port, cxn) for cxn in connections], key=lambda x: x[:2]
    )
    connection_offsets = {}

    for n, (src_id, src_port, _) in enumerate(connections_by_src_id):
        connection_offsets.setdefault((src_id, src_port), n)

    for node in nodes:
        print(
            f"""\
/* {node.name} */
flow->nodes[{node.id}] = (struct CurrentsNode){{
    .id = {node.id},
    .fn = {node.fn}_fn,
    .link_offsets = {{
        {connection_offsets.get((node.id, 0), 0)},
        {connection_offsets.get((node.id, 1), 0)},
        {connection_offsets.get((node.id, 2), 0)},
        {connection_offsets.get((node.id, 3), 0)},
    }}
}};
""",
            file=fh,
        )
        for name, value in node.args.items():
            print(f"states[{node.id}].{node.fn}.{name} = {value};", file=fh)

        print("", file=fh)

    for n, (_, _, cxn) in enumerate(connections_by_src_id):
        print(
            f"flow->links[{n}] = (struct CurrentsLink){{.src_id = {cxn.src.id}, .src_port = {cxn.src_port}, .dst_id = {cxn.dst.id}, .dst_port = {cxn.dst_port}}};",
            file=fh,
        )

    print("}", file=fh)


def main():
    nodes, connections = parse(open(os.path.join(HERE, "midi.flow"), "r").read())

    with open(sys.argv[1], "w") as fh:
        generate_c(nodes, connections, fh)


if __name__ == "__main__":
    main()
