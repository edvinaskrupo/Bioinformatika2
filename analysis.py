from ete3 import Tree

# Load the tree file generated from FastTree
tree = Tree("phylogenetic_tree.tree", format=1)

camel_virus_id = "lcl|Query_74706184901-8458MN514967.1DromedarycamelcoronavirusHKU23isolateDcCoV-HKU23/camel/Nigeria/NV1385/2016"
outgroup_node = tree.search_nodes(name=camel_virus_id)

if outgroup_node:
    tree.set_outgroup(outgroup_node[0])
    # Save the rooted tree to a new file
    tree.write(outfile="rooted_tree.tree", format=1)
    print("Rooted tree saved as 'rooted_tree.tree'")
else:
    print(f"Outgroup {camel_virus_id} not found in the tree.")
