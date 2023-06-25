function P = neville(x, y, xi)
    n = length(x);
    P = zeros(n, n);

    for i = 1:n
        P(i, 1) = y(i);
    end

    for j = 2:n
        for i = 1:n-j+1
            P(i, j) = ((xi - x(i+j-1)) * P(i, j-1) + (x(i) - xi) * P(i+1, j-1)) / (x(i) - x(i+j-1));
        end
    end

    P0n = P(1, n);
end
