{
  medie = ($3 + $4 + $5) / 3;
  note[$1 " " $2] = medie
}

END{
  for(nota in note) {
    print nota " " note[nota];
  }
  for(nota in note) {
    if(note[nota] < 8) {
      print nota;
    }
  }
}
