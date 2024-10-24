function [x succes iter] = GaussSeidel(A, b, x0, tol, maxiter)
 [n n]=size(A);
 succes=0;
 iter=maxiter;
 x=zeros(n,1);

 while maxiter > 0
 maxiter--;

 for i=1:n
 suma=A(i,1:i-1)*x(1:i-1)+A(i,i+1:n)*x0(i+1:n);
 x(i)=(b(i)-suma)/A(i,i);
 endfor

 if norm(x-x0)<tol
 succes=1;
 break;
 endif
  x0=x;
  endwhile
  iter=iter-maxiter;
endfunction

