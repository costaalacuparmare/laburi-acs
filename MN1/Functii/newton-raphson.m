function [root, iterations] = newton_raphson(f, df, x0, tolerance, max_iterations)
    iterations = 0;
    fx = f(x0);
    
    while abs(fx) > tolerance && iterations < max_iterations
        dfx = df(x0);
        
        if dfx == 0
            error('The derivative of the function is zero. Newton-Raphson method cannot be applied.');
        endif
        
        x1 = x0 - fx / dfx;
        fx = f(x1);
        
        x0 = x1;
        iterations = iterations + 1;
    endwhile
    
    root = x1;
endfunction
