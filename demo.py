import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
n, m = map(int, input().split())

for i in range(m):
    a, b, c = map(float, input().split())
    a = int(a)
    b = int(b)
    G.add_edge(a, b, weight=c)

pos = nx.spring_layout(G)
options = {

    "node_size": 300,
    "width": 2,
}
nx.draw(G, pos, with_labels=True, font_weight="bold", **options)
edge_labels = {(u, v): f"{d['weight']:.2f}" for u, v, d in G.edges(data=True)}
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color='red')
plt.savefig("path.png", bbox_inches='tight', dpi=150)
