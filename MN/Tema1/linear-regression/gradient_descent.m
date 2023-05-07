function [Theta] = gradient_descent(FeatureMatrix, Y, n, m, alpha, iter)
  % FeatureMatrix -> the matrix with all training examples
  % Y -> the vector with all actual values
  % n -> the number of predictors
  % m -> the number of trainings
  % alpha -> the learning rate
  % iter -> the number of iterations

  % Theta -> the vector of weights

  % TODO: gradient_descent implementation
  Theta = zeros(n, 1);
  for i = 1:iter
    for j = 1:n
      gradient(j) = (FeatureMatrix * Theta - Y)' * FeatureMatrix(:, j)/m;
    endfor
    Theta = Theta - alpha * gradient';
  endfor
  % adds Theta0 to the vector
  Theta = [0; Theta];
endfunction
