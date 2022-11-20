function out = doi_b(N, R)
  inCerc = 0;
  for index = 1:N
    x = rand;
    y = rand;
    dist = pdist([x y; 0.5 0.5]);
    if dist < min([pdist([x y;0 0]), pdist([x y;0 1]), pdist([x y;1 0]), pdist([x y;1 1])])
      inCerc = inCerc + 1;
      plot(x, y, 'dr');
    else
      plot(x, y, '*b');
    endif
  endfor

  out = inCerc / N
end

# A(xa, ya), B(xb, yb)
# pdist([xa, ya; xb yb])
