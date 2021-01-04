"""
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
"""

# I haven't written parser to read from text file, just solving the challenge
# for the sample input
input_tuple = (
    ("light red", (1, "bright white"), (2, "muted yellow")),
    ("dark orange", (3, "bright white"), (4, "muted yellow")),
    ("bright white", (1, "shiny gold")),
    ("muted yellow", (2, "shiny gold"), (9, "faded blue")),
    ("shiny gold", (1, "dark olive"), (2, "vibrant plum")),
    ("dark olive", (3, "faded blue"), (4, "dotted black")),
    ("vibrant plum", (5, "faded blue"), (6, "dotted black")),
    ("faded blue",),
    ("dotted black",)
)

# Construct a dict (map) as a graph structure
def construct_dict(input):
    result = {}
    for row in input:
        result[input[0]] = row[1:]
    
    return result


# Test whether outer_bag can hold search_bag
def bag_contains(outer_bag_name, search_bag_name):
    if input[outer_bag_name].get(search_bag_name) is not None:
        return True
    else:
        for inner_bag_name in input[outer_bag_name].keys():
            if bag_contains(inner_bag_name, search_bag_name):
                return True
    return False


# Count the number of bags that are able to
# contain search bag
def count_num_carrier_bags(graph_dict, search_bag_name):
    res = 0
    for bag in graph_dict.keys():
        if bag_contains(bag, search_bag_name):
            res += 1

graph_dict = construct_dict(input_tuple)
count_num_carrier_bags(graph_dict, "shiny gold")


