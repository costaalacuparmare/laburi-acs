function [Error] = linear_regression_cost_function(Theta, Y, FeatureMatrix)
  % Theta -> the vector of weights
  % Y -> the vector with all actual values
  % FeatureMatrix -> the matrix with all training examples

  % Error -> the error of the regularized cost function

  % TODO: linear_regression_cost_function implementation
  [m n] = size(FeatureMatrix);
  h = zeros(m, 1);
  for i = 1:m
    for j = 1:n
      % getting Theta from j + 1 to ignore Theta0
      h(i, 1) += Theta(j + 1, 1) * FeatureMatrix(i, j);
    endfor
  endfor
  sum = 0;
  for i = 1:m
    sum += (h(i, 1) - Y(i, 1)) * (h(i,1) - Y(i, 1));
  endfor
  Error = sum / (2 * m);
endfunction
