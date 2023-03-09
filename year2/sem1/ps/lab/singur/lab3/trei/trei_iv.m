N = 1000;

zaruri = randi(6, 4, N);
sume_rel = sum(zaruri);

PB_rel = sum(sume_rel <= 20);
PAB_rel = sum(sume_rel >= 10 & sume_rel <= 20);
disp(PAB_rel / PB_rel)

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

PB_teo = sum(s <= 20);
PAB_teo = sum(s >= 10 & s <= 20);
disp(PAB_teo / PB_teo)
