function [root, iterations] = secant(f, x0, x1, tolerance, max_iterations)
    iterations = 0;
    fx0 = f(x0);
    fx1 = f(x1);
    
    while abs(fx1) > tolerance && iterations < max_iterations
        if fx0 == fx1
            error('The function has the same value at x0 and x1. Secant method cannot be applied.');
        endif
        
        x2 = x1 - (fx1 * (x1 - x0)) / (fx1 - fx0);
        fx2 = f(x2);
        
        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = fx2;
        
        iterations = iterations + 1;
    endwhile
    
    root = x1;
endfunction
