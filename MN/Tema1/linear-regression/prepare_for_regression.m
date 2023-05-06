function [FeatureMatrix] = prepare_for_regression(InitialMatrix)
  % InitialMatrix -> the matrix that must be transformed

  % FeatureMatrix -> the matrix with all training examples

  % TODO: prepare_for_regression implementation
  [m n] = size(InitialMatrix);
  for i = 1:m
    for j = 1:n
      if (strcmp(InitialMatrix(i,j), "yes"))
        FeatureMatrix(i,j) = 1;
      endif
    endfor
  endfor
endfunction
