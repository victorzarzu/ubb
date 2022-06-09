{
  for(i = 1;i <= NF;++i) {
    freq[$i]++;
  }
}

END{
  for(cuv in freq) {
    print cuv "->" freq[cuv];
  }
}
