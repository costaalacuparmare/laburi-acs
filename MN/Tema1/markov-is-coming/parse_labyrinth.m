function [Labyrinth] = parse_labyrinth(file_path)
	% file_path -> the relative path to a file that needs to
  %              be loaded_graphics_toolkits

  % Labyrinth -> the matrix of all encodings for the labyrinth's walls

  % TODO: parse_labyrinth implementation
    file = fopen(file_path, "r");
  n = fscanf(file, "%d", 1);
  m = fscanf(file, "%d", 1);
  Labyrinth = zeros(n,m);
  for i = 1:n
    for j = 1:m
      Labyrinth(i,j) = fscanf(file, "%d", 1);
    endfor
    fscanf(file, "\n");
  endfor
  fclose(file);
endfunction
