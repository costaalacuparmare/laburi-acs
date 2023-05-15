function [A, v] = GPP(A)
    n = size(A, 1);
    v = zeros(n, 1);
    
    for p = 1:n-1
        [~, ip] = max(abs(A(p:n, p)));  % Determină indicele ip pentru pivot
        ip = ip + p - 1;
        
        % Efectuează schimb de linii
        A([p, ip], :) = A([ip, p], :);
        v(p) = ip;
        
        for j = p:n
            A([p, ip], j) = A([ip, p], j);  % Schimbă elementele coloanelor
        end
        
        for i = p+1:n
            mu = A(i, p) / A(p, p);  % Calculează factorul de multiplicare
            
            A(i, p) = mu;  % Salvează factorul în matrice
            
            for j = p+1:n
                A(i, j) = A(i, j) - mu * A(p, j);  % Actualizează elementele
            end
        end
    end
    
endfunction
