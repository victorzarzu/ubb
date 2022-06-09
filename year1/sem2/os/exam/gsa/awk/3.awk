NF % 2 == 0 {
  print $1 + $NF;
}

NF % 2 == 1 {
  suma += $int(NF / 2 + 1);
  linii++;
}

END{
  print "Medie: " suma/linii
}
