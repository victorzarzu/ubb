NR % 2 == 0 {
  pare += NF;
}

NR % 2 == 1{
  impare += NF;
  linii++;
}

END{
  print "Total: " pare;
  print "Mediu: " impare / linii;
}
