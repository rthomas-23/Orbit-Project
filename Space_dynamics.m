%QUESTION 1

I = 0.715585;
RAAN = 0.9;
AOP = 1.5708;
f = 0;
e = 0.4; %eccentricity
a = 12792.865; %semi major axis (km)
Tp = 4*3600; %time persiod of chosen orbit (s)
mu = 398600; %gravitational constant
Re = 6378; %radius of Earth (km)
p = a*(1-e^2); %semi latus rectum
numOfOrbits = 1;

Tspan = 0:100:(Tp*numOfOrbits); %time we want to iterate over

%define the initial conditions of the state space matrix
%these are the positions and velocities at perigee (analytical part)
%{
[r,v]  = OE2RV(a,e,I,RAAN,AOP,f,mu);
x0 = zeros(6,1);
x0(1) = r(1);
x0(2) = r(2);
x0(3) = r(3);
x0(4) = v(1);
x0(5) = v(2);
x0(6) = v(3);
%}

x0 = [-5016.8 2896.5 5035.7 -4.263 -7.384 0];

%set up options paramater to set ode45 tolerance
options = odeset('RelTol',1e-7,'AbsTol',1e-7);

%propogate orbit over timespan of 1 orbit using ode45, initial conditions
[t, dx] = ode45(@(t,x) TwoBP(t,x,mu), Tspan, x0, options);

[X,Y,Z] = sphere;

figure;
hold on; grid on; axis equal;
plot3(dx(:,1), dx(:,2), dx(:,3));
surf(Re*X,Re*Y,Re*Z);
title('One Orbit (ECI Frame)');
xlabel('X (km)'); ylabel('Y (km)'); zlabel('Z (km)');


%QUESTION 2

GMST = deg2rad(-132); %GMST (rad)
w_earth = 2*pi/(24*3600); %rotational rate of Earth (rad/s)

r_eci = [dx(:,1) dx(:,2) dx(:,3)]';

v_eci = [dx(:,4) dx(:,5) dx(:,6)]';

[r_ecef, v_ecef] = ECI2ECEF(r_eci, v_eci, w_earth, Tspan, GMST);

%(1) 3D plot
figure;
hold on; grid on; axis equal;
plot3(r_ecef(:,1), r_ecef(:,2), r_ecef(:,3));
surf(Re*X,Re*Y,Re*Z);
title('3D Orbit (ECEF Frame)');
xlabel('X (km)'); ylabel('Y (km)'); zlabel('Z (km)');

%(2) X-Y plane view
figure;
grid on; hold on;
plot(r_ecef(:,1), r_ecef(:,2));
title('X-Y Plane View (One Orbit in ECEF Frame)');
xlabel('X (km)'); ylabel('Y (km)');
    
%(3) Y-Z plane view
figure;
grid on; hold on;
plot(r_ecef(:,2), r_ecef(:,3));
title('Y-Z Plane View (One Orbit in ECEF Frame)');
xlabel('Y (km)'); ylabel('Z (km)');

%(4) X-Z plane view
figure;
grid on; hold on;
plot(r_ecef(:,1), r_ecef(:,2));
title('X-Z Plane View (One Orbit in ECEF Frame)');
xlabel('X (km)'); ylabel('Z (km)');



%QUESTION 3
long = zeros(length(t));
lat = zeros(length(t));

for i = 1:length(r_ecef)
    long(i) = atan2d(r_ecef(i,2), r_ecef(i,1));
    lat(i) = atan2d(r_ecef(i,3), sqrt(r_ecef(i,1)^2+r_ecef(i,2)^2));

    if long(i) > 172
        long(i) = NaN;
        lat(i) = NaN;
    end
end

figure;
load('topo.mat','topo');
topoplot = [topo(:,181:360),topo(:,1:180)];
contour(-180:179,-90:89,topoplot,[0,0],'black','linewidth',1);
grid on
grid minor
axis equal
hold on


plot(long,lat,'m','LineWidth',2)
plot(-78, 41,'ro', 'LineWidth',2)

xlabel('Longitude [deg]')
ylabel('Latitude [deg]')
set(gca,'FontSize',18)



%QUESTION 4
format long

% General params
r0 = [-5.0168;
      2.8965;
      5.0357]*1e3; % ECI

v0 = [-4.2633;
      -7.3842;
      0];
mu = 398600;

% Iteration params
T = 4*60*60;
ti = 100;

[r_FG,v_FG] = FGfunc_new(r0, v0, T, mu, ti);


%QUESTION 5
r_eci = transpose(r_eci);
v_eci = transpose(v_eci);
disp(r_eci)
disp(r_FG)
disp(size(r_FG))
disp(size(r_eci))
err_r = zeros(145,2);
err_v = zeros(145,2);
dt_err = 0;
for i=1:145
    disp(r_eci(i,:))
    disp(r_FG(i,:))
    err_r(i,1) = 100 * abs(norm(r_eci(i,:))-norm(r_FG(i,:)))/norm(r_FG(i,:));
    err_r(i,2) = dt_err;
    err_v(i,1) = 100 * abs(norm(v_eci(i,:))-norm(v_FG(i,:)))/norm(v_FG(i,:));
    err_v(i,2) = dt_err;
    dt_err = dt_err + 100;
end
 
dts = linspace(0,4*60*60, 145);
mean(err_r(:,1))
mean(err_v(:,1))

%QUESTION 6
%after 0 seconds:
[a, e, I, RAAN, AOP, f] = RV2OE([r_eci(1,1); r_eci(2,1); r_eci(3,1);], [v_eci(1,1); v_eci(2,1); v_eci(3,1);], mu)
%after one orbit:
[a, e, I, RAAN, AOP, f] = RV2OE([r_eci(1,144); r_eci(2,144); r_eci(3,144);], [v_eci(1,144); v_eci(2,144); v_eci(3,144);], mu)
%after 1.5 orbits:
[a, e, I, RAAN, AOP, f] = RV2OE([r_eci(1,216); r_eci(2,216); r_eci(3,216);], [v_eci(1,216); v_eci(2,216); v_eci(3,216);], mu)
%after 4 orbits
[a, e, I, RAAN, AOP, f] = RV2OE([r_eci(1,576); r_eci(2,576); r_eci(3,576);], [v_eci(1,576); v_eci(2,576); v_eci(3,576);], mu)


function [r,v] = OE2RV(a,e,I,RAAN,AOP,f,mu)
%--- Enter code here ---
r_mag = a*(1-e^2)/(1+e*cos(f));
rpf = [r_mag*cos(f); r_mag*sin(f); 0];
vpf = [(-mu*sin(f))/(sqrt(mu*a*(1-e^2))); (mu*(e+cos(f)))/(sqrt(mu*a*(1-e^2))); 0];
R = [(cos(RAAN)*cos(AOP)-sin(RAAN)*sin(AOP)*cos(I)) (sin(RAAN)*cos(AOP)+cos(RAAN)*sin(AOP)*cos(I)) (sin(AOP)*sin(I)); (-cos(RAAN)*sin(AOP)-sin(RAAN)*cos(AOP)*cos(I)) (-sin(RAAN)*sin(AOP)+cos(RAAN)*cos(AOP)*cos(I)) (cos(AOP)*sin(I)); (sin(RAAN)*sin(I)) (cos(RAAN)*sin(I)) (cos(I))];
Rt = transpose(R);
r = Rt*rpf;
v = Rt*vpf;
end

function [a,e,I,RAAN,AOP,f] = RV2OE(r,v,mu)
    %--- Enter code here ---
    rmag = norm(r);
    vmag = norm(v);
    a = ((2/rmag)-(vmag^2/mu))^-1;
    h = cross(r,v);
    hmag = sqrt(sum(h.*h));
    e = sqrt(1-(hmag^2/(mu*a)));
    p = a*(1-e^2);
    if acos(((p/rmag)-1)/e) < 0.001
        f = 0;
    elseif dot(r,v) >= 0
        f = acos(((p/rmag)-1)/e);
    elseif dot(r,v) < 0
        f = 2*pi - acos(((p/rmag)-1)/e);
    end
    I = acos(h(3)/hmag);
    RAAN = asin(h(1)/(hmag*sin(I)));
    AOP = asin(r(3)/(rmag*sin(I)))-f;
    
    %{
    I = deg2rad(I);
    RAAN = deg2rad(RAAN);
    AOP = deg2rad(AOP);
    f = deg2rad(f);
    %}
    
end

function [r_ecef,v_ecef] = ECI2ECEF(r_eci, v_eci, omega, t, GMST)
    %r_eci, v_eci and t are passed into this function as matrices
    %therefore initialise r_ecef and v_ecef as matrices of the same size
    r_ecef = zeros(3, length(r_eci));
    v_ecef = zeros(3, length(v_eci));
    
    %length of t = length of r_eci and v_eci
    for i = 1:length(t)
    
    %angle by which to rotate about z-axis (rad)
    theta = GMST + omega*t(i);

    %define the directional cosine matrix for ECI to ECEF conversion
    DCM = [cos(theta) sin(theta) 0;
        -1*sin(theta) cos(theta) 0;
        0 0 1;];
    
    %use matrix multiplication to apply the DCM to the position
    %and velocity ECI vectors to find the ecef vectors
    r_ecef(:,i) = DCM * r_eci(:,i);
    v_ecef(:,i) = DCM * v_eci(:,i);
    end

    %finally transpose to ensure consistant formating of eci and ecef
    %matrices
    r_ecef = r_ecef';
    v_ecef = v_ecef';
end

function [dxdt] = TwoBP(t,x,mu)
    %x is our state space vector
    %initialise xdot (dxdt)
    dxdt = zeros(6,1);
    
    %define the first three components of the 6x1 dxdt vector
    dxdt(1) = x(4);
    dxdt(2) = x(5);
    dxdt(3) = x(6);
    
    %define the common denominator of the last three components
    rCubed = norm([x(1) x(2) x(3)])^3;

    %deifine the last three components of the dtdx vector
    dxdt(4) = x(1)*-1*mu/rCubed;
    dxdt(5) = x(2)*-1*mu/rCubed;
    dxdt(6) = x(3)*-1*mu/rCubed;
end

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