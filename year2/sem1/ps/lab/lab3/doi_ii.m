N = 5000;
p = 1 / 3;
n = 5;
k = 2;

# h = hist() #hist() fara atribuire retureaza figura in sine
           #hist(vector, vector indici)
           #hist(binorand(), 0:5) - face suma pentru toate in functie de indici

v = binornd(n, p, 1, N);
fa = sum(v == 2);

[fa / N binopdf(k, n, p)]
