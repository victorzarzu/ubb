N = 5000;
urn = 'rrrrrggbbb';
PA = 0; PAB = 0; Pcond = 0;
for i = 1:N
  ext = randsample(urn, 3);
  if any(ext == 'r') # cel putin unul este egal cu 'r'
    PA = PA + 1;
  endif
endfor

disp(PA / N);
