const pi = Math.PI;
var width = window.innerWidth;
var height = window.innerHeight;
function random_int(start, end) {
    return parseInt(Math.random() * (end - start + 1) + start);
}

function init() {
    const canvas = document.getElementById("canvas");
    const ballMove = document.getElementById("ballMove");
    const bg = document.getElementById("bg");
    //初始化图层及创建画笔
    canvas.width = width;
    canvas.height = height;
    ballMove.width = width;
    ballMove.height = height;
    bg.width = width;
    bg.height = height;
    ctx = canvas.getContext("2d");
    ballCtx = ballMove.getContext("2d");
    bgCtx = bg.getContext("2d");
    ballCtx.fillStyle = "rgba(200,0,0,0.5)";

    allTime = 5; //控制小球的总运动时间
    bzArray = [];
    bz = new Bezier([50, 50], [150, 150], [500, 50]);
    bz.draw();
    bzArray.push(bz);
    drawbg();
}

class Bezier {
    constructor(startP, controlP, endP, isFirst = 1) {
        this.startP = startP;
        this.controlP = controlP;
        this.endP = endP;
        this.color = `rgba(${random_int(40, 240)},${random_int(40, 240)},${random_int(40, 240)},0.5)`;
        this.creatdiv(isFirst);
    }

    creatdiv(isFirst) {
        this.controlD = document.createElement("div");
        this.endD = document.createElement("div");
        this.controlD.style.left = this.controlP[0] + "px";
        this.controlD.style.top = this.controlP[1] + "px";
        this.endD.style.left = this.endP[0] + "px";
        this.endD.style.top = this.endP[1] + "px";
        this.controlD.style.backgroundColor = this.color;
        this.endD.style.backgroundColor = this.color;
        addDrag(this.controlD, this.controlP);
        addDrag(this.endD, this.endP);
        document.getElementById("pointList").appendChild(this.controlD);
        document.getElementById("pointList").appendChild(this.endD);
        if (isFirst) {
            this.startD = document.createElement("div");
            this.startD.style.left = this.startP[0] + "px";
            this.startD.style.top = this.startP[1] + "px";
            this.startD.style.backgroundColor = this.color;
            addDrag(this.startD, this.startP);
            document.getElementById("pointList").appendChild(this.startD);
        }
    }

    draw() {
        ctx.beginPath();
        ctx.moveTo(this.startP[0], this.startP[1]);
        ctx.quadraticCurveTo(this.controlP[0], this.controlP[1], this.endP[0], this.endP[1]);
        ctx.stroke();
        //绘制三个点
        ctx.fillStyle = "rgb(200,0,0)";
        ctx.beginPath();
        ctx.arc(this.controlP[0], this.controlP[1], 2, 0, pi * 2);
        ctx.fill();
        ctx.beginPath();
        ctx.arc(this.startP[0], this.startP[1], 2, 0, pi * 2);
        ctx.fill();
        ctx.beginPath();
        ctx.arc(this.endP[0], this.endP[1], 2, 0, pi * 2);
        ctx.fill();
    }
}

function addDrag(pDiv, syncP) {
    pDiv.onmousedown = function () {
        event.preventDefault();
        //点的拖动控制
        let ox = event.offsetX - 10;
        let oy = event.offsetY - 10;
        document.onmousemove = function () {
            pDiv.style.top = event.clientY - oy + "px";
            pDiv.style.left = event.clientX - ox + "px";
            syncP[0] = event.clientX - ox;
            syncP[1] = event.clientY - oy;
            ctx.clearRect(0, 0, width, height);
            bzArray.forEach(element => {
                element.draw();
            });
        };
        document.onmouseup = function () {
            document.onmousemove = null;
        };
    };
}

function add_point() {
    let bz = new Bezier(bzArray[bzArray.length - 1].endP, [random_int(0, width), random_int(0, height)], [random_int(0, width), random_int(0, height)], 0);
    bz.draw();
    bzArray.push(bz);
}

function del_point() {
    if (bzArray.length == 1) {
        alert("无法继续删除");
        return;
    }
    let bz = bzArray.pop();
    let pointList = document.getElementById("pointList");
    pointList.removeChild(bz.controlD);
    pointList.removeChild(bz.endD);
    ctx.clearRect(0, 0, width, height);
    bzArray.forEach(element => {
        element.draw();
    });
}

function ball_move(i = 0) {
    if (i >= bzArray.length || !allTime) {
        ballCtx.clearRect(0, 0, width, height);
        return;
    }
    let { startP, controlP, endP } = bzArray[i];
    let singleTime = allTime / bzArray.length;
    let tval = 1 / (60 * singleTime);
    let t = 0; //计算位置的参数
    let move = setInterval(draw_ball, 16);
    function draw_ball() {
        if (t < 1) {
            //通过二次贝塞尔曲线公式计算坐标
            ballCtx.clearRect(0, 0, width, height);
            ballx = Math.pow(1 - t, 2) * startP[0] + 2 * t * (1 - t) * controlP[0] + Math.pow(t, 2) * endP[0];
            bally = Math.pow(1 - t, 2) * startP[1] + 2 * t * (1 - t) * controlP[1] + Math.pow(t, 2) * endP[1];
            ballCtx.beginPath();
            ballCtx.arc(ballx, bally, 20, 0, pi * 2);
            ballCtx.fill();
            t += tval;
        } else {
            clearInterval(move);
            ball_move(i + 1);
        }
    }
}

function setTime() {
    allTime = parseFloat(event.target.value);
}

function drawbg() {
    //绘制背景格子
    bgCtx.beginPath();
    for (let i = 1; i <= width / 16; i++) {
        bgCtx.moveTo(i * 16, 0);
        bgCtx.lineTo(i * 16, height);
    }
    for (let i = 1; i <= height / 16; i++) {
        bgCtx.moveTo(0, i * 16);
        bgCtx.lineTo(width, i * 16);
    }
    bgCtx.strokeStyle = "rgba(230,230,230,0.5)";
    bgCtx.lineWidth = 1;
    bgCtx.stroke();
    bgCtx.closePath();

    //绘制中心横竖线
    bgCtx.beginPath();
    bgCtx.moveTo(width / 2, 0);
    bgCtx.lineTo(width / 2, height);
    bgCtx.moveTo(0, height / 2);
    bgCtx.lineTo(width, height / 2);
    bgCtx.strokeStyle = "rgba(200,0,0,0.5)";
    bgCtx.lineWidth = 1;
    bgCtx.stroke();
    bgCtx.closePath();
}

init();
