BEGIN{
  suma = 0;
  nr = 0;
}

{
  sumaPare = 0;
  for(count = 1; count <= NF;++count)
    {
      sumaPare += $count; 
      if(sumaPare % 2)
        {
          suma += $count;
          nr++;
        }
    }
  if(NR % 2 == 0)
    print sumaPare;
}

END{
  print suma / nr;
}
