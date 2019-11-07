function Hilbert()
{
  wyczysc();
  let stopien = document.getElementById("polecenie").value;
  krzywa_Hilberta(parseInt((stopien)));
}

function krzywa_Hilberta(stopien, lustrzane=false, d=100/Math.pow(2, stopien+1))
{
  let l = 1;
  let glowna = false;
  if (lustrzane) l = -1;
  else l = 1;
  if (stopien > 3) ustaw_grubosc(1);

  if (stopien < 1)
    return;
  else
  {
    if (d == 100/Math.pow(2, stopien+1)){
      ustaw_rysuj(false);
      prawo(180);
      naprzod(50 - d);
      prawo(180);
      prawo(90);
      naprzod(50 - d);
      lewo(90);
      ustaw_rysuj(true);
      glowna = true;
      console.info("Początek rysowania krzywej Hilberta");
    }

    lewo(90*l);
    krzywa_Hilberta(stopien - 1, !lustrzane, d); if (glowna) console.info("1/4");
    naprzod(2*d);
    prawo(90*l);
    krzywa_Hilberta(stopien - 1, lustrzane, d); if (glowna) console.info("2/4");
    naprzod(2*d);
    krzywa_Hilberta(stopien - 1, lustrzane, d); if (glowna) console.info("3/4");
    prawo(90*l);
    naprzod(2*d);
    krzywa_Hilberta(stopien - 1, !lustrzane, d); if (glowna) console.info("4/4");
    lewo(90*l);
  }

  if (glowna)
    console.info("Koniec rysowania krzywej Hilberta");

  return;
}
