BEGIN{
  maxLinii[100];
  indexMax = 0;
  max = 0;
  minimLinii[100];
  indexMin = 0;
  min = 100000;
  cuvinte = 0;
}

{
  if(NF > max)
  {
    indexMax = 1;
    maxLinii[0] = NR;
    max = NF;
  }
  else if(NF == max)
  {
    maxLinii[indexMax] = NR;
    indexMax++;
  }

  if(NF < min)
  {
    indexMin = 1;
    minLinii[0] = NR;
    min = NF;
  }
  else if(NF == min)
  {
    minLinii[indexMax] = NR;
    indexMin++;
  }

  cuvinte += NF;
}

END{
  print "Liniile cu numar maxim de cuvinte\n";
  for(i = 0;i < indexMax;++i)
    print maxLinii[i]; 
  print "Liniile cu numar minim de cuvinte\n";
  for(i = 0;i < indexMin;++i)
    print minLinii[i]; 
  print "Numar mediu " int(cuvinte / NR);
  
  #for(i = 0;i < indexMax;++i)
  #  delete maxLinii[i];
  #for(i = 0;i < indexMin;++i)
  #  delete minLinii[i]; 
  delete maxLinii;
  delete minLinii;
}

