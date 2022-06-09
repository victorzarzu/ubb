BEGIN{
  freq[1000];
  numberWords = 0;
}

{
  numberWords += NF;
  for(i = 1;i <= NF;++i)
    if($i in freq)
      freq[$i]++;
    else
      freq[$i] = 1;
}

END{
  medie = int(numberWords / NR);
  print "Medie " medie;

  print "Cuvinte cu frecventa sub medie ";
  for(word in freq)
    if(freq[word] < medie)
      print word;
  
  for(word in freq)
    delete freq[word];
  delete freq;
}
