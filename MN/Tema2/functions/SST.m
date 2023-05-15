function X = SST (U, b)
  [n m] = size(U);
  X = zeros(n, 1);
  for i = n:-1:1
    aux = 0;
    for j = i+1:n
      aux = aux + U(i, j) * X(j);
    endfor
    X(i) = (b(i) - aux) / U(i, i);
  endfor
endfunction
