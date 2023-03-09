m = 1000;
p = 0.5;
k = 10; #numar par de pasi => apar doar pozitii pare la final si la fel si la impar
availablePos = -k:k;

posEnd = [];
for i=1:m
  posEnd = [posEnd, doi_a(p, k)(end)]; #ultima pozitie din rezultat
endfor

h = hist(posEnd, availablePos);
bar(availablePos, h, 'hist');

maxFrq = max(h);
maxPos = availablePos(h == maxFrq); # maxPos = find(h == maxFrq) - k - 1
