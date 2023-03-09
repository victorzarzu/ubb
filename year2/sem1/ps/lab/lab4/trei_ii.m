m = 10000;
p = hygepdf(3:6, 49, 6, 6);
p = sum(p);
x = geornd(p, 1, m);

prob_estimata = mean(x >= 10)
teoretica = 1 - sum(geopdf(0:9, p)) # se neaga pentru ca poate sa joace la infinit P(!A) = 1 - P(A);
