function [path] = heuristic_greedy (start_position, probabilities, Adj)
	% start_position -> the starting point in the labyrinth
	% probabilities -> vector of associated probabilities: including WIN and LOSE
	% Adj -> adjacency matrix

	% path -> the states chosen by the algorithm

  % TODO: heuristic_greedy implementation
  path = [start_position];
  visited = false(size(probabilities));
  visited(start_position) = true;
  while (!isempty(path))
    if (path(end) == size(probabilities, 1));
      return;
    endif
    unvisited_neigh = find(Adj(path(end),:) & !visited');
    if (isempty(unvisited_neigh))
      path(end) = [];
    else
      [!, i] = max(probabilities(unvisited_neigh));
      neigh = unvisited_neigh(i);
      visited(neigh) = true;
      path = [path, neigh];
    endif
  endwhile
  path = path(:);
endfunction
