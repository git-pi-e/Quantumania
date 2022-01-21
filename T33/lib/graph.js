class Graph {
    constructor ( noOfVertices ) {
        this.noOfVertices = noOfVertices;
        this.AdjList = new Map();
    }

    addVertex ( v ) {
        this.AdjList.set( v, [] );
    }
    addEdge ( v, w ) {
        this.AdjList.get( v ).push( w );
        this.AdjList.get( w ).push( v );
    }
    printGraph () {
        // get all the vertices
        var get_keys = this.AdjList.keys();

        // iterate over the vertices
        for ( var i of get_keys ) {
            var get_values = this.AdjList.get( i );
            var conc = "";

            for ( var j of get_values )
                conc += j + " ";

            console.log( i + " -> " + conc );
        }
    }

    // bfs(v)
    // dfs(v)
}