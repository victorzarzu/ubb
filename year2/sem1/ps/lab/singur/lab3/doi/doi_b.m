n = 5;
p = 1 / 3;
m = 5000;

x = binornd(n, p, 1, m);

estimata = sum(x == 2) / m
teoretica = binopdf(2, n, p)
