BEGIN{

}

{
  medie = ($3 + $4 + $5) / 3;
  print $1 " " $2 " " medie;

  if(medie > 8)
    persoane[$1 " " $2] = 1;
}

END{
  for(persoana in persoane)
    print persoana
  
  for(persoana in persoane)
    delete persoane[persoana]
}
