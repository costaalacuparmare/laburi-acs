function L = cholesky(A)
  [n n] = size(A);
  L = zeros(n, 1);
  for i = 1:n
    for j = 1:i-1
      aux = 0;
      for k = 1:j-1
        aux = aux + L(i, k) * L(j, k);
      endfor
      L(i, j) = (A(i, j) - aux) / L(j, j);
    endfor
    aux = 0;
    for k = 1:i-1
      aux = aux + L(i,k) * L(i,k);
    endfor
    L(i, i) = sqrt(A(i, i) - aux);
  endfor
endfunction
