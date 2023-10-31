fontSize = 16;
% Generate the sample data.
X=[5.47459,21.56079,47.34219,81.55464,122.83436,169.8972,221.62951,277.1123,335.60853,396.53567,459.43598,523.94976,589.79335,656.74184,724.61564,793.27029,862.58873,932.47532];
Y=[2.86
4.45
7.51
11.63
14.9
17.83 
20.51 
19.53 
19.31 
18.50 
16.63 
14.33 
11.78 
9.03 
7.96 
5.65 
4.78 
3.71 
];
% Find the coefficients.
coeffs = polyfit(X, Y, 7)
plot(X, Y, 'ro', 'MarkerSize', 10);
% Make a finer sampling so we can see what it
% does in between the training points.
interpolatedX = linspace(min(X), max(X), 50000);
interpolatedY = polyval(coeffs, interpolatedX);
% Plot the interpolated points.
hold on;
plot(interpolatedX, interpolatedY, 'b-', 'LineWidth', 3);
grid on;
title('Interpolating Polynomial', 'FontSize', fontSize);
xlabel('X', 'FontSize', fontSize);
ylabel('Y', 'FontSize', fontSize);
% Enlarge figure to full screen.
%set(gcf, 'units','normalized','outerposition',[0 0 1 1]);