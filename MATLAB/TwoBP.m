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
