// cycle_finder_new.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <set>

int adjMat[27][27] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //Adjacency matrix init
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

std::unordered_map<int, std::tuple<int, int, int, int>> nodemap; //hashmap for all nodes; key=node number, value=tuple
std::unordered_map<int, std::vector<int>> edgemap;// hashmap for all edges (reduces chek speed to O(1) from O(log(n)) in std::set
int tree_id = 1;// A tree id genreating variable
std::vector<int> collapse_List;//List of nodes to be collapsed. currently the game assumes freedom of the next player to collapse the node that the player wants. Makes programmer's job easier.. :P

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> edgelist;//List of all edges connecting the cycled grapph (includes branches)



void showMat(int adjMat[27][27]) {//Helper function to Help us visualize whats happening, good for debugging
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            std::cout << adjMat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void showMap(std::unordered_map<int, std::tuple<int, int, int, int>> nodemap, int n) {//Helper function to Help us visualize whats happening, good for debugging
    for (int i = 1; i <= n; i++) {
        std::cout << i << ": " << std::get<0>(nodemap[i]) << " " << std::get<1>(nodemap[i]) << " " << std::get<2>(nodemap[i]) << std::endl;
    }
}
void showMap(std::unordered_map<int, std::vector<int>> map, int n) {//Helper function to Help us visualize whats happening, good for debugging

    for (int i = 1; i <= n; i++) {
        std::vector<int>a = map.at(i);
        std::cout << i << ": ";
        for (auto x : a) {
            std::cout << x << " ";
        }
        std::cout << std::endl;

    }
}

void showvec(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> a, int n) {//Helper function to Help us visualize whats happening, good for debugging
    for (int i = 0; i < n; i++) {
        std::cout << a[i].first.first << "," << a[i].second.second << std::endl;
    }
}
void updateTree(int update_tree_id, int tree_id_to_update) {   //A function that will update the id value of a tree when 2 trees get connected
    for (int i = 1; i <= 27; i++) {
        if (std::get<2>(nodemap[i]) == tree_id_to_update) {
            std::get<2>(nodemap[i]) = update_tree_id;
        }
    }
}
bool insertEdgeAndCheck(int a, int b) {
    adjMat[a][b] = 1; //make the edge
    adjMat[b][a] = 1; //make the edge
    if (std::get<0>(nodemap[a]) == 0 and std::get<0>(nodemap[b]) == 0) {
        //check case 1, tree formation O(1)
        std::get<0>(nodemap[a]) = 1;
        std::get<0>(nodemap[b]) = 1;
        std::get<1>(nodemap[a]) -= 1;
        std::get<1>(nodemap[b]) -= 1;
        std::get<2>(nodemap[a]) = tree_id;
        std::get<2>(nodemap[b]) = tree_id;
        tree_id++;
        edgemap.insert({ a,{b} });
        edgemap.insert({ b,{a} });
        return false;
    }
    else if (std::get<0>(nodemap[a]) == 1 and std::get<0>(nodemap[b]) == 0) {
        //case 2 tree extension O(1)
        std::get<0>(nodemap[b]) = 1;
        std::get<1>(nodemap[a]) -= 1;
        std::get<1>(nodemap[b]) -= 1;
        std::get<2>(nodemap[b]) = std::get<2>(nodemap[a]);
        edgemap.at(a).push_back(b);
        edgemap.insert({ b,{a} });
        return false;
    }
    else if (std::get<0>(nodemap[a]) == 0 and std::get<0>(nodemap[b]) == 1) {
        //case 2 but with other edge O(1)
        std::get<0>(nodemap[a]) = 1;
        std::get<1>(nodemap[a]) -= 1;
        std::get<1>(nodemap[b]) -= 1;
        std::get<2>(nodemap[a]) = std::get<2>(nodemap[b]);
        edgemap.at(b).push_back(a);
        edgemap.insert({ a,{b} });
        return false;
    }
    else if (std::get<0>(nodemap[a]) == 1 and std::get<0>(nodemap[b]) == 1 and std::get<2>(nodemap[a]) == std::get<2>(nodemap[b])) {
        //case 3 cycle formation O(1)
        std::get<1>(nodemap[a]) -= 1;
        std::get<1>(nodemap[b]) -= 1;
        edgemap.at(b).push_back(a);
        edgemap.at(a).push_back(b);
        return true;
    }
    else if (std::get<0>(nodemap[a]) == 1 and std::get<0>(nodemap[b]) == 1 and std::get<2>(nodemap[a]) != std::get<2>(nodemap[b])) {
        //case 4 joining 2 trees O(alpha) alpha<n
        std::get<1>(nodemap[a]) -= 1;
        std::get<1>(nodemap[b]) -= 1;
        edgemap.at(b).push_back(a);
        edgemap.at(a).push_back(b);
        int update_tree_id = std::min(std::get<2>(nodemap[b]), std::get<2>(nodemap[a]));
        int tree_id_to_update = std::max(std::get<2>(nodemap[b]), std::get<2>(nodemap[a]));
        updateTree(update_tree_id, tree_id_to_update);

        return false;
    }
}

void returnCycle(int a) {
    //returns the edges in cycle and list of nodes to collapse O(n^2)
    if (std::get<3>(nodemap.at(a)) == 1) {
        return;
    }
    collapse_List.push_back(a);
    std::get<3>(nodemap.at(a)) = 1;
    std::vector<int> neighbors = edgemap.at(a);

    for (auto i : neighbors) {
        if (std::get<3>(nodemap.at(a)) == 1 && std::get<3>(nodemap.at(i)) == 1) {
            continue;
        }
        adjMat[a][i] = 2;
        adjMat[i][a] = 2;
        edgelist.push_back({ { i,a }, {i,a} });

        returnCycle(i);
    }
}

void collapse_List_Maker(int i) {
    //O(n) method to just return the list of nodes to collapse incomplete as of now
//    for (int i = 0; i < 27; i++) {
//        if (nodemap.at(i))
//    }
}
int main()
{

    for (int i = 1; i <= 27; i++) {
        //creating the nodemap
        std::tuple<int, int, int, int> node(0, 26, 0, 0);
        nodemap[i] = node;
    }


    insertEdgeAndCheck(1, 2); //testing
    insertEdgeAndCheck(3, 2); //testing
    insertEdgeAndCheck(3, 4); //testing
    insertEdgeAndCheck(5, 4); //testing
    insertEdgeAndCheck(5, 6); //testing
    insertEdgeAndCheck(5, 7); //testing
    insertEdgeAndCheck(1, 5); //testing
    insertEdgeAndCheck(9, 10); //testing
    insertEdgeAndCheck(11, 27); //testing
    returnCycle(5); //testing


    for (auto n : collapse_List) {
        std::cout << n << " ";
    }


}