BEGIN{
  sum = 0;
  medie = 0;
  linii = 0;
}

NR % 2 == 0 {
  for(i = 1;i <= NF;++i) {
    sum += $i;
  }
}

NR % 2 == 1 {
  for(i = 1;i <= NF;i++) {
    medie += $i;
  }
  linii++;
}

END{
  print "Suma: " sum
  print "Media: " medie/linii
}
