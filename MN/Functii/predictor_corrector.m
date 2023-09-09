function [x, y] = predictor_corrector(f, g, x0, y0, h, N)
    x = zeros(1, N+1);
    y = zeros(1, N+1);
    
    x(1) = x0;
    y(1) = y0;
    
    for i = 1:2
        x(i+1) = x(i) + h;
        y(i+1) = g(x(i), y(i), h);
    end
    
    for i = 2:N
        x(i+1) = x(i) + h;
        y(i+1) = g(x(i), y(i), h);
        y(i+1) = y(i) + h/2 * (f(x(i+1), y(i+1)) + f(x(i), y(i)));
    end
end
