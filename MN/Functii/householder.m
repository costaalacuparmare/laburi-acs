function [Q R x]=householder(A, b)
  [m n]=size(A);
  Q=eye(m);
  
  for p=1:min(m-1,n)
    vp=zeros(m,1);
    sigma=norm(A(p:m,p));
    if A(p,p) < 0
      sigma=-sigma;
    endif
    vp(p)=A(p,p)+sigma;
    vp(p+1:m)=A(p+1:m,p);
    
    Hp=eye(m)-(2*vp*vp')/(vp'*vp);
    A=Hp*A;
    b=Hp*b;
    Q=Hp*Q;
    
  endfor

  Q=Q';
  R=A;
  x=SST(R,b);
endfunction
