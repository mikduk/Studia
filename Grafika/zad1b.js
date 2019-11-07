function polecenie_wykonac()
{
  let command = document.getElementById("polecenie").value;
  let history = document.getElementById("historia").value;
  let arg = null;

  if (command == "wyczysc()")
    wyczysc();
  else if (command.includes("lewo(") || command.includes("prawo(")
        || command.includes("naprzod(") || command.includes("powtorz")
        || command.includes("kolor(") || command.includes("grubosc")){
    if (!command.includes("powtorz")){
      command = command.split("(");
      arg = command[1].split(")")[0];
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
        case "kolor":
            ustaw_kolor(arg);
        break;
        case "grubosc":
            ustaw_grubosc(arg);
        break;
      }
    }
    else{
      let ile = null;
      command = command.split("[");
      arg = command[1].split("]");
      arg = arg[0].split(", ");
      command = command[0].split(" ");
      ile = command[1];
      command = command[0];

      if (command == "powtorz")
        powtorz(ile, arg);

    }
  }
  else{
    if (history)
      document.getElementById("historia").innerHTML = history + '<br>Niepoprawna komenda';
    else
      document.getElementById("historia").innerHTML = '<br>Niepoprawna komenda';
  }
}
