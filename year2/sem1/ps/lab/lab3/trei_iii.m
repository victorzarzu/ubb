for i1 = 1:6
  for i2 = 1:6
    for i3 = 1:6
      for i4 = 1:6
        st = [st i1+i2+i3+i4]
      endfor
    endfor
  endfor

clf;
grid on;
hold on;

N = 1000;
sumeP = st;
fa = hist(sumeP, 4:24);

xticks(4:24); xlim([3 25]);
yticks(0:0.01:0.14); ylim([0 0.14]);
bar(4:24, fa / N, 'FaceColor', 'b');
legend('sume');
set(findobj('type','patch'),'facealpha', 0.7); # identifica barele si le da o capacitate mai mica

sume_pos = 4:24;
fm = max(fa);
mostFrequentSum = sume_pos(fa == fm) # vector_indici(conditie) sau find(conditie)
