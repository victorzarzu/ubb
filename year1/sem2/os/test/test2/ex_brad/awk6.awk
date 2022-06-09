BEGIN{
  nrPutin = 0;
}

NF > 2{
  indexes[NR] = 1;
}

NF % 2 == 1{
  print $(int(NF / 2) + 1);
  $(NF + 1) = "dfas"
  print $0;
}

END{
  ORS = " ";
  for(ind in indexes)
    print ind;

  for(ind in indexes)
    delete indexes[ind];

  delete indexes;
}
