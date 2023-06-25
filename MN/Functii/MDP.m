function [eigenvalue, eigenvector] = MPD(A, y, max_iterations, tolerance)
    k = 0;
    lambda = 0;
    while k < max_iterations
        z = A * y;
        y = z / norm(z);
        lambda_old = lambda;
        lambda = y' * A * y;
        if abs(lambda - lambda_old) < tolerance
            break;
        end
        k = k + 1;
    end
    eigenvalue = lambda;
    eigenvector = y;
end

