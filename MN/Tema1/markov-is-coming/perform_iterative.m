function [x, err, steps] = perform_iterative (G, c, x0, tol, max_steps)
	% G -> iteration matrix
	% c -> iteration vector
	% x0 -> initial solution
	% tol -> accepted tolerance (norm of the difference between two solutions)
	% max_steps -> the maximum number of iterations

	% x -> final solution
	% err -> last calculated difference (as an euclidean norm)
	% steps -> actual number of steps performed

   % TODO: perform_iterative implementation
   x = x0;
   err = Inf;
   steps = 0;
   while (err > tol && steps < max_steps)
     new_x = G*x + c;
     err = norm(new_x - x);
     x = new_x;
     steps++;
   endwhile
endfunction
