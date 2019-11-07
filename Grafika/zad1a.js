function lizak()
{

  for (i=0; i<7; i++){
    naprzod(5);
    lewo(45);
  }
  for (i=0; i<12; i++){
    naprzod(5);
    lewo(20);
  }
  prawo(15);
  naprzod(20);

  ctx.stroke();
}

function gwiazda()
{

  for (i=0; i<40; i++){
    naprzod(16);
    lewo(20);
    naprzod(16);
    prawo(90);
    naprzod(16);
    prawo(90);
    naprzod(16);
  }

  ctx.stroke();
}

function sudoku()
{
  for (i=0; i<1; i++){
    prawo(90);
    naprzod(5);
    lewo(90);
    naprzod(45);
    lewo(90);
    naprzod(50);
    lewo(90);
    naprzod(90);
    lewo(90);
    naprzod(90);
    lewo(90);
    naprzod(90);
  }
  for (i=0; i<5; i++){
    for (i=0; i<4; i++){
      lewo(90);
      naprzod(10);
      lewo(90);
      naprzod(90);
      lewo(-90);
      naprzod(10);
      lewo(-90);
      naprzod(90);
    }
      lewo(90);
      naprzod(10);
      lewo(90);
      naprzod(80);
      lewo(90);
      naprzod(90);

    for (i=0; i<4; i++){
      lewo(90);
      naprzod(10);
      lewo(90);
      naprzod(90);
      lewo(-90);
      naprzod(10);
      lewo(-90);
      naprzod(90);
    }
  }
}

function losowa_figura(){

    ustaw_grubosc(Math.random()*20);

    let kolor_par = [Math.random()*255, Math.random()*255, Math.random()*255, Math.random()];
    let kolor = 'rgba(' + kolor_par[0].toString() +',' + kolor_par[1].toString() + ',' + kolor_par[2].toString() + ',' + kolor_par[3].toString() + ')';
    ustaw_kolor(kolor);

    let figura  = Math.random()*3
    let komendy = [];

    if (figura <= 1)
    {
      komendy = ["naprzod(4)", "prawo(10)"]
      powtorz(36, komendy);
    }
    else if(figura <= 2)
    {
      komendy = ["naprzod(10)", "lewo(90)"];
      powtorz(4, komendy);
      prawo(90);
    }
    else if(figura <=3)
    {
      komendy = ["naprzod(20)", "lewo(120)"];
      powtorz(3, komendy);
      prawo(120);
    }
}
