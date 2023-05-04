function [Y, InitialMatrix] = parse_data_set_file(file_path)
  % Read the file contents
  file_contents = fileread(file_path);

  % Split the file contents into lines
  lines = strsplit(file_contents, "\n");

  % Get the number of rows and columns of the initial matrix
  [n, m] = sscanf(lines{1}, "%d %d");

  % Initialize the initial matrix with zeros
  InitialMatrix = zeros(n, m);

  % Parse the initial matrix values from the file
  for i = 1:n
    row_values = sscanf(lines{i+1}, "%f");
    InitialMatrix(i,:) = row_values';
  endfor

  % Parse the Y vector from the file
  Y = sscanf(lines{n+2}, "%f");

endfunction
