function out = unu_func(N)
  count = 0;
  for i = 1:N
    zile = randi(365, 1, 23);
    if length(unique(zile)) != length(zile)
      count = count + 1;
    endif
  endfor
  out = count / N;
end
