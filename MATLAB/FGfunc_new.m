    function [rs,vs] = FGfunc_new(r0, v0, T, mu, ti)

%  inputs:
% - inital position and velocity
% - Total time for simulation to run (seconds)
% - gravitational constant for Earth
% - ti: time step between orbit calculations 
%
% outputs:
% - Position vector of orbit throughout entire simulation
% - Plots the orbit in 3D

% Initialise
%{
r0 = [-5.0168;
      2.8965;
      5.0357]*1e3;

v0 = [-4.2633;
      -7.3842;
      0];
%}

dt0 = 0;
dt = 0;
E0 = 0; % Starting at perigee

%T = 4*60*60;
%mu = 398600;
i = 1;

% Get INITIAL orbital elements
[a,e,I,RAAN,AOP,f0] = RV2OE(r0,v0,mu);
n = sqrt(mu/a^3); % Mean motion

rs = zeros(1+T/ti,3);
rs(1,:) = r0;
vs = zeros(1+T/ti,3);
vs(1,:) = r0;

while dt < T

% Get NEW dt
dt = dt0 + (i*ti); % increment by 10 seconds

% Get E (newton raphson)
x0 = pi; % guess for Newton Raphson method
tol = 0.0001; %tolerance for Newton Raphson method
syms E_var real
func = symfun((E_var - (e*sin(E_var)) - dt*n), E_var);
E = NRSolver(func, E_var, tol, x0); % Solution for E

% Change in E
dE = E - E0;

% Get r
r0_mag = norm(r0);
F = (1 - (a/r0_mag) * (1 - cos(dE)));
G = dt - (((a^3)/mu)^0.5) * (dE-sin(dE));
r = F*r0 + G*v0;

% Get v
r_mag = norm(r);
F_dot = - (((mu*a)^0.5)/ (r_mag*r0_mag))*sin(dE);
G_dot = 1 - (a/r_mag)*(1-cos(dE));
v = F_dot*r0 + G_dot*v0;

i = i + 1;
disp(dt)
rs(i,:) = r;
vs(i,:) = v;

end

Re = 6378;
[X,Y,Z] = sphere;

figure;
hold on; grid on; axis equal;
plot3(rs(:,1), rs(:,2), rs(:,3))
surf(Re*X,Re*Y,Re*Z);
title('One Orbit (ECI Frame (Analytical Using F&G Functions))');
xlabel('X (km)'); ylabel('Y (km)'); zlabel('Z (km)');


end
