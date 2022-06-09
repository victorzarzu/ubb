{
  sum = $1 + $(NF - 1) + $NF;
  medie += $1;
  print sum;
}

END{
  print medie / NR;
}
