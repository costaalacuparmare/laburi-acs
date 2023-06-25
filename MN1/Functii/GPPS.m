function [A, v] = GPPS(A)
    n = size(A, 1);
    v = zeros(n, 1);

    for p = 1:n-1
        [val, ip] = max(abs(A(p:n, p)));
        ip = ip + p - 1;

        % Swap rows p and ip
        A([p, ip], :) = A([ip, p], :);

        v(p) = ip;

        for j = 1:n
            % Swap elements apj and aipj
            temp = A(p, j);
            A(p, j) = A(ip, j);
            A(ip, j) = temp;
        endfor

        for i = p+1:n
            mip = A(i, p) / A(p, p);

            A(i, p) = 0;

            for j = p+1:n
                A(i, j) = A(i, j) - mip * A(p, j);  % Update aij
            endfor
        endfor
    endfor
endfunction
