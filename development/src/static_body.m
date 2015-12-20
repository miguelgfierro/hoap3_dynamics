% Manipulador fijo que simula el cuerpo completo del HOAP
clear
clc
close all

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

nb=21; % 4 for each arm, 6 for each leg and one for the HOAP 
HOAP.NB=nb;
HOAP.pitch = zeros(1,nb); % all revolute joints
HOAP.parent=[0 1 1 1 1 2 3 4 5 6 7 8 9 10 11 12 13 16 17 18 19];

fact=0.15; %factor de tamaño

% modo momia
HOAP.Xtree{1} = Xrotz(-pi/2)*Xroty(-pi/2)*Xtrans([0 -BODY_LINK2 0]); % Waist
HOAP.Xtree{2} = Xrotx(pi)*Xtrans([-BODY_LINK2 BODY_LINK1 -ARM_LINK1]); %Left arm 
HOAP.Xtree{3} = Xrotx(pi)*Xtrans([-BODY_LINK2 BODY_LINK1 ARM_LINK1]); %Right arm
HOAP.Xtree{4} = Xroty(pi/2)*Xrotz(pi/2)*Xtrans([-WAIST_LINK2 -WAIST_LINK1 -LEG_LINK1]); %Left leg
HOAP.Xtree{5} = Xroty(pi/2)*Xrotz(pi/2)*Xtrans([-WAIST_LINK2 -WAIST_LINK1 LEG_LINK1]); %Right leg
HOAP.Xtree{6} = Xrotz(pi/2)*Xrotx(pi/2);
HOAP.Xtree{7} = Xrotz(pi/2)*Xrotx(pi/2);
HOAP.Xtree{8} = Xrotz(pi/2)*Xrotx(pi/2);
HOAP.Xtree{9} = Xrotz(pi/2)*Xrotx(pi/2);
HOAP.Xtree{10} = Xrotx(pi/2)*Xroty(-pi/2);
HOAP.Xtree{11} = Xrotx(pi/2)*Xroty(-pi/2);
HOAP.Xtree{12} = Xrotx(pi/2);
HOAP.Xtree{13} = Xrotx(pi/2);
HOAP.Xtree{14} = Xrotx(pi/2)*Xtrans([0 0 ARM_LINK2]);
HOAP.Xtree{15} = Xrotx(pi/2)*Xtrans([0 0 ARM_LINK2]);
HOAP.Xtree{16} = Xtrans([-LEG_LINK2 0 0]);
HOAP.Xtree{17} = Xtrans([-LEG_LINK2 0 0]);
HOAP.Xtree{18} = Xtrans([-LEG_LINK3 0 0]);
HOAP.Xtree{19} = Xtrans([-LEG_LINK3 0 0]);
HOAP.Xtree{20} = Xrotx(-pi/2);
HOAP.Xtree{21} = Xrotx(-pi/2);

% Dibujo del robot
backbone=BODY_LINK1+WAIST_LINK1+HEAD_LINK1;
backbone_pos=backbone/2-WAIST_LINK1;
HOAP.appearance{1}={{'cyl', [0 0 backbone_pos], 0.08*fact,backbone, 'Z' },...
    {'cyl', [0 0 -WAIST_LINK1], 0.08*fact,2*LEG_LINK1, 'X'},...
    {'cyl', [0 0 BODY_LINK1], 0.08*fact,2*ARM_LINK1, 'X'},...
    {'cyl', [0 0 BODY_LINK1+HEAD_LINK1], 0.3*fact,HEAD_LINK1, 'Z' }}; 
%HOAP.appearance{2}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }}; 
HOAP.appearance{2}={{0}}; % No dibujamos el joint de la cadera por simplicidad(no se usa)
HOAP.appearance{3}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }};
HOAP.appearance{4}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
HOAP.appearance{5}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
HOAP.appearance{6}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
HOAP.appearance{7}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }};
HOAP.appearance{8}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
HOAP.appearance{9}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
HOAP.appearance{10}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};

HOAP.appearance{11}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [0 0 ARM_LINK2/2], 0.05*fact, ARM_LINK2, 'Z' }};
HOAP.appearance{12}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
    { 'cyl', [0 0 ARM_LINK2/2], 0.05*fact, ARM_LINK2, 'Z' }};
HOAP.appearance{13}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [-LEG_LINK2/2 0 0], 0.05*fact, LEG_LINK2, 'X' }};
HOAP.appearance{14}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [-LEG_LINK2/2 0 0], 0.05*fact, LEG_LINK2, 'X' }};

HOAP.appearance{15}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [0 ARM_LINK3/2 0], 0.05*fact, ARM_LINK3, 'Y' }};
HOAP.appearance{16}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [0 ARM_LINK3/2 0], 0.05*fact, ARM_LINK3, 'Y' }};
HOAP.appearance{17}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [-LEG_LINK3/2 0 0], 0.05*fact, LEG_LINK3, 'X' }};
HOAP.appearance{18}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [-LEG_LINK3/2 0 0], 0.05*fact, LEG_LINK3, 'X' }};

HOAP.appearance{19}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
HOAP.appearance{20}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
HOAP.appearance{21}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [-LEG_LINK4/2 0 0], 0.05*fact, LEG_LINK4, 'X' },...
    { 'box', [-LEG_LINK4, -LEG_LINK4+LEG_LINK4/4; -0.15*fact, 0.15*fact; -0.2*fact, 0.4*fact] }};
HOAP.appearance{22}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'},...
    { 'cyl', [-LEG_LINK4/2 0 0], 0.05*fact, LEG_LINK4, 'X' },...
    { 'box', [-LEG_LINK4, -LEG_LINK4+LEG_LINK4/4; -0.15*fact, 0.15*fact; -0.2*fact, 0.4*fact] }};

%HOAP.appearance{1}={{0}}; 
%HOAP.appearance{2}={{0}}; 
% HOAP.appearance{3}={{0}};
% HOAP.appearance{4}={{0}};
% HOAP.appearance{5}={{0}};
% HOAP.appearance{6}={{0}};
% HOAP.appearance{7}={{0}};
% HOAP.appearance{8}={{0}};
% HOAP.appearance{9}={{0}};
% HOAP.appearance{10}={{0}};
% HOAP.appearance{11}={{0}};
% HOAP.appearance{12}={{0}};
% HOAP.appearance{13}={{0}};
% HOAP.appearance{14}={{0}};
% HOAP.appearance{15}={{0}};
% HOAP.appearance{16}={{0}};
% HOAP.appearance{17}={{0}};
% HOAP.appearance{18}={{0}};
% HOAP.appearance{19}={{0}};
% HOAP.appearance{20}={{0}};
% HOAP.appearance{21}={{0}};
% HOAP.appearance{22}={{0}};


%Mass properties
[body,left_arm,right_arm,left_leg,right_leg,head]=mass_prop_HOAP;

%Simplification of the body mass,CoG and Inertia. Mass body is equal to all
%the parts masses, CoG is the same of body 1 but in the new frame and I is
%the same of body 1 but in the new frame
mass_body=body.mass{1}+body.mass{2}+head.mass{1}+head.mass{2};
A=Xrotx(-pi/2);
Rotax=A(1:3,1:3);
CoG_body=body.CoG{1}*Rotax*1e-3-[BODY_LINK2 0 0];
I_body=Rotax'*body.I{1}*Rotax*1e-6;

HOAP.I{1}=mcI(mass_body,CoG_body,I_body);

% Lets group for kinematic trees as in the HOAP manual
pos_left_arm=[2 6 10 14];
pos_right_arm=[3 7 11 15];
pos_left_leg=[4 8 12 16 18 20];
pos_right_leg=[5 9 13 17 19 21];
pos_simulator=[pos_right_leg pos_right_arm pos_left_leg pos_left_arm];

for i = 1:length(pos_left_arm)
    HOAP.I{pos_left_arm(i)}=mcI(left_arm.mass{i},left_arm.CoG{i}*1e-3,left_arm.I{i}*1e-6);
    HOAP.I{pos_right_arm(i)}=mcI(right_arm.mass{i},right_arm.CoG{i}*1e-3,right_arm.I{i}*1e-6);
end

for i = 1:length(pos_left_leg)
    HOAP.I{pos_left_leg(i)}=mcI(left_leg.mass{i},left_leg.CoG{i}*1e-3,left_leg.I{i}*1e-6);
    HOAP.I{pos_right_leg(i)}=mcI(right_leg.mass{i},right_leg.CoG{i}*1e-3,right_leg.I{i}*1e-6);
end

conversion=[1;1;-1;1;1;-1;1;1;-1;-1;1;1;1;-1;-1;-1;-1;1;-1;1]*pi/180/209;

% initial pose 
motors0 = [0; 40; 3695; 9537; -5807; -334; 18810;-2000; 1; 8801; 0; 40; -3730; -9537; 5807; 425; -18800; 2000; 0; -8800]; 

joint_position=conversion.*motors0;
q(1)=0;
for i=1:nb-1
    q(pos_simulator(i))=joint_position(i);
end

joint_vals=[q ;q];
drawmodel(HOAP,1,joint_vals);







