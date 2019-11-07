// zad 1

window.onload = main;

var x = 50;
var y = 50;
var arc = 0;
var vw;
var vh;
var ctx;
var rysuj = true;

function main(arg = null){

  var c = document.getElementById("myCanvas");
  vw = c.width/100;
  vh = c.height/100;

  ctx = c.getContext("2d");
  ctx.moveTo(x*vw, y*vh);
  switch (arg) {
    case "lizak":
      lizak();
    break;
    case "gwiazda":
      gwiazda();
    break;
    case "sudoku":
      sudoku();
    break;
    case "losuj":
      losowa_figura();
    break;
    default:
    break;
  }
}

function straznikGranic(x1, y1){

  if (x1 > 100*vw)
    x1 = 100*vh;
  else if (x1 < 0)
    x1 = 0;

  if (y1 > 100*vh)
    y1 = 100*vh;
  else if (y1 < 0)
    y1 = 0;

  return [x1, y1];
}

function naprzod(d)
{
  //ctx.beginPath();
  let x1 = x*vw + d*Math.sin((arc/180) * Math.PI)*vw;
  let y1 = (100 - y)*vh - d*Math.cos((arc/180) * Math.PI)*vh;
  [x1, y1] = straznikGranic(x1, y1);

  if (rysuj){
    ctx.lineTo(x1, y1);
    ctx.stroke();
  }
  else
    ctx.moveTo(x1, y1);

  x = x1/vw;
  y = 100 - y1/vh;

  document.getElementById("pozycja_x").innerHTML = 'x: <b>'+x+'%</b>';
  document.getElementById("pozycja_y").innerHTML = 'y: <b>'+y+'%</b>';

}

function ustaw_rysuj(flag)
{
  rysuj = flag;
}

function ustaw_kolor(kolor)
{
  ctx.strokeStyle = kolor;
}

function ustaw_grubosc(grubosc)
{
  ctx.lineWidth = grubosc;
}

function wyczysc()
{
  ctx.clearRect(0, 0, 100*vw, 100*vh);
  x = 50;
  y = 50;
  ctx.moveTo(x, y);
}

function lewo(t_arc)
{
  arc = (arc - t_arc) % 360;
  document.getElementById("pozycja_arc").innerHTML = 'kąt: <b>'+arc+'</b>';
}

function prawo(t_arc)
{
  arc = (arc + t_arc) % 360;
  document.getElementById("pozycja_arc").innerHTML = 'kąt: <b>'+arc+'</b>';
}

function powtorz(ile_razy, komendy)
{
  for (i=0; i<ile_razy; i++)
    for (j=0; j<komendy.length; j++){
      let command = komendy[j].split("(");
      let arg = command[1].split(")")[0];
      command = command[0];
      switch (command) {
        case "naprzod":
            naprzod(arg);
        break;
        case "lewo":
            lewo(arg);
        break;
        case "prawo":
            prawo(arg);
        break;
      }
  }
  ctx.stroke();
}
