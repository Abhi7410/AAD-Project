
class BinaryHeap {

    constructor() {
        this.heap = [];
    }

    insert(value) {
        console.log(value);
        this.heap.push(value);
        this.bubbleUp();
    }

    size() {
        return this.heap.length;
    }

    empty() {
        return (this.size() === 0);
    }

    //using iterative approach
    bubbleUp() {
        let index = this.size() - 1;

        while (index > 0) {
            let element = this.heap[index],
                parentIndex = Math.floor((index - 1) / 2),
                parent = this.heap[parentIndex];

            if (parent[0] >= element[0]) break;
            this.heap[index] = parent;
            this.heap[parentIndex] = element;
            index = parentIndex
        }
    }

    extractMax() {
        const max = this.heap[0];
        const tmp = this.heap.pop();
        if (!this.empty()) {
            this.heap[0] = tmp;
            this.sinkDown(0);
        }
        return max;
    }

    sinkDown(index) {

        let left = 2 * index + 1,
            right = 2 * index + 2,
            largest = index;
        const length = this.size();

        // console.log(this.heap[left], left, length, this.heap[right], right, length, this.heap[largest]);

        if (left < length && this.heap[left][0] > this.heap[largest][0]) {
            largest = left
        }
        if (right < length && this.heap[right][0] > this.heap[largest][0]) {
            largest = right
        }
        // swap
        if (largest !== index) {
            let tmp = this.heap[largest];
            this.heap[largest] = this.heap[index];
            this.heap[index] = tmp;
            this.sinkDown(largest)
        }
    }
}


onload = function () {
    // create a network
    let curr_data;
    const container = document.getElementById('mynetwork');
    const container2 = document.getElementById('mynetwork2');
    const genNew = document.getElementById('generate-graph');
    const solve = document.getElementById('solve');
    const temptext = document.getElementById('temptext');
    // initialise graph options
    const options = {
        edges: {
            arrows: {
                to: true
            },
            labelHighlightBold: true,
            font: {
                size: 18
            }
        },
        nodes: {
            font: '15px arial red',
            scaling: {
                label: true
            },
            shape: 'icon',
            icon: {
                face: 'FontAwesome',
                code: '\uf1ae',
                size: 45,
                color: 'black',
            }
        }
    };
    // initialize your network!
    let network = new vis.Network(container);
    network.setOptions(options);
    let network2 = new vis.Network(container2);
    network2.setOptions(options);
    const map1 = new Map();

    function createData(){
        const sz = Math.floor(Math.random() * 10) + 3

        // Adding people to nodes array
        let nodes = [];
        for(let i=1;i<=sz;i++){
            nodes.push({id:i, label:"P"+i})
        }
        nodes = new vis.DataSet(nodes);

      

        const edges = [];
        for(let i=1;i<=sz;i++){
            for(let j=i+1;j<=sz;j++){
                // Modifies the amount of edges added in the graph
               
                    // Controls the direction of cash flow on edge
                if (Math.random() > 0.5) {
                    edges.push({ from: i, to: j, label: String(Math.floor(Math.random() * 100) + 1) });
                    map1.set(i, j);
                }
                else {
                    edges.push({ from: j, to: i, label: String(Math.floor(Math.random() * 100) + 1) });
                    map1.set(j, i);
                }
                
            }
        }
        const data = {
            nodes: nodes,
            edges: edges
        };
        return data;
    }

    genNew.onclick = function () {
        const data = createData();
        curr_data = data;
        network.setData(data);
        temptext.style.display = "inline";
        container2.style.display = "none";
    };

    solve.onclick = function () {
        temptext.style.display  = "none";
        container2.style.display = "inline";
        const solvedData = solveData();
        network2.setData(solvedData);
    };

    function solveData() {
        let data = curr_data;
        const sz = data['nodes'].length;
        const vals = Array(sz).fill(0);
        // Calculating net balance of each person
        for (let i = 0; i < data['edges'].length; i++) {
            const edge = data['edges'][i];
            vals[edge['to'] - 1] += parseInt(edge['label']); // Adding to the balance of the person
            vals[edge['from'] - 1] -= parseInt(edge['label']); // Subtracting from the balance of the person
        }

        const pos_heap = new BinaryHeap(); //positive goes in  (givers)
        const neg_heap = new BinaryHeap();// negative goes in  (receviers)
 
        for (let i = 0; i < sz; i++) {
            if (vals[i] > 0) {
                pos_heap.insert([vals[i], i]);  //all givers in one subset
            } else {
                neg_heap.insert(([-vals[i], i])); //all reveivers in another subset
                vals[i] *= -1;
            }
        }

        const new_edges = [];
        while (!pos_heap.empty() && !neg_heap.empty()) {
            const mx = pos_heap.extractMax();
            const mn = neg_heap.extractMax();
            // if (map1.get(mx[1]) == mn[1] || map1.get(mn[1]) == mx[1]) {
            //     {
                    const amt = Math.min(mx[0], mn[0]);
                    const to = mx[1];
                    const from = mn[1];

                    new_edges.push({ from: from + 1, to: to + 1, label: String(Math.abs(amt)) });
                    vals[to] -= amt;
                    vals[from] -= amt;

                    if (mx[0] > mn[0]) {
                        pos_heap.insert([vals[to], to]);
                    } else if (mx[0] < mn[0]) {
                        neg_heap.insert([vals[from], from]);
                    }
                }
            // }

            data = {
                nodes: data['nodes'],
                edges: new_edges
            };
            return data;
        }

        genNew.click();
    // }
};
