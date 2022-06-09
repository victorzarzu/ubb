BEGIN{
  cuvintePare = 0;
  cuvinteImpare = 0;
  nrImpare = 0;
}

NR % 2 == 0 {
  cuvintePare += NF;
}

NR % 2 == 1{
  cuvinteImpare += NF;
  nrImpare++;
}

END{
  print "Cuvinte de pe linii pare " cuvintePare;
  print "Numarul mediu de cuvinte de pe linii impare " int(cuvinteImpare / nrImpare);
}
