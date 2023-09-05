function intergral = newton_cotes(f, a, b, N, type)
    switch type
        case 'trapezoidal_simple'
            h = b - a;
    	    integral = (f(a) + f(b)) * h / 2;
	case 'trapezoidal_composed'
	    h = (b - a) / N;
   	    integral = (f(a) + f(b)) / 2; 
    	    for i = 1:N-1
        	x = a + i*h;
        	integral = integral + f(x);
    	    end
    	    integral = h * integral;
	case 'simpsons_simple'
	    h = (b - a) / N;
    	    x = a:h:b;
            n = length(x);
    	    integral = f(a) + f(b);
    	    for i = 2:n-1
        	if mod(i, 2) == 0
            	    integral = integral + 4 * f(x(i));
        	else
                    integral = integral + 2 * f(x(i));
                end
            end
    	    integral = (h / 3) * integral;
	case 'simpsons_composed'
	   h = (b - a) / N;
    	   x = a + (h / 2) : h : b - (h / 2);
    	   integral = f(a) + f(b);
    	   for i = 1:N
         	integral = integral + 2 * f(x(i));
    	   end
    	   integral = (h / 3) * integral;
	 otherwise
            disp('No available type');
	end
end
