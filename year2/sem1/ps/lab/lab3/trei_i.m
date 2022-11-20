clf;
grid on;
hold on;

N = 1000;
zaruri = randi(6, 4, N); # numar maxim, linii, coloane
sumeP = sum(zaruri); # sum face implicit suma pe coloane => pentru linii sum(zaruri, 2)
fa = hist(sumeP, 4:24);
[4:24; fa]'
