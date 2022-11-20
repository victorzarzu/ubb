function out = doi_a(N, R)
  inCerc = 0;
  for index = 1:N
    x = rand;
    y = rand;
    # if x ^ 2 + y ^ 2 <= R
    if pdist([x y; 0.5 0.5]) < 0.5
      inCerc = inCerc + 1;
      plot(x, y, 'dr');
    else
      plot(x, y, '*b');
    endif
  endfor

  out = inCerc / N;
end

# A(xa, ya), B(xb, yb)
# pdist([xa, ya; xb yb])
