function out=aranjamente(n, k)
  out = [];
  comb = nchoosek([1:n], k);
  [size, ~] = size(comb);
  for index=1:size
    comb_ = comb(index, :);
    aranj = perms(comb_);
    out = [out;aranj];
  endfor
end
