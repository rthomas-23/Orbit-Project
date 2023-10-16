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
