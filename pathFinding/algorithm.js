function drawRoute(node){
    if(node.father.isStart){
        return;
    }
    node.father.span.style.backgroundColor="rgba(180, 180, 0,0.5)";
    drawRoute(node.father);
}

function drawRoute_(node){
    let length=1;
    let drawNode=node;
    let drawtime=setInterval(draw,25);
    function draw(){
        if(drawNode.father.isStart){
            clearInterval(drawtime);
            totalLength=length;
            updateInfo();
            return;
        }
        drawNode.father.span.style.backgroundColor="rgba(255, 220, 30,0.6)";
        drawNode=drawNode.father;
        length++;
    }
}

function breadthFirst(){
    let openList=[startNode];
    let closeList=[];
    while(openList.length>0){
        let node=openList.pop();
        if(node.isEnd){
            return node;
        }
        if(node.up){
            if(!openList.includes(node.up)&&!closeList.includes(node.up)){
                openList.push(node.up);
                node.up.father=node;
            }
        }
        if(node.under){
            if(!openList.includes(node.under)&&!closeList.includes(node.under)){
                openList.push(node.under);
                node.under.father=node;
            }
        }
        if(node.left){
            if(!openList.includes(node.left)&&!closeList.includes(node.left)){
                openList.push(node.left);
                node.left.father=node;
            }
        }
        if(node.right){
            if(!openList.includes(node.right)&&!closeList.includes(node.right)){
                openList.push(node.right);
                node.right.father=node;
            }
        }
        closeList.push(node);
    }
}

function breadthFirst_(startNode){
    let openList=[startNode];
    let closeList=[];
    function judgeNode(nextNode,node){
        if(nextNode){
            if(nextNode.isEnd){
                nextNode.father=node;
                clearInterval(timer);
                totalNode=closeList.length;
                drawRoute_(nextNode);
                return; 
            }
            if(!openList.includes(nextNode)&&!closeList.includes(nextNode)&&!nextNode.isBlock){
                openList.push(nextNode);
                nextNode.span.style.backgroundColor="rgba(0, 200, 0,0.2)";
                nextNode.father=node;
            }
        }
    }
    let timer=setInterval(search,16);
    function search(){
        if(openList.length>0){
            let node=openList.shift();
            if(node.up) judgeNode(node.up,node);
            if(node.under) judgeNode(node.under,node);
            if(node.left) judgeNode(node.left,node);
            if(node.right) judgeNode(node.right,node);
            closeList.push(node);
            if(!node.isStart) node.span.style.backgroundColor="rgba(0, 150, 200,0.3)";
        }
        else clearInterval(timer);
    }
}

function dijkstra_(startNode){
    let priorityArray=[{node:startNode,cost:0}];
    let closeList=[];

    //给优先队列增加一个按序插入的方法
    function addin(costNode){
        costNode.node.span.style.backgroundColor="rgba(0, 200, 0,0.2)";
        //如果队列为空直接插入
        if(priorityArray.length==0) {
            priorityArray.push(costNode);
            return;
        }
        for(let i=0;i<priorityArray.length;i++){
            //如果待插入点的代价比队列当前位置点的代价小则插入
            if(costNode.cost<=priorityArray[i].cost){
                priorityArray.splice(i,0,costNode);
                return;
            }
        }
        //到这一步表明待插入的元素代价最大
        priorityArray.push(costNode);
    }

    let judgeNode=function(nextNode,cost,fnode){
        //如果该点是终点则停止计时器
        if(!nextNode) return;
        if(nextNode.isEnd){
            nextNode.father=fnode;
            clearInterval(timer);
            totalNode=closeList.length;
            drawRoute_(nextNode);
            return; 
        }
        //判断该点是否已关闭或是障碍
        if(closeList.includes(nextNode) || nextNode.isBlock) return;
        //判断该点是否已经在优先队列
        for(let i=0;i<priorityArray.length;i++){
            if(priorityArray[i].node==nextNode){
                if(priorityArray[i].cost>cost){
                    priorityArray.splice(i,1);
                    addin({node:nextNode,cost:cost});
                    nextNode.father=fnode;
                    return;
                }
                else return; 
            }
        }
        addin({node:nextNode,cost:cost});
        nextNode.father=fnode;
    }

    let timer=setInterval(search,16);
    function search(){
        if(priorityArray.length>0){
            let costNode=priorityArray.shift();
            judgeNode(costNode.node.up,costNode.cost+1,costNode.node);
            judgeNode(costNode.node.under,costNode.cost+1,costNode.node);
            judgeNode(costNode.node.left,costNode.cost+1,costNode.node);
            judgeNode(costNode.node.right,costNode.cost+1,costNode.node);
            closeList.push(costNode.node);
            if(!costNode.node.isStart) costNode.node.span.style.backgroundColor="rgba(0, 150, 200,0.3)";
        }
        else clearInterval(timer);
    }
}

function greedSearch(startNode,endNode){
    let endx=endNode.x,endy=endNode.y;
    let priorityArray=[{node:startNode,
        distinct:Math.abs(startNode.x-endx)+Math.abs(startNode.y-endy)}];
    let closeList=[];

    function addin(dNode){
        dNode.node.span.style.backgroundColor="rgba(0, 200, 0,0.2)";
        if(priorityArray.length==0) {
            priorityArray.push(dNode);
            return;
        }
        for(let i=0;i<priorityArray.length;i++){
            if(dNode.distinct<=priorityArray[i].distinct){
                priorityArray.splice(i,0,dNode);
                return;
            }
        }
        priorityArray.push(dNode);
    }

    let judgeNode=function(nextNode,fnode){
        if(!nextNode) return;
        if(nextNode.isEnd){
            nextNode.father=fnode;
            clearInterval(timer);
            totalNode=closeList.length;
            drawRoute_(nextNode);
            return; 
        }
        if(closeList.includes(nextNode) || nextNode.isBlock) return;
        for(let i=0;i<priorityArray.length;i++){
            if(priorityArray[i].node==nextNode) return; 
        }
        addin({node:nextNode,distinct:Math.abs(nextNode.x-endx)+Math.abs(nextNode.y-endy)});
        nextNode.father=fnode;
    }

    let timer=setInterval(search,16);
    function search(){
        if(priorityArray.length>0){
            let dNode=priorityArray.shift();
            judgeNode(dNode.node.up,dNode.node);
            judgeNode(dNode.node.under,dNode.node);
            judgeNode(dNode.node.left,dNode.node);
            judgeNode(dNode.node.right,dNode.node);
            closeList.push(dNode.node);
            if(!dNode.node.isStart) dNode.node.span.style.backgroundColor="rgba(0, 150, 200,0.3)";
        }
        else clearInterval(timer);
    }

}

function AstarSearch(startNode,endNode){
    let Dweight=1;
    let abs=(num)=>Math.abs(num);
    let sx=startNode.x,sy=startNode.y,ex=endNode.x,ey=endNode.y;
    let priorityArray=[{node:startNode,distinct:(abs(sx-ex)+abs(sy-ey))*Dweight,cost:0}];
    let closeList=[];

    function addin(dNode){
        dNode.node.span.style.backgroundColor="rgba(0, 200, 0,0.2)";
        if(priorityArray.length==0) {
            priorityArray.push(dNode);
            return;
        }
        for(let i=0;i<priorityArray.length;i++){
            if(dNode.distinct+dNode.cost<=priorityArray[i].distinct+priorityArray[i].cost){
                priorityArray.splice(i,0,dNode);
                return;
            }
        }
        priorityArray.push(dNode);
    }

    let judgeNode=function(nextNode,cost,fnode){
        if(!nextNode) return;
        if(nextNode.isEnd){
            nextNode.father=fnode;
            clearInterval(timer);
            totalNode=closeList.length;
            drawRoute_(nextNode);
            return; 
        }
        if(closeList.includes(nextNode) || nextNode.isBlock) return;
        let N=cost+(abs(nextNode.x-ex)+abs(nextNode.y-ey))*Dweight;
        for(let i=0;i<priorityArray.length;i++){
            if(priorityArray[i].node==nextNode){
                if(priorityArray[i].distinct+priorityArray[i].cost>N){
                    priorityArray.splice(i,1);
                    addin({node:nextNode,distinct:(abs(nextNode.x-ex)+abs(nextNode.y-ey))*Dweight,cost:cost});
                    nextNode.father=fnode;
                    return;
                }
                else return; 
            } 
        }
        addin({node:nextNode,distinct:(abs(nextNode.x-ex)+abs(nextNode.y-ey))*Dweight,cost:cost});
        nextNode.father=fnode;
    }

    let timer=setInterval(search,16);
    function search(){
        if(priorityArray.length>0){
            let dNode=priorityArray.shift();
            judgeNode(dNode.node.up,dNode.cost+1,dNode.node);
            judgeNode(dNode.node.under,dNode.cost+1,dNode.node);
            judgeNode(dNode.node.left,dNode.cost+1,dNode.node);
            judgeNode(dNode.node.right,dNode.cost+1,dNode.node);
            closeList.push(dNode.node);
            if(!dNode.node.isStart) dNode.node.span.style.backgroundColor="rgba(0, 150, 200,0.3)";
        }
        else clearInterval(timer);
    }

}