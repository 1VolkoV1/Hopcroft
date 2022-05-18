import json
import pydot
import sys
import os



os.environ["PATH"] += os.pathsep + 'C:' + os.pathsep + 'Program Files' + os.pathsep + 'Graphviz' + os.pathsep + 'bin'
# prepare data like so: echo "a(aa)*b(bb)*" | ./a.out > test.json

filename = sys.argv[1] if len(sys.argv)>1 else 'test.json'
with open(filename, 'r') as f:
  data = json.load(f)
print(data)

graph = pydot.Dot('my_graph', graph_type='digraph', rankdir='LR')

graph.add_node(pydot.Node('\2', shape='point'))
for state in data['Q']:
  if state not in data['Q_f']:
    graph.add_node(pydot.Node(state, shape='circle'))
  else:
    graph.add_node(pydot.Node(state, shape='doublecircle'))

graph.add_edge(pydot.Edge('\2', data['q0'], arrowhead='normal', color='blue'))

for i, edge in enumerate(data['f']):
  for l, point in enumerate(edge):
    graph.add_edge(pydot.Edge(i, point, label=chr(data['T'][l]), arrowhead='normal', color='black'))

graph.write_png(sys.argv[2] if len(sys.argv)>2 else 'output.png')