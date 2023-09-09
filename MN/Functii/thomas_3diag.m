function x = Thomas_3diag(a, b, c, d) 

n = length(b); 

            x = zeros(n,1); 

   

          %transform a astfel incat sa aiba n elemente, cu primul element 0 

         a = [inf; a]; 

 

% Operatiile la limita; 

c(1) = c(1)/b(1);  

d(1) = d(1)/b(1);    

   

          % calculul coeficientilor pe caz general 

for i = 2 : n-1 

aux = b(i)-a(i)*c(i-1); 

c(i) = c(i)/aux; 

d(i) = (d(i)-a(i)*d(i-1))/aux; 

endfor 

d(n) = (d(n)-a(n)*d(n-1))/(b(n)-a(n)*c(n-1)); 

  

% Substitutia inapoi pentru rezolvarea sistemului de ecuatii 

x(n) = d(n); 

for i = n-1 : -1 : 1 

x(i) = d(i)-c(i)*x(i+1); 

endfor 

endfunction 
