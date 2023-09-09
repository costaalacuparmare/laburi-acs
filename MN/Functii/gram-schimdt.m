function [Q, R] = GS(A)
  [m n]=size(A);
  Q=zeros(m,n);
  R=zeros(n,n);
  
  for j=1:n
    for k=1:j-1
        R(k,j)=Q(:,k)'*A(:,j);
    endfor
    aux=A(:,j)- Q(:,1:j-1)*R(1:j-1,j);
    R(j,j)=norm(aux);
    Q(:,j)=aux/R(j,j);
  endfor  
endfunction
