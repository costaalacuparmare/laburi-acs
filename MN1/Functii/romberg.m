function integral = romberg(f, a, b, epsilon, maxIterations)
    h = b - a;
    n = 1;
    I = zeros(maxIterations, maxIterations);
    I(1, 1) = (h / 2) * (f(a) + f(b));
    
    for j = 2:maxIterations
        h = h / 2;
        sum = 0;
        for i = 1:n
            x = a + (i - 0.5) * h;
            sum = sum + f(x);
        end
        
        I(j, 1) = (1/2) * I(j-1, 1) + h * sum;
        
        for k = 2:j
            I(j, k) = I(j, k-1) + (I(j, k-1) - I(j-1, k-1)) / ((4^(k-1)) - 1);
        end
        
        n = n * 2;
        
        if abs(I(j, j) - I(j-1, j-1)) < epsilon * abs(I(j, j))
            break;
        end
    end
    
    integral = I(j, j);
end
