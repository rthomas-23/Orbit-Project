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