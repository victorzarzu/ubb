N = 5000;
urna = 'rrrrraaagg'
PA = 0; PAB = 0;

for i = 1:N
  extragere = randsample(urna, 3);
  if any(extragere == 'r') && all(extragere == 'r')
    PAB++;
  endif
end

disp(PAB / N);
