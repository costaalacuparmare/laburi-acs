function [X_train, y_train, X_test, y_test] = split_dataset(X, y, percent)
  % X -> the loaded dataset with all training examples
  % y -> the corresponding labels
  % percent -> fraction of training examples to be put in training dataset

  % X_[train|test] -> the datasets for training and test respectively
  % y_[train|test] -> the corresponding labels

  % Example: [X, y] has 1000 training examples with labels and percent = 0.85
  %           -> X_train will have 850 examples
  %           -> X_test will have the other 150 examples

  % TODO: split_dataset implementation
  id_rand = randperm(size(X, 1));
  X = X(id_rand, :);
  y = y(id_rand, :);
  id_split = round(size(X, 1) * percent);
  X_train = X(1:id_split, :);
  y_train = y(1:id_split, :);
  X_test = X(id_split+1:end, :);
  y_test = y(id_split+1:end, :);
endfunction
