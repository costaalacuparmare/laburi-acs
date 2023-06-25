function [Y, InitialMatrix] = parse_csv_file(file_path)
  % path -> a relative path to the .csv file

  % Y -> the vector with all actual values
  % InitialMatrix -> the matrix that must be transformed

  % TODO: parse_csv_file implementation
  file = fopen(file_path, 'r');
  % using textscan to read csv, ignoring the header
  % and the delimiter ',', then moves in Y the price
  % and changes aux in mat using cell2mat
  aux = textscan(file, '%f%s%s%s%s%s%s%s%s%s%s%s%s', 'HeaderLines', 1, 'Delimiter', ',');
  Y = aux{1};
  aux(:, 1) = [];
  aux = cell2mat(aux);
  [m n] = size(aux);
  for i = 1:m
    for j = 1:n
      InitialMatrix(i, j) = aux(i, j);
    endfor
  endfor
  endfunction
