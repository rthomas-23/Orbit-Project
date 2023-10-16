%{
% x^3 = 11 TEST
f(x) = x^3 - 11;
syms x
func = symfun(x^3-11,x);
tol = 0.001;
x0 = 2;

sol = NRSolver(func, x, tol, x0);
disp(sol)
%}

% now trying for true anomaly at perigee
% Set variables
e = 0.4;
dt = 100;
a = 1.2793e4;
x0 = 457564;
tol = 0.0001;
mu = 398600;

%{
syms E real
func = symfun((E - (e*sin(E)) - dt*(mu/(a^3))^0.5), E);
sol = NRSolver(func, E, tol, x0);
disp(sol)
%}

syms x real
func = symfun(0.4876*cos(x) - 1.0262*sin(x) - 1.1364, x);
sol = NRSolver(func, x, tol, 0);
disp(sol)
