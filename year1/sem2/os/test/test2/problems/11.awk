BEGIN{
  sum = 0;
}

{
  sum += $2
} 

END{
  print sum / NR;
}
