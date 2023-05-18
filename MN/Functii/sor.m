function [x, iter] = sor(A, b, omega, x0, max_iter, tolerance)
    n = size(A, 1);
    x = x0;
    iter = 0;
    residual = tolerance + 1;

    while residual > tolerance && iter < max_iter
        x_prev = x;
        for i = 1:n
            sum1 = A(i, 1:i-1) * x(1:i-1);
            sum2 = A(i, i+1:n) * x_prev(i+1:n);
            x(i) = (1 - omega) * x_prev(i) + (omega / A(i, i)) * (b(i) - sum1 - sum2);
        endfor
        residual = norm(A * x - b);
        iter = iter + 1;
    endwhile
endfunction
