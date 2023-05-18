function [root, iterations] = bisection(f, a, b, tolerance, max_iterations)
    fa = f(a);
    fb = f(b);
    
    if fa * fb > 0
        error('The function has the same sign at both ends of the interval. Bisection method cannot be applied.');
    endif
    
    iterations = 0;
    
    while (b - a) / 2 > tolerance && iterations < max_iterations
        c = (a + b) / 2;
        fc = f(c);
        
        if abs(fc) < tolerance
            root = c;
            return;
        endif
        
        if fa * fc < 0
            b = c;
            fb = fc;
        else
            a = c;
            fa = fc;
        endif
        
        iterations = iterations + 1;
    endwhile
    
    root = (a + b) / 2;
endfunction
