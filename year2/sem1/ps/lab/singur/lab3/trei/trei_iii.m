clf;
hold on;
grid on;

s = [];
for i1 = 1:6
  for i2 = 1:6
    for i3 = 1:6
      for i4 = 1:6
        s = [s i1+i2+i3+i4];
      endfor
    endfor
  endfor
endfor

histogram_teo = hist(s, 4:24);
[4:24; histogram]';

sume_pos = 4:24;
maxim = max(histogram_teo);
sume_pos(histogram_teo == maxim)

N = 1000;
zaruri = randi(6, 4, N);
sume = sum(zaruri);
histogram_rel = hist(sume, 4:24);

xticks(4:24); xlim([3 25]);
yticks(0:0.01:0.14); ylim([0 0.14])
bar(4:24, histogram_rel / N, 'FaceColor', 'b');
bar(4:24, histogram_teo / 6^4, 'FaceColor', 'y');
legend('probabilitati relative', 'probabilitati teoretice');
set(findobj('type', 'patch'), 'facealpha', 0.7);
