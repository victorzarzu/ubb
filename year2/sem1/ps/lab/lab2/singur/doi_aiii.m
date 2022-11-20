# Se poate folosi si teorema lui Pitagora
# daca a^2 + b^2 < c^2 => triunghi obtuzunghic, unde c este cea mai lunga latura
# daca a^2 + b^2 > c^2 => triunghi ascutitunghic, unde c este cea mai lunga latura

function out = doi_aiii(N)
  count = 0;
  for i = 1:N
    x = rand();
    y = rand();
    obtuz = 0;
    if pdist([x, y;0, 0])^2 + pdist([x, y;0, 1])^2 < 1 # daca triunghiul format cu latura stanga este obtuzunghic
      obtuz = obtuz + 1;
    endif
    if pdist([x, y;0, 1])^2 + pdist([x, y;1, 1])^2 < 1 # daca triunghiul format cu latura de sus este obtuzunghic
      obtuz = obtuz + 1;
    endif
    if pdist([x, y;1, 1])^2 + pdist([x, y;1, 0])^2 < 1 # daca triunghiul format cu latura dreapta este obtuzunghic
      obtuz = obtuz + 1;
    endif
    if pdist([x, y;0, 0])^2 + pdist([x, y;1, 0])^2 < 1 # daca triunghiul format cu latura de jos este obtuzunghic
      obtuz = obtuz + 1;
    endif
    if obtuz == 2
      plot(x, y, 'dr');
      count = count + 1;
    else
      plot(x, y, '*b');
    endif
  endfor
  out = count / N;
end

#{
function out = doi_aiii(N)
  count = 0;
  for i = 1:N
    x = rand();
    y = rand();
    obtuz = 0;
    if pdist([x, y;0.5, 0]) <= 0.5 # daca este in cercul de jos cu un semicerc in patrat atunci exista un triunghi obtuz
      obtuz = obtuz + 1;
    endif
    if pdist([x, y;0, 0.5]) <= 0.5 # daca este in cercul din stanga cu un semicerc in patrat atunci exista un triunghi obtuz
      obtuz = obtuz + 1;
    endif
    if pdist([x, y;0.5, 1]) <= 0.5 # daca este in cercul de sus cu un semicerc in patrat atunci exista un triunghi obtuz
      obtuz = obtuz + 1;
    endif
    if pdist([x, y;1, 0.5]) <= 0.5 # daca este in cercul din dreapta cu un semicerc in patrat atunci exista un triunghi obtuz
      obtuz = obtuz + 1;
    endif
    if obtuz == 2
      plot(x, y, 'dr');
      count = count + 1;
    else
      plot(x, y, '*b');
    endif
  endfor
  out = count / N;
end
#}
