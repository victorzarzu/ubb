# calculeaza P(B si A) / P(A)

N = 5000;
urn = 'rrrrrggbbb';
PA = 0; PAB = 0; Pcond = 0;
for i = 1:N
  ext = randsample(urn, 3);
  if all(ext == 'r') # toate elementele sunt egale cu 'r'
    PAB = PAB + 1;
  endif
  if any(ext == 'r')
    PA = PA + 1;
  endif
endfor

disp(PAB / PA);
