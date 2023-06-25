pkg load symbolic

function integral = gaussian_ quadrature(f, a, b, N)
    syms x;
    
    % Calculează polinoamele Legendre și nodurile
    P = sym(zeros(1, N+1));
    xi = sym(zeros(1, N+1));
    
    for i = 0:N
        P(i+1) = legendreP(i, x);
        xi(i+1) = double(vpasolve(P(i+1) == 0, x, [-1, 1]));
    end
    
    % Calculează coeficienții AiN
    AiN = sym(zeros(1, N+1));
    
    for i = 1:N+1
        w = int(P(i)^2, x, -1, 1);
        AiN(i) = 2 / ((1 - xi(i)^2) * subs(diff(P(i), x), x, xi(i))^2);
    end
    
    % Calculează aproximarea integralei
    integral = 0;
    
    for i = 1:N+1
        x_val = a + (b - a) * (xi(i) + 1) / 2;
        integral = integral + AiN(i) * double(subs(f, x, x_val));
    end
    
    integral = (b - a) / 2 * integral;
end

