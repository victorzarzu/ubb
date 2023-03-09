function pos = doi_a(p = 0.5, k = 10)
  pos = zeros(1, k + 1);
  for i=2:k+1
    pos(i) = pos(i - 1) + 2 * binornd(1, p) - 1;
  endfor
end

# miscari = 2 * binornd(1, p, 1, k) - 1;
# miscari = 2 * floor(rand(1, k) + 1) - 1;
