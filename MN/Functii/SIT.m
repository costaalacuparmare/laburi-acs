function X = SIT (L, b)
  [n m] = size(L);
  X = zeros(m, 1);
  for i = 1:n
    aux = 0;
    for j = 1:i-1
      aux = aux + L(i, j) * X(j);
    endfor
    X(i) = (b(i) - aux) / L(i, i);
  endfor
endfunction
