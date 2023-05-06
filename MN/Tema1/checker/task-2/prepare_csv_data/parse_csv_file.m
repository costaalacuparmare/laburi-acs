function [Y, InitialMatrix] = parse_csv_file(file_path)
  % path -> a relative path to the .csv file

  % Y -> the vector with all actual values
  % InitialMatrix -> the matrix that must be transformed

  % TODO: parse_csv_file implementation
  M = csvread(file_path, 1, 0); % skip header row
  Y = M(:, end);
  InitialMatrix = M(:, 1:end-1);
endfunction
