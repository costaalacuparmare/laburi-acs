function [x iter] = Jacobi(A, b, x0, tol, maxiter) 

  [n n]=size(A); 

  x=zeros(n,1); 

 

  for iter=1:maxiter 

    for i=1:n  

      x(i)=(b(i)-A(i, 1:i-1)*x0(1:i-1) - A(i, i+1:n)*x0(i+1:n))/A(i,i); 

    endfor   

     

    if norm(x-x0)<tol 

      return; 

    endif 

    x0=x; 

  endfor 

endfunction 

 
