function integral = numerical_integration(f, a, b, N)
    % Metoda aproximativă de integrare
    x = linspace(a, b, N+1);
    f_vals = f(x);
    integral = sum(f_vals) * (b - a) / N;
end
