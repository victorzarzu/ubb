function out = doi_c(N, R)
  count = 0;
  for index = 1:N
    obtuz = 0;
    x = rand;
    y = rand;
    O1 = [0.5 0];
    O2 = [0 0.5];
    O3 = [0.5 1];
    O4 = [1 0.5];
    if pdist([x y;O1]) < 0.5
      obtuz = obtuz + 1;
    endif
    if pdist([x y;O2]) < 0.5
      obtuz = obtuz + 1;
    endif
    if pdist([x y;O3]) < 0.5
      obtuz = obtuz + 1;
    endif
    if pdist([x y;O4]) < 0.5
      obtuz = obtuz + 1;
    endif
    if obtuz == 2
      count = count + 1;
      plot(x, y, 'dr');
    else
      plot(x, y, '*b');
    endif
  endfor

  out = count / N;
end

# A(xa, ya), B(xb, yb)
# pdist([xa, ya; xb yb])
