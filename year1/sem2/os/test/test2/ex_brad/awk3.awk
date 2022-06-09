BEGIN{
  sumaImpar = 0;
  nrImpar = 0;
}

NF % 2 == 0{
  print int($1 + $NF);
}

NF % 2 == 1{
  sumaImpar += $(int(NF/2) + 1);
  nrImpar++;
}

END{
  print "Media numerelor cu un numar impar de numere " sumaImpar / nrImpar;
}
