function derivative = numerical_derivative(f, x0, h)
    % Aproximarea derivatei folosind formula de derivare numerică
    derivative = (f(x0 + h) - f(x0 - h)) / (2 * h);
end
