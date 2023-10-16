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