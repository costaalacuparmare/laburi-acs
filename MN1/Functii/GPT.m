function [A, vst, vdr] = GPT(A)
    n = size(A, 1);
    vst = zeros(n-1, 1);
    vdr = zeros(n-1, 1);

    for p = 1:n-1
        max_val = 0;
        for ip = p:n
            for jp = p:n
                val = abs(A(ip:jp, ip:jp));
                max_val = max(max_val, val);
            endfor
        endfor
        [val, idx] = max(max_val);
        [ip, jp] = ind2sub(size(max_val), idx);
        ip = ip + p - 1;
        jp = jp + p - 1;

        % Swap rows p and ip
        A([p, ip], :) = A([ip, p], :);

        % Swap columns p and jp
        A(:, [p, jp]) = A(:, [jp, p]);

        vst(p) = ip;
        vdr(p) = jp;

        for i = 1:n
            % Swap elements aip and aijp
            temp = A(i, p);
            A(i, p) = A(i, jp);
            A(i, jp) = temp;
        endfor

        for i = p+1:n
            mip = A(i, p) / A(p, p);

            A(i, p) = 0;

            for j = p+1:n
                A(i, j) = A(i, j) - mip * A(p, j);
            endfor
        endfor
    endfor
endfunction

