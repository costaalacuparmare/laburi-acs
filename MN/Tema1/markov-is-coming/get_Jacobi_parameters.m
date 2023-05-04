function [G, c] = get_Jacobi_parameters (Link)
	% Link -> the link matrix (edge with probabilities matrix)

  % G -> iteration matrix
	% c -> iteration vector

  % TODO: get_Jacobi_parameters
  [n m] = size(Link);
  G = sparse(zeros(n-2, m-2));
  c = sparse(zeros(m-2, 1));
  for i = 1:n-2
    for j = 1:m
      if (Link(i, j) != 0)
        if (j == m-1)
          c(i) = Link(i, j);
        elseif (j == m)
          c(i) = 0;
        else
          G(i,j) = Link(i,j);
        endif
      endif
    endfor
  endfor
endfunction
