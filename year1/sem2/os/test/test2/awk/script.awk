#!/bin/awk -f

BEGIN{
  printf "Nume\t\t\tPrenume\t\tData nasterii\tTelefon\t\tSalariu\n";
  printf "----------------------------------------------------------------------------------\n";

  angajati = 0;
  #printf "%d\n", ARGC
  #for(i = 0;i < ARGC;++i)
  #{
    #printf "ARGV[%d] = %s\n", i, ARGV[i]
  #}
}

{
  printf "%s\t\t\t %s\t\t %s\t %s \t %s\n", $2, $1, $3, $4, $5
  angajati++;
}

END{
  printf "Numar angajati: %d\n", angajati
}
