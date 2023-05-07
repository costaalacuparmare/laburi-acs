# Numerical Methods - First Homework

### Constantinescu Vlad 314CB 

The archive contains the implementation of the three tasks required

## Task 1 - Markov is coming

- `parse_labyrinth` The function reads the labyrinth matrix using to loops and after
each read line makes sure to read separately the newline character


- `get_adjacency_matrix` The function decodes the given matrix that represents
where the walls are found in the labyrinth by checking bit by bit each wall. To get the elements
int the adjacency matrix, it uses general formulas for the rows and columns.


- `get_link_matrix` The function counts how many places in the labyrinth can move
from one to another and calculates the links by dividing the 1s in the matrix by
the number of connections


- `get_Jacobi_parameters` The function returns the G matrix and the c vector used for the
Jacobi method. The c vector is composed of all the probabilities from the link matrix contained
in the last two columns and rows, which are related to the WIN/LOSE cases. The G matrix is filled
by the rest of the link matrix, using loop functions, disregarding the last two rows and columns


- `perform_iterative` The function solves the system using the Jacobi method, which is implemented
as long as the error is bigger than the tolerance and the maximum number of steps has not been achieved


- `heuristic_greedy` The function, using the heuristic algorithm given, determines the quickest path
in the labyrinth to get out


- `decode_path` The function return the pairs of rows and columns that compose the quickest path, making
sure to not take into account the WIN state

  
## Task 2 - Linear Regression

- `parse_data_set_file` The function reads the matrix that must be transformed, as well
  as a vector with the actual values that must be reached by the regression, using a similar
  style of reading as the previous task, with two loops, but the matrix is initialized with the
  *cell* function, in order to keep the strings intact


- `prepare_for_regression` The function takes the values from the initial matrix and uses
  the *switch* function to populate the feature matrix with 0s and 1s respecting the indications
  given. It uses 2 loops and before reading every line from the initial matrix, a counter is
  initialized with 0 that verifies how many elements are already loaded in the feature matrix
  inside the switch so that, if none of the cells are string, the feature matrix can be loaded
  with 0s using the function *str2num*, jumping over already filled areas memorised by the furnish_check
  variable


- `linear_regression_cost_function` The function calculates the cost using the specified formula,
  implemented with the help of loops to calculate sums in order to simplify the code



- `parse_csv_file` The function uses the *textscan* function in order to get the cells from the csv file.
  Using the function's parameters, it skips the header and gets the format of the cells on each line. The
  first column is then attributed to the vector of the actual values and the auxiliary in which the data is
  read is transformed intro a matrix, using the *cell2mat* function. The initial matrix is then populated by the


- `gradient_descent` The function calculates the Theta vector using the formulas given, adding at the end
  a line in the vector at the beginning, representing the first Theta, Theta0, which is 0


- `normal_equation` The function uses the conjugated gradient algorithm to calculate the normal equation.
  The function's implementation required that the parameters of the function to be transformed in the data
  for the algorithm, thus having to verify if the data for the algorithm respect the conditions of the
  theoretical algorithm


- `lasso_regression_cost_function` The function is almost identical to the end to the *linear_regression_cost_function*
because of the formulas' similarity. At the end the 1st norm of the Theta vector, multiplied by lambda is added
to the error and the sum is divided by m, instead of 2 * m


- `ridge_regression_cost_function` The function is almost identical to the end to the *linear_regression_cost_function* 
because of the formulas' similarity. At the end the sum of the squared elements of the Theta vector, calculated with
the *sumsq* function, multiplied by lambda is added to the error.


## Task 3 - MNis 101

- `load_dataset` The function uses the *load* function to read the .mat file


- `split_dataset` The function gets a random index vector id_rand using the *randperm* function and splits the X matrix
and the y vector


- `initialize_weights` The function calculates the epsilon based on the L_prev and L_next values and the formula
given. Afterwards, the matrix is calculated by making a random matrix of L_next rows and L_prev + 1 lines and
multiplying it by 2 and epsilon and subtracting  an epsilon to get the random values in the -epsilon, epsilon range
