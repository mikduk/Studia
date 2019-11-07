var width = 320, height = 320;

var minX = 0, maxX = 100, minY = 0, maxY = 100;
var x = maxX/2, y = maxY/2;


var radian = Math.PI/180;
var direction = 0;



function parseX(x){
    return x * width/(maxX - minX);
}

function parseY(y){
    return height - (y * height/(maxY - minY));
}


function forward(distance){
        x = x  + (distance * Math.cos(direction*radian));
        y = y + (distance * Math.sin(direction*radian));
        line = line + " " + parseX(x).toString() + "," + parseY(y).toString();
}

function left(arc){
    this.direction = (this.direction + arc)%360;
}

function right(arc){
    this.direction =(this.direction - arc)%360;
}
var line = "";

function drawHilbert(j,k,mirror)
{
    if (k == 0) return;
    let l = 1;
    if (mirror) l = -1;

    left(90*l);
    drawKoch(j, k-1, !mirror);
    forward(j);
    right(90*l);
    drawKoch(j, k-1, mirror);
    forward(j);
    drawKoch(j, k-1, mirror);
    right(90*l);
    forward(j);
    drawKoch(j, k-1, !mirror);
    left(90*l);

}

function prepareLine(){
    var k = document.getElementById("degree").value;
    var param = (1-Math.pow(2, -k-1));
    x = param*maxX;
    y = (1 - param)*maxY;
    left(90);
    line = parseX(x).toString() + "," + parseY(y).toString();
    drawHilbert(2*(1 - param)*maxX, k, false);
    //var l = line.toString();
    document.getElementById("line").setAttribute("points",line);
}

function makeHilbert(){
    prepareLine();
}
