function out = doi_ai(N)
  count = 0;
  for i = 1:N
    x = rand();
    y = rand();
    if pdist([x y;0.5 0.5]) <= 0.5  # distanta de la punct la centru este mai mica sau egala decat raza lui (0.5)
      count = count + 1;
      plot(x, y, 'dr');
    else
      plot(x, y, '*b');
    endif
  endfor
  out = count / N;
end
