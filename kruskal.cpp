#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

struct Edge {
    int a;
    int b;
    int weight;
};

//hash-table based disjoint set
class disjoint_set {
private:
    struct Item {
        int data;
        int parent;
        int rank;
    };
    std::vector<Item> item_list;
public:
    disjoint_set(int num_of_nodes) {
        for (int i = 0; i < num_of_nodes; ++i) {
            Item current_item;
            current_item.data = i;
            current_item.parent = i;
            current_item.rank = 0;
            item_list.push_back(current_item);
        }
    }

    int Find(int item) {
        if (item_list[item].parent == item)
            return item;
        else {
            item_list[item].parent = Find(item_list[item].parent);  // path compression
            return item_list[item].parent;
        }
    }

    void Union(int set1, int set2) {    // union by rank
        set1 = Find(set1);
        set2 = Find(set2);
        int rank1 = item_list[set1].rank;
        int rank2 = item_list[set2].rank;
        if (rank1 > rank2)
            item_list[set2].parent = set1;
        else if (rank2 > rank1)
            item_list[set1].parent = set2;
        else {
            item_list[set2].parent = set1;
            ++(item_list[set1].rank);
        }
    }

};


int main() {

    int num_of_villages;
    scanf("%d\n", &num_of_villages);

    std::vector <Edge> distance_list((num_of_villages * num_of_villages - num_of_villages) / 2);
    std::vector <Edge> outp_edge_list(num_of_villages - 1);

    // read in distance matrix
    const int max_line_size = 2500 * 8;
    int row_cnt = 0;
    int col_cnt = 0;
    char inp_buffer[max_line_size], *str, *endptr;
    long current_dist;
    int dist_list_iter = 0;

    while (fgets(inp_buffer, sizeof(inp_buffer), stdin)) {
        str = inp_buffer;
        col_cnt = 0;
        for (str = inp_buffer; ; str = endptr) {
            current_dist = strtol(str, &endptr, 10);
            if (str == endptr)
                break;
            if (col_cnt > row_cnt) {
                Edge current_edge = { row_cnt, col_cnt, current_dist };
                distance_list[dist_list_iter] = current_edge;  // w assignment
                ++dist_list_iter;
            }
            ++col_cnt;
        }
        ++row_cnt;

    }

    // Sort distance list

    std::sort(distance_list.begin(), distance_list.end(),
        [](Edge const &a, Edge const &b) { return a.weight < b.weight; });

    // Kruskal

    disjoint_set villages(num_of_villages);

    int outp_list_cnt = 0;
    for (auto distance_list_elem : distance_list) {
        int u = distance_list_elem.a;
        int v = distance_list_elem.b;
        if (villages.Find(u) != villages.Find(v)) {
            Edge current_edge = {u, v};
            outp_edge_list[outp_list_cnt] = current_edge;
            villages.Union(u, v);
            ++outp_list_cnt;
        }
    }


    for (auto edge : outp_edge_list) {
        printf("%d %d\n", edge.a + 1, edge.b + 1);
    }

    return 0;
}
