function [FeatureMatrix] = prepare_for_regression(InitialMatrix)
  % InitialMatrix -> the matrix that must be transformed

  % FeatureMatrix -> the matrix with all training examples

  % TODO: prepare_for_regression implementation
  [m n] = size(InitialMatrix);
  for i = 1:m
    furnish_check = 0 % counts if two elements are allocated
    for j = 1:n
        switch InitialMatrix{i, j}
          case "yes"
            FeatureMatrix(i, j) = 1;
          case "no"
            FeatureMatrix(i, j) = 0;
          case "semi-furnished"
            FeatureMatrix(i, j) = 1;
            FeatureMatrix(i, j + 1) = 0;
            furnish_check++;
          case "unfurnished"
            FeatureMatrix(i, j) = 0;
            FeatureMatrix(i, j + 1) = 1;
            furnish_check++;
          case "furnished"
            FeatureMatrix(i, j) = 0;
            FeatureMatrix(i, j + 1) = 0;
            furnish_check++;
          otherwise
            FeatureMatrix(i, j + furnish_check) = str2num(InitialMatrix{i, j});
        endswitch
    endfor
  endfor
endfunction
