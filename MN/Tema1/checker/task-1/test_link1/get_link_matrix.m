function [Link] = get_link_matrix (Labyrinth)
	% Labyrinth -> the matrix of all encodings

  % Link -> the link matrix associated to the given labyrinth

  % TODO: get_link_matrix implementation
    Link = get_adjacency_matrix(Labyrinth);
  [n m] = size(Link);
  for i = 1:n
    k = 0;
    for j = 1:m
      if (Link(i, j) == 1)
        k++;
      endif
    endfor
    for j = 1:m
      Link(i, j) = Link(i, j) / k;
    endfor
  endfor
endfunction
