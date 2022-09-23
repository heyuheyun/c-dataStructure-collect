const width = window.innerWidth;
const height = window.innerHeight;
//每个格子的大小
const cellLength = 30;
const lineNum = Math.trunc(height / cellLength);
const rowNum = Math.trunc(width / cellLength);

const nodeList = [];
var selectMode = 0;
var startNode = null;
var endNode = null;

var totalLength = 0;
var totalNode = 0;

function init() {
    document.getElementById("getBreadthFirst").onclick = () => {
        clearColor();
        breadthFirst_(startNode);
    };
    document.getElementById("getDijkstra").onclick = () => {
        clearColor();
        dijkstra_(startNode);
    };
    document.getElementById("getGreedSearch").onclick = () => {
        clearColor();
        greedSearch(startNode, endNode);
    };
    document.getElementById("getAstar").onclick = () => {
        clearColor();
        AstarSearch(startNode, endNode);
    };

    for (let i = 0; i < lineNum; i++) {
        for (let j = 0; j < rowNum; j++) {
            let node = new MapNode(j, i);
            nodeList.push(node);
        }
    }
    for (let i = 0; i < lineNum; i++) {
        for (let j = 0; j < rowNum; j++) {
            //左节点：只有j！=0的结点有左节点  右节点：只有j！=（rowNum-1）的结点有右结点
            //上节点：i！=0  下结点：i！=（lineNum-1）
            let node = nodeList[i * rowNum + j];
            if (j) node.left = nodeList[i * rowNum + j - 1];
            if (j < rowNum - 1) node.right = nodeList[i * rowNum + j + 1];
            if (i) node.up = nodeList[(i - 1) * rowNum + j];
            if (i < lineNum - 1) node.under = nodeList[(i + 1) * rowNum + j];
        }
    }

    startNode = nodeList[Math.trunc(((lineNum - 1) / 2) * rowNum + rowNum / 3)];
    endNode = nodeList[Math.trunc(((lineNum - 1) / 2) * rowNum + (rowNum / 3) * 2)];
    startNode.isStart = true;
    startNode.span.style.backgroundColor = "rgb(180, 0, 0)";
    endNode.isEnd = true;
    endNode.span.style.backgroundColor = "rgb(0, 0, 180)";
    startNode.span.onclick = () => {
        changeSelect(1);
    };
    endNode.span.onclick = () => {
        changeSelect(2);
    };
}

function changeSelect(i) {
    event.stopPropagation();
    selectMode = i;
    document.body.style.cursor = "pointer";
}

class MapNode {
    constructor(x, y) {
        this.isStart = false;
        this.isEnd = false;
        this.x = x;
        this.y = y;
        this.up = null;
        this.under = null;
        this.left = null;
        this.right = null;
        this.isBlock = false;
        this.father = null;
        this.creatSpan();
    }

    creatSpan() {
        this.span = document.createElement("span");
        /* this.span.innerHTML=`${this.x},${this.y}`; */
        document.getElementById("spanList").appendChild(this.span);
    }
}

function clearColor() {
    nodeList.forEach(node => {
        if (!node.isEnd && !node.isStart && !node.isBlock) node.span.style.backgroundColor = "";
    });
}
function clearBlock() {
    nodeList.forEach(node => {
        if (!node.isEnd && !node.isStart) {
            node.isBlock = false;
            node.span.style.backgroundColor = "";
            node.span.style.animation = "";
        }
    });
}
function updateInfo() {
    document.getElementById("lengthP").innerHTML = `总距离:${totalLength}`;
    document.getElementById("nodeSumP").innerHTML = `总探测结点:${totalNode}`;
}

document.body.onclick = event => {
    let i = Math.trunc(event.pageY / cellLength);
    let j = Math.trunc(event.pageX / cellLength);
    let node = nodeList[i * rowNum + j];

    if (selectMode == 1) {
        startNode.isStart = false;
        startNode.span.style.backgroundColor = "";
        startNode.span.onclick = null;

        startNode = node;
        startNode.isStart = true;
        startNode.isBlock = false;
        startNode.isEnd = false;
        startNode.span.style.backgroundColor = "rgb(180, 0, 0)";
        startNode.span.onclick = () => {
            changeSelect(1);
        };
        document.body.style.cursor = "default";
        selectMode = 0;
        return;
    }
    if (selectMode == 2) {
        endNode.isEnd = false;
        endNode.span.style.backgroundColor = "";
        endNode.span.onclick = null;

        endNode = node;
        endNode.isStart = false;
        endNode.isBlock = false;
        endNode.isEnd = true;
        endNode.span.style.backgroundColor = "rgb(0, 0, 180)";
        endNode.span.onclick = () => {
            changeSelect(2);
        };
        document.body.style.cursor = "default";
        selectMode = 0;
        return;
    }
};

document.body.onmousedown = function () {
    event.preventDefault();
    let i = Math.trunc(event.pageY / cellLength);
    let j = Math.trunc(event.pageX / cellLength);
    let node = nodeList[i * rowNum + j];
    let moveflag = false;
    document.body.onmousemove = function () {
        moveflag = true;
        i = Math.trunc(event.pageY / cellLength);
        j = Math.trunc(event.pageX / cellLength);
        node = nodeList[i * rowNum + j];
        if (!node.isBlock && !node.isStart && !node.isEnd) {
            node.isBlock = true;
            node.span.style.backgroundColor = "rgb(170, 170, 170)";
            node.span.style.animation = "spanan 0.5s";
        }
    };
    document.body.onmouseup = function () {
        document.body.onmousemove = null;
        if (!moveflag) {
            node.isBlock = false;
            node.span.style.backgroundColor = "";
            node.span.style.animation = "";
        }
    };
};

init();
