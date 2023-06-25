function [Q, R] = QR(A)
    [m, n] = size(A);
    Q = eye(m);
    R = A;

    for k = 1:min(m-1, n)
        x = R(k:m, k);
        e = eye(length(x), 1);
        v = sign(x(1))*norm(x)*e + x;
        v = v / norm(v);

        R(k:m, k:n) = R(k:m, k:n) - 2*v*(v'*R(k:m, k:n));
        Q(:, k:m) = Q(:, k:m) - 2*(Q(:, k:m)*v)*v';
    end
end
