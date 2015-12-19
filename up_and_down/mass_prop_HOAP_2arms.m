% Mass properties of the HOAP3 body, two reference points has been taken 
% (see manual in page 6-4)
% For arms the reference point is the chest and for legs is the waist. 

function [left_arm,right_arm]=mass_prop_HOAP

% Distances of HOAP3 body in m(pag 6-5 of the manual)
ARM_LINK1=0.111;
ARM_LINK2=0.111;
ARM_LINK3=0.171;
LEG_LINK1=0.039;
LEG_LINK2=0.105;
LEG_LINK3=0.105;
LEG_LINK4=0.040;
BODY_LINK1=0.125;
BODY_LINK2=0.035;
HEAD_LINK1=0.103;
HEAD_LINK2=0.015;
WAIST_LINK1=0.055;
WAIST_LINK2=0.035;


% Left arm 
% Mass in Kg
left_arm.mass{1}=2.10e-1;
left_arm.mass{2}=2.34e-1;
left_arm.mass{3}=1.965e-1;
left_arm.mass{4}=2.16e-1;
% Local CoG in mm{with respect to coordinate system of DH parameters}
left_arm.CoG{1}= [-3.64197e-02 ,6.64174e+00, -6.34825e+00];
left_arm.CoG{2}= [7.47218e-01,-4.63619e+01,-3.77403e+00];
left_arm.CoG{3}= [-2.70991e+00, 1.60227e+00,-2.09019e+00];
left_arm.CoG{4}= [ 9.62091e-01, 6.64766e+01, 5.58629e-01];
% Inertia Tensor Kg.mm²
left_arm.I{1}=[8.66760e+01, 8.54331e-02, 2.13651e-01;8.54331e-02, 6.69975e+01,-3.14870e+00;2.13651e-01,-3.14870e+00, 7.29706e+01];
left_arm.I{2}=[1.90701e+02,-4.53865e+00, 4.72738e-01;-4.53865e+00, 9.55349e+01, 1.08196e+01; 4.72738e-01, 1.08196e+01, 1.67377e+02];
left_arm.I{3}=[6.51094e+01, 1.24947e-01, 1.66316e+00;1.24947e-01, 5.30426e+01,-5.66321e-01;1.66316e+00,-5.66321e-01, 6.81049e+01];
left_arm.I{4}=[3.59070e+02,-7.34962e-01,-7.26630e-01;-7.34962e-01, 1.03303e+02,-2.22301e+01;-7.26630e-01,-2.22301e+01, 3.35228e+02];

% Rigth arm
% Mass in Kg
right_arm.mass{1}=2.10e-1;
right_arm.mass{2}=2.34e-1;
right_arm.mass{3}=1.965e-1;
right_arm.mass{4}=2.16e-1;
% Local CoG in mm{with respect to coordinate system of DH parameters}
right_arm.CoG{1}= [8.28367e-02, 6.66808e+00, 6.34824e+00];
right_arm.CoG{2}= [-6.57560e-01,-4.63848e+01,-3.77395e+00];
right_arm.CoG{3}= [-2.72189e+00,-1.60245e+00,-2.20452e+00];
right_arm.CoG{4}= [1.00237e+00, 6.64225e+01,-6.15512e-01];
% Inertia Tensor Kg.mm²
right_arm.I{1}=[8.66688e+01, 6.58521e-02,-5.21141e-01;6.58521e-02, 6.69963e+01, 3.24962e+00;-5.21141e-01, 3.24962e+00, 7.29623e+01];
right_arm.I{2}=[1.90208e+02, 4.38002e+00,-1.91098e-01;4.38002e+00, 9.55647e+01, 1.09480e+01;-1.91098e-01, 1.09480e+01, 1.66913e+02];
right_arm.I{3}=[6.49972e+01,-1.21159e-01,1.21288e+00; -1.21159e-01, 5.29142e+01, 6.02001e-01;1.21288e+00, 6.02001e-01, 6.80659e+01];
right_arm.I{4}=[3.60567e+02,-4.53239e-01, 8.95113e-01;-4.53239e-01, 1.03381e+02, 2.20497e+01;8.95113e-01, 2.20497e+01, 3.36596e+02];


