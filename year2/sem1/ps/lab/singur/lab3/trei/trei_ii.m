clf;
grid on;
hold on;

N = 1000;

zaruri = randi(6, 4, N);
sume = sum(zaruri);
histogram = hist(sume, 4:24);

xticks(4:24); xlim([3 25]);
yticks(0:0.01:0.14); ylim([0 0.14]);
bar(4:24, histogram / N, 'FaceColor', 'b');
legend('frecventa estimate sume');
set(findobj('type', 'patch'), 'facealpha', 0.7);

sume_pos = 4:24;
maxim = max(histogram);
sume_pos(histogram == maxim)
#find(histogram == maxim) + 3
