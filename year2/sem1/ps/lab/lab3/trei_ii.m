clf;
grid on;
hold on;

N = 1000;
zaruri = randi(6, 4, N); # numar maxim, linii, coloane
sumeP = sum(zaruri); # sum face implicit suma pe coloane => pentru linii sum(zaruri, 2)
fa = hist(sumeP, 4:24);

xticks(4:24); xlim([3 25]);
yticks(0:0.01:0.14); ylim([0 0.14]);
bar(4:24, fa / N, 'FaceColor', 'b');
legend('sume');
set(findobj('type','patch'),'facealpha',0.7); # findobj(la ce obiecte schimbari, la ce proprietati, valoarea) - transparenta

sume_pos = 4:24;
fm = max(fa);
mostFrequentSum = sume_pos(fa == fm) # vector_indici(conditie) sau find(conditie)
