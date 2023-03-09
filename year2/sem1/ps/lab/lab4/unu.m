hamW = strsplit(fileread('keywords_ham.txt'), ' '); #strsplit(string, caracter de split)
hamUW = unique(hamW); #le si sorteaza => primul este spatiu
hamUW = hamUW(2:end);
hamL = length(hamW);
hamUL = length(hamUW);
hamFrq = [];

spamW = strsplit(fileread('keywords_spam.txt'), ' ');
spamUW = unique(spamW);
spamUW = spamUW(2:end);
spamL = length(spamW);
spamUL = length(spamUW);
spamFrq = [];

email1 = strsplit(fileread('email1.txt'), ' ');
email2 = strsplit(fileread('email2.txt'), ' ');

# nu merge hist pentru ca elementele nu sunt string, ci cell-uri

for i=1:hamUL
  counter = 0;
  for j=1:hamL
    counter += strcmp(hamUW(i), hamW(j)); #strcmp returneaza 1 daca string-urile sunt egale
  endfor
  hamFrq = [hamFrq, counter / hamL];
endfor


# hamFrq = {P(Wi = true | C = ham)} i = 1,14
# P(C = ham | E1) = (P(W1 = true | C = ham) * ... * (P(Wn = false | C = ham) * P(C = ham))) / P(E1);

for i=1:spamUL
  counter = 0;
  for j=1:spamL
    counter += strcmp(spamUW(i), spamW(j)); #strcmp returneaza 1 daca string-urile sunt egale
  endfor
  spamFrq = [spamFrq, counter / spamL];
endfor

# spamFrq = {P(Wi = true | C = spam)} i = 1,14

# email1

hamFrq1 = hamFrq;
hamFrq2 = hamFrq;
spamFrq1 = spamFrq;
spamFrq2 = spamFrq;

for i=1:hamUL
  counter = 0;
  for j=1:length(email1)
    counter += strcmp(hamUW(i), email1(j));
  endfor

  if(counter == 0)
    hamFrq1(i) = 1 - hamFrq(i);
  else
    hamFrq1(i) = hamFrq(i);
  endif
endfor

for i=1:spamUL
  counter = 0;
  for j=1:length(email1)
    counter += strcmp(spamUW(i), email1(j));
  endfor

  if(counter == 0)
    spamFrq1(i) = 1 - spamFrq(i);
  else
    spamFrq1(i) = spamFrq(i);
  endif
endfor

hamP1 = prod(hamFrq1) * hamL / (spamL + hamL);
spamP1 = prod(spamFrq1) * spamL / (spamL + hamL);

disp(hamP1);
disp(spamP1);

if spamP1 > hamP1
  disp('email1 este spam');
else
  disp('email1 este ham');
endif

# email2

for i=1:hamUL
  counter = 0;
  for j=1:length(email1)
    counter += strcmp(hamUW(i), email2(j));
  endfor

  if(counter == 0)
    hamFrq2(i) = 1 - hamFrq(i);
  else
    hamFrq2(i) = hamFrq(i);
  endif
endfor

for i=1:spamUL
  counter = 0;
  for j=1:length(email1)
    counter += strcmp(spamUW(i), email2(j));
  endfor

  if(counter == 0)
    spamFrq2(i) = 1 - spamFrq(i);
  else
    spamFrq2(i) = spamFrq(i);
  endif
endfor

hamP2 = prod(hamFrq2) * hamL / (spamL + hamL);
spamP2 = prod(spamFrq2) * spamL / (spamL + hamL);

disp(hamP2);
disp(spamP2);

if spamP2 > hamP2
  disp('email2 este spam');
else
  disp('email2 este ham');
endif
