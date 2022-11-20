# calculeaza P(B|A)

function out = unu_iv()
  N = 5000;
  urn = 'rrrrrggbbb';
  PA = 0; PAB = 0; Pcond = 0;

  for i = 1:N
    ext = randsample(urn, 3);
    if any(ext == 'r')
      PA = PA + 1;
      if all(ext == 'r') # toate elementele sunt egale cu 'r'
        PAB = PAB + 1;
      endif
    endif
  endfor
  out = PAB / PA; # sau PAB / N
end
