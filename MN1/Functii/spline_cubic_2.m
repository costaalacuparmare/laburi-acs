function [a, b, c, d] = spline_cubic_2(x, f, f_prime)
    n = length(x) - 1;  % Numărul de intervale

    % Inițializare coeficienți
    a = f;
    d = zeros(1, n);
    b = zeros(1, n);
    c = zeros(1, n);

    h = diff(x);  % Lungimea fiecărui interval

    % Calculul coeficienților
    for i = 1:n
        d(i) = (c(i+1) - c(i)) / (3 * h(i));
        b(i) = (a(i+1) - a(i)) / h(i) - (h(i) * (2 * c(i) + c(i+1))) / 3;
    end

end
