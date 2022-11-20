N = 1000;
zaruri = randi(6, 4, N); # numar maxim, linii, coloane
sumeP = sum(zaruri); # sum face implicit suma pe coloane => pentru linii sum(zaruri, 2)

PA = sum(sumeP <= 20) / N;
PAB = sum(sumeP >= 10 & sumeP <= 20) / N; # cu unu trateaza element cu element in loc de lazy evaluation

disp(PAB / PA)
