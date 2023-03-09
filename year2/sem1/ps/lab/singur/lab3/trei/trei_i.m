N = 1000;

zaruri = randi(6, 4, N);
sumeP = sum(zaruri); #sum(vector, dim) - implicit dim = 1 (coloane) => dim = 2 (linii)
histogram = hist(sumeP, 4:24);

[4:24; histogram]'
