N = 5000;
urna = 'rrrrraaagg';
PA = 0;

for i = 1:5000
  extragere = randsample(urna, 3);
  if any(extragere == 'r')
    PA++;
  endif
end

disp(PA / N)
