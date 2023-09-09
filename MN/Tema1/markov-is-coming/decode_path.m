function [decoded_path] = decode_path (path, lines, cols)
	% path -> vector containing the order of the states that arrived
	% 		 to a winning position
	% lines -> number of lines
	% cols -> number of columns

	% decoded_path -> vector of pairs (line_index, column_index)
	%                 corresponding to path states
	% hint: decoded_path does not contain indices for the WIN state
  n = length(path);
	decoded_path = zeros(n - 1, 2);
	for i = 1:n - 1
		decoded_path(i, :) = [floor((path(i) - 1) / cols) + 1, mod(path(i) - 1, cols) + 1];
	endfor
endfunction
