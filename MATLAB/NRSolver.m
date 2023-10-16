function sol = NRSolver(func, funcvar, tol, x0)
%format long
% Function that uses newton-rhapson method to solve for the root of a
% fucnction
%
% Inputs:
% func - symfun (symbolic function) defines the function to sovle for the root of
% funcvar - variable with respect for which to find roots
% tol - tolerance for iteration error
% x0 - initial guess
%
% Outputs:
% sol - solution to function
%

% Find derivative of function
%fprime = matlabFunction(diff(func, funcvar));
fprime = matlabFunction(diff(func)); % note: this only works for f(x) (does not work ofr multiple variables (x,y,z..)

% convert symbolic function to matlab function
f = matlabFunction(func);

% Set error
error = inf;

i = 0;
% iteratively solve for root of function
while abs(error) > tol
    %k9
    % fprintf("f(x0) = " + f(x0) + " fprime(x0) = " + fprime(x0))
    sol = x0 - f(x0) / fprime(x0); % compute next solution
    error = sol - x0; % compute error
    %fprintf(" x0 =" + x0 + " i = " + i+ " sol = " + sol + " error = " + error);
    x0 = sol; % set next guess
    i = i +1;
end % while error > tol
%fprintf("\n number of iterations: " + i + "\n")
end %
