function out = prob1(n)
  count = 0;
  for i = 1:n
    zile = randi(365, 1, 23);
    if length(unique(zile)) < length(zile)
      count = count + 1;
    endif
  endfor
  out = count / n;
end
