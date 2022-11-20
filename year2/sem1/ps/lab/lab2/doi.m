clf; hold on; axis square
rectangle('Position', [0 0 1 1]);

nums = [500, 1000, 2000];
i = randi(3);
N = nums(i);

doi_b(N, 1)
