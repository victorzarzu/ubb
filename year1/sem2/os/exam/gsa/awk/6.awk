NF > 2 {
   freq[NR] = 1;
}

NF % 2 == 1 {
  print $int(NF % 2 + 1);
}

END{
  ORS = " ";
  for(linie in freq) {
    print linie;
  }
}
