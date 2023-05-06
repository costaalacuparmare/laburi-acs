function [path] = heuristic_greedy (start_position, probabilities, Adj)
	% start_position -> the starting point in the labyrinth
	% probabilities -> vector of associated probabilities: including WIN and LOSE
	% Adj -> adjacency matrix

	% path -> the states chosen by the algorithm

  % TODO: heuristic_greedy implementation
  n = size(Adj, 1);
  path = [start_position];
  visited = zeros(n, 1);
  visited(start_position) = 1;
  while (!isempty(path))
    if (path(end) == n - 1)
      return;
    endif
    unvisited = [];
    for i = 1:n-1
      if (Adj(path(end), i) && !visited(i))
        unvisited = [unvisited i];
      endif
    endfor
    if (isempty(unvisited))
      path(end) = [];
    else
      [!, i] = max(probabilities(unvisited));
      neigh = unvisited(i);
      visited(neigh) = 1;
      path = [path, neigh];
    endif
  endwhile
  path = path';
endfunction
