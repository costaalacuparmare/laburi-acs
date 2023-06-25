function [Adj] = get_adjacency_matrix (Labyrinth)
	% Labyrinth -> the matrix of all encodings

  % Adj -> the adjacency matrix associated to the given labyrinth

  % TODO: get_adjacency_matrix implementation
  [n m] = size(Labyrinth);
  Adj = sparse(zeros(n*m + 2, n*m + 2));
  Adj(n*m + 1, n*m + 1) = 1;
  Adj(n*m + 2, n*m + 2) = 1;
  for i = 1:n
    for j = 1:m
      mask = 1;
      if (!bitand(mask, Labyrinth(i,j)))
        if (j == 1)
          Adj(m*(i - 1) + j, m*n + 2) = 1;
        else
          Adj(m*(i - 1) + j, m*(i - 1) + j - 1) = 1;
        endif
      endif
      mask = 2;
      if (!bitand(mask, Labyrinth(i,j)))
        if (j == m)
          Adj(m*(i - 1) + j, n*m + 2) = 1;
        else
          Adj(m*(i - 1) + j, m*(i - 1) + j + 1) = 1;
        endif
      endif
      mask = 4;
      if (!bitand(mask, Labyrinth(i,j)))
        if (i == n)
          Adj(m*(i - 1) + j, m*n + 1) = 1;
        else
          Adj(m*(i - 1) + j, m*i + j) = 1;
        endif
      endif
      mask = 8;
      if (!bitand(mask, Labyrinth(i,j)))
        if (i == 1)
          Adj(m*(i - 1) + j, m*n + 1) = 1;
        else
          Adj(m*(i - 1) + j, m*(i - 2) + j) = 1;
        endif
      endif
    endfor
  endfor
endfunction
