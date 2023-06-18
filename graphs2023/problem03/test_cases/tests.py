import networkx as nx
import matplotlib.pyplot as plt


def draw_digraph_from_data(edgelist, fname = "case0"):
    g = nx.DiGraph()
    g.add_edges_from(edgelist)

    components = sorted(nx.strongly_connected_components(g), key = len, reverse = True)

    color_map = []
    for node in g.nodes():
        for i, component in enumerate(components):
            if node in component:
                color_map.append(i)

    pos = nx.spring_layout(g) 
    nx.draw(g, pos, node_color=color_map, with_labels=True)
    plt.savefig(fname+".png")
    plt.show()

edgelist1 = [(0,1), (0,2), (0,4), (1,6), (2,5), (2,6), (3,7), (5,6), (6,2), (6,4), (7,6)]

draw_digraph_from_data(edgelist1, "case1")
