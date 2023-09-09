function [x, y] = adams_bashforth(f, x0, y0, h, N)
    x = zeros(1, N+1);
    y = zeros(1, N+1);
    
    x(1) = x0;
    y(1) = y0;
    
    for i = 1:3
        k1 = f(x(i), y(i));
        k2 = f(x(i) + h/2, y(i) + h/2 * k1);
        k3 = f(x(i) + h, y(i) - h*k1 + 2*h*k2);
        
        x(i+1) = x(i) + h;
        y(i+1) = y(i) + h/12 * (23*k1 - 16*k2 + 5*k3);
    end
    
    for i = 4:N
        x(i+1) = x(i) + h;
        y(i+1) = y(i) + h/12 * (23*f(x(i), y(i)) - 16*f(x(i-1), y(i-1)) + 5*f(x(i-2), y(i-2)));
    end
end

