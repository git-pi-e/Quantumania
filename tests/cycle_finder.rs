let mut nodemap:HashMap<i32, (i32,i32,i32,i32)> = HashMap::new(); //hashmap for all nodes; key=node number, value=tuple
	let mut edgemap:HashMap<i32, Vec<i32>> = HashMap::new();// hashmap for all edges (reduces chek speed to O(1) from O(log(n)) in std::set
	let mut tree_id:i32 = 1;// A tree id genreating variable
	let mut collapse_List:Vec<i32> = Vec::new();//List of nodes to be collapsed. currently the game assumes freedom of the next player to collapse the node that the player wants. Makes programmer's job easier.. :P
	let mut edgelist:Vec<((i32, i32),(i32, i32))> = Vec::new();//List of all edges connecting the cycled grapph (includes branches)

let mut nodemap: HashMap<i32, (i32, i32, i32, i32)> = HashMap::new(); //hashmap for all nodes; key=node number, value=tuple
let mut edgemap: HashMap<i32, Vec<i32>> = HashMap::new(); // hashmap for all edges (reduces chek speed to O(1) from O(log(n)) in std::set
let mut tree_id: i32 = 1; // A tree id genreating variable
let mut collapse_List: Vec<i32> = Vec::new(); //List of nodes to be collapsed. currently the game assumes freedom of the next player to collapse the node that the player wants. Makes programmer's job easier.. :P
let mut edgelist: Vec<((i32, i32), (i32, i32))> = Vec::new(); //List of all edges connecting the cycled grapph (includes branches)

fn show_mat(adj_mat: [[i32; 27]; 27]) { //Helper function to Help us visualize whats happening, good for debugging
    for i in 0..27 {
        for j in 0..27 {
            print!("{} ", adj_mat[i][j]);
        }
        println!();
    }
}

fn show_map(nodemap: HashMap<i32, (i32, i32, i32, i32)>, n: i32) { //Helper function to Help us visualize whats happening, good for debugging
    for i in 1..=n {
        println!("{}: {} {} {}", i, nodemap[&i].0, nodemap[&i].1, nodemap[&i].2);
    }
}

fn show_map(map: HashMap<i32, Vec<i32>>, n: i32) { //Helper function to Help us visualize whats happening, good for debugging
    for i in 1..=n {
        let a: Vec<i32> = map[&i].clone();
        print!("{}: ", i);
        for x in a {
            print!("{} ", x);
        }
        println!();
    }
}

fn showvec(a: &Vec<((i32, i32), (i32, i32))>, n: i32) { //Helper function to Help us visualize whats happening, good for debugging
    for i in 0..n {
        println!("{},{}", a[i as usize].0 .0, a[i as usize].1 .1);
    }
}
fn updateTree(update_tree_id: i32, tree_id_to_update: i32) {   //A function that will update the id value of a tree when 2 trees get connected
    for i in 1..=27 {
        if nodemap[i as usize].2 == tree_id_to_update {
            nodemap[i as usize].2 = update_tree_id;
        }
    }
}

fn insert_edge_and_check(a: usize, b: usize, nodemap: &mut Vec<(usize, i32, usize)>, tree_id: &mut usize, edgemap: &mut HashMap<usize, Vec<usize>>, adj_mat: &mut Vec<Vec<i32>>) -> bool {
    adj_mat[a][b] = 1; //make the edge
    adj_mat[b][a] = 1; //make the edge
    if nodemap[a].0 == 0 && nodemap[b].0 == 0 {
        //check case 1, tree formation O(1)
        nodemap[a].0 = 1;
        nodemap[b].0 = 1;
        nodemap[a].1 -= 1;
        nodemap[b].1 -= 1;
        nodemap[a].2 = *tree_id;
        nodemap[b].2 = *tree_id;
        *tree_id += 1;
        edgemap.insert(a, vec![b]);
        edgemap.insert(b, vec![a]);
        return false;
    }
    else if nodemap[a].0 == 1 && nodemap[b].0 == 0 {
        //case 2 tree extension O(1)
        nodemap[b].0 = 1;
        nodemap[a].1 -= 1;
        nodemap[b].1 -= 1;
        nodemap[b].2 = nodemap[a].2;
        edgemap.get_mut(&a).unwrap().push(b);
        edgemap.insert(b, vec![a]);
        return false;
    }
    else if nodemap[a].0 == 0 && nodemap[b].0 == 1 {
        //case 2 but with other edge O(1)
        nodemap[a].0 = 1;
        nodemap[a].1 -= 1;
        nodemap[b].1 -= 1;
        nodemap[a].2 = nodemap[b].2;
        edgemap.get_mut(&b).unwrap().push(a);
        edgemap.insert(a, vec![b]);
        return false;
    }
    else if nodemap[a].0 == 1 && nodemap[b].0 == 1 && nodemap[a].2 == nodemap[b].2 {
        //case 3 cycle formation O(1)
        nodemap[a].1 -= 1;
        nodemap[b].1 -= 1;
        edgemap.get_mut(&b).unwrap().push(a);
        edgemap.get_mut(&a).unwrap().push(b);
        return true;
    }
    else if (nodemap[a].0 == 1 && nodemap[b].0 == 1 && nodemap[a].2 != nodemap[b].2) {
        //case 4 joining 2 trees O(alpha) alpha<n
        nodemap[a].1 -= 1;
        nodemap[b].1 -= 1;
        edgemap[b].push(a);
        edgemap[a].push(b);
        let update_tree_id = nodemap[b].2.min(nodemap[a].2);
        let tree_id_to_update = nodemap[b].2.max(nodemap[a].2);
        updateTree(update_tree_id, tree_id_to_update);

        return false;
    }
    else {
        return false;
    }
}

fn return_cycle(a: int) {
    //returns the edges in cycle and list of nodes to collapse O(n^2)
    if nodemap[a].3 == 1 {
        return;
    }
    collapse_List.push(a);
    nodemap[a].3 = 1;
    let neighbors = edgemap[a];

    for i in neighbors {
        if nodemap[a].3 == 1 && nodemap[i].3 == 1 {
            continue;
        }
        adjMat[a][i] = 2;
        adjMat[i][a] = 2;
        edgelist.push({ { i,a }, {i,a} });

        return_cycle(i);
    }
}

fn collapse_List_Maker(i: int) {
    //O(n) method to just return the list of nodes to collapse incomplete as of now
   for (int i = 0; i < 27; i++) {
       if (nodemap.at(i))
   }
}

fn main() {
    for i in 1..=27 {
        //creating the nodemap
        let node: (i32, i32, i32, i32) = (0, 26, 0, 0);
        nodemap.insert(i, node);
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

    for n in collapse_list {
        println!("{} ", n);
    }
}