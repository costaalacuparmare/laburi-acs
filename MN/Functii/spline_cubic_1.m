function [a, b, c, d] = spline_cubic_1(x, f, f_prime)
    n = length(x) - 1;  % Numărul de intervale

    % Inițializare coeficienți
    a = f;
    d = zeros(1, n);
    b = zeros(1, n);
    c = zeros(1, n);

    h = diff(x);  % Lungimea fiecărui interval

    % Calculul coeficienților
    for i = 1:n
        b(i) = f(i) + (h(i)^3 * f_prime(i)) / 3;
        c(i) = f(i+1) - (h(i)^3 * f_prime(i+1)) / 3;
        d(i) = f_prime(i);
    end

end
