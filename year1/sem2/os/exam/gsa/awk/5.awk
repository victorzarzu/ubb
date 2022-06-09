NR == 1 {
  maxim = NF;
  minim = NF;
  pmaxim = 1;
  pminim = 1;
  medie = NF;
}

NR != 1 {
  if(NF > maxim) {
    pmaxim = NR;
    maxim = NF;
  }
  if(NF < minim) {
    pminim = NR;
    minim = NF;
  }
  medie += NF;
}

END{
  print "Medie: " medie / NR;
  print pminim
  print pmaxim
}
