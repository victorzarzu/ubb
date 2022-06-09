{
  for(i = 1;i <= NF;++i) {
    freq[$i]++;
  }
  sum += NF;
}

END{
  medie = sum / NR;
  print "Medie: " medie;
  for(val in freq) {
    if(freq[val] < medie) {
      print val;
    }
  }
}
