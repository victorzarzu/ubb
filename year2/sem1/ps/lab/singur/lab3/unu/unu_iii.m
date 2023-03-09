N = 5000;
urna = 'rrrrrbbbgg'
PA = 0; PAB = 0;

for i = 1:N
  extragere = randsample(urna, 3);
  if any(extragere == 'r')
    PA++;
  endif
  if all(extragere == 'r')
    PAB++;
  endif
end

disp(PAB / PA);
