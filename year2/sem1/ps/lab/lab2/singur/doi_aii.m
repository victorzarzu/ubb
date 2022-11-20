function out = doi_aii(N)
  count = 0;
  for i = 1:N
    x = rand();
    y = rand();
    distCentru = pdist([x, y;0.5, 0.5]);
    # daca distanta de la centru la punct este mai mica sau egala cu minimul dintre distantele pana la centru
    if distCentru < min([pdist([x, y;0, 0]), pdist([x, y;1, 0]), pdist([x y;0, 1]), pdist([x y;1, 1])])
      count = count + 1;
      plot(x, y, 'dr');
    else
      plot(x, y, '*b');
    endif
  endfor
  out = count / N;
end
