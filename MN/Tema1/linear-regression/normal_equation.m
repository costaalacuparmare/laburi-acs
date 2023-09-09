function [Theta] = normal_equation(FeatureMatrix, Y, tol, iter)
  % FeatureMatrix -> the matrix with all training examples
  % Y -> the vector with all actual values
  % tol -> the learning rate
  % iter -> the number of iterations
  % tol -> the tolerance level for convergence of the conjugate gradient method

  % Theta -> the vector of weights

  % TODO: normal_equation implementation

  % need to get the A and b from the pseudocode
  % in order to make the algorithm wok and
  % the A matrix must be positively defined
  A = FeatureMatrix' * FeatureMatrix;
  b = FeatureMatrix' * Y;
  [n n] = size(A);
  Theta = zeros(n, 1);

  % to verify A is positively defined
  % by seeing if the lambda values are positive
  if (!all(eig(A) >= 0))
    Theta = [0; Theta];
    return
  endif

  r = b - A * Theta;
  v = r;
  tol = tol^2;
  k = 1;
  while (k <= iter && r' * r > tol)
    t = (r' * r) / (v' * A * v);
    Theta = Theta + t * v;
    r_new = r - t * A * v;
    s = (r_new' * r_new) / (r' * r);
    v = r_new + s * v;
    r = r_new;
    k++;
  endwhile
  % adds Theta0 to the vector
  Theta = [0; Theta];
endfunction
