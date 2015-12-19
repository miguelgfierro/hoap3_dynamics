% Mass properties of the HOAP3 body, two reference points has been taken 
% (see manual in page 6-4)
% For arms the reference point is the chest and for legs is the waist. 

function [body,left_arm,right_arm,left_leg,right_leg,head]=mass_prop_HOAP

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

% Left leg
% Mass in Kg
left_leg.mass{1}=5.87e-02;
left_leg.mass{2}=2.10e-01;
left_leg.mass{3}=5.19e-01;
left_leg.mass{4}=3.28e-01;
left_leg.mass{5}=1.95e-01;
left_leg.mass{6}=1.54e-01;
% Local CoG in mm{with respect to coordinate system of DH parameters}
left_leg.CoG{1}= [3.00449e+00,-2.25088e+00, 3.35846e+01];
left_leg.CoG{2}= [-2.71179e+00,-1.24723e+00, 2.38665e+00];
left_leg.CoG{3}= [-6.99224e+01, 6.27642e+00, 3.31502e+00];
left_leg.CoG{4}= [-5.08386e+01, 5.37031e+00, 4.87773e+00];
left_leg.CoG{5}= [2.92057e+00, 3.69219e+00, 1.19731e+00];
left_leg.CoG{6}= [-2.92236e+01,-3.34620e+00, 8.27642e+00];
% Inertia Tensor Kg.mm²
left_leg.I{1}=[5.98222e+01,-3.85905e-01,-5.71594e+00;-3.85905e-01, 4.32083e+01,-2.91155e+00;-5.71594e+00,-2.91155e+00, 2.95769e+01];
left_leg.I{2}=[6.93238e+01, 5.11967e-01, 4.43105e-01;5.11967e-01, 5.85697e+01,-6.18331e-01;4.43105e-01,-6.18331e-01, 5.45564e+01];
left_leg.I{3}=[3.33124e+02,-1.04299e+01,-2.93471e+01;-1.04299e+01, 7.14361e+02, 2.11288e+01;-2.93471e+01, 2.11288e+01, 6.69044e+02];
left_leg.I{4}=[2.10989e+02,-2.62826e+01, 1.58357e+01;-2.62826e+01, 3.31772e+02, 8.60718e+00;1.58357e+01, 8.60718e+00, 2.73517e+02];
left_leg.I{5}=[6.35542e+01, 2.67585e-01, 8.67380e-01;2.67585e-01, 5.31460e+01, 8.92463e-01;8.67380e-01, 8.92463e-01, 5.26905e+01];
left_leg.I{6}=[2.19156e+02,-2.72205e+00, 1.63411e+01;-2.72205e+00, 1.78310e+02, 2.84694e+00;1.63411e+01, 2.84694e+00, 8.19287e+01];

% Right leg
% Mass in Kg
right_leg.mass{1}=5.87e-02;
right_leg.mass{2}=2.10e-01;
right_leg.mass{3}=5.19e-01;
right_leg.mass{4}=3.28e-01;
right_leg.mass{5}=1.95e-01;
right_leg.mass{6}=1.54e-01;
% Local CoG in mm{with respect to coordinate system of DH parameters}
right_leg.CoG{1}= [-3.01500e+00,-2.23990e+00, 3.35846e+01];
right_leg.CoG{2}= [-2.72697e+00, 1.13482e+00, 2.37780e+00];
right_leg.CoG{3}= [-6.98208e+01, 6.16508e+00,-3.26392e+00];
right_leg.CoG{4}= [-5.08521e+01, 5.36785e+00,-4.69750e+00];
right_leg.CoG{5}= [ 2.93669e+00, 3.66853e+00,-1.33746e+00];
right_leg.CoG{6}= [-2.92236e+01, 3.24167e+00, 8.27642e+00];
% Inertia Tensor Kg.mm²
right_leg.I{1}=[5.98251e+01, 4.07692e-01, 5.70458e+00;4.07692e-01, 4.32046e+01,-2.93763e+00;5.70458e+00,-2.93763e+00, 2.95761e+01];
right_leg.I{2}=[6.94143e+01,-8.93597e-01, 4.50011e-01;-8.93597e-01, 5.87096e+01, 5.13879e-01;4.50011e-01, 5.13879e-01, 5.47365e+01];
right_leg.I{3}=[3.33437e+02,-1.04660e+01, 2.86176e+01;-1.04660e+01, 7.15435e+02,-1.85334e+01;2.86176e+01,-1.85334e+01, 6.69659e+02];
right_leg.I{4}=[2.14004e+02,-2.63054e+01,-1.52711e+01;-2.63054e+01, 3.34738e+02,-9.48167e+00;-1.52711e+01,-9.48167e+00, 2.73483e+02];
right_leg.I{5}=[6.35459e+01, 2.96980e-01,-5.85740e-01;2.96980e-01, 5.29750e+01,-9.54911e-01;-5.85740e-01,-9.54911e-01, 5.27906e+01];
right_leg.I{6}=[2.19262e+02, 3.30179e+00, 1.63411e+01;3.30179e+00, 1.78310e+02,-3.47988e+00;1.63411e+01,-3.47988e+00, 8.20349e+01];

% Body (worst of the cases)
% Mass in Kg
body.mass{1}=3.26e+00;
body.mass{2}=4.17e-01;
% Local CoG in mm{with respect to coordinate system of DH parameters}
body.CoG{1}= [-4.94890e+01, 8.92912e-01, 8.41741e+01]; % in respect to waist frame
body.CoG{2}= [-3.22707e+01, 1.11375e+01,-3.29172e-01]; % in respect to BODY_JOINT[1] frame
% Inertia Tensor Kg.mm²
body.I{1}=[1.21947e+04, 2.95479e+02, 6.84001e+02;2.95479e+02, 1.75644e+04, 1.45795e+02;6.84001e+02, 1.45795e+02, 1.56708e+04];
body.I{2}=[6.60777e+02, 6.74647e+00, 4.93444e+00;6.74647e+00, 6.42117e+02,-1.51777e+00;4.93444e+00,-1.51777e+00, 1.70178e+02];

% Head
% Mass in Kg
head.mass{1}=7.10e-02;
head.mass{2}=4.12e-01;
% Local CoG in mm{with respect to coordinate system of DH parameters}
head.CoG{1}= [5.39731e+00,-1.58067e+00, 5.64034e+01];
head.CoG{2}= [-1.03952e+00,-5.17985e+00, 1.82267e-02];
% Inertia Tensor Kg.mm²
head.I{1}=[6.90569e+01, 1.08546e+00,-9.83691e+00;1.08546e+00, 6.41244e+01, 5.08942e+00;-9.83691e+00, 5.08942e+00, 3.33541e+01];
head.I{2}=[5.52356e+02, 7.77318e+00, 3.17868e+00;7.77318e+00, 7.32140e+02, 4.57784e-01;3.17868e+00, 4.57784e-01, 6.82132e+02];





