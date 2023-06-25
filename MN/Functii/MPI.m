function [eigenvalue, eigenvector] = MPI(A, y, mu, max_iterations, tolerance)
    k = 0;
    lambda = 0;
    while k < max_iterations
        z = (A - mu * eye(size(A))) \ y;
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

