function point = de_casteljau(points, t)
    n = size(points, 1) - 1;  % Gradul curbei Bézier

    while n > 0
        for i = 1:n
            points(i, :) = (1 - t) * points(i, :) + t * points(i + 1, :);
        end
        n = n - 1;
    end

    point = points(1, :);  % Punctul de pe curba Bézier

end
