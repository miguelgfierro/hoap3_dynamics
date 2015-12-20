% Manipulador fijo que simula el cuerpo completo del HOAP
% This program draws all the body joints
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

nb=21; % 4 for each arm, 6 for each leg and one for the body 
body.NB=nb;
body.pitch = zeros(1,nb); % all revolute joints
%body.parent=[0 1 1 1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17];
body.parent=[0 1 1 1 1 2 3 4 5 6 7 8 9 10 11 12 13 16 17 18 19];
fact=0.15; %factor de tamaño


% modo momia
body.Xtree{1} = Xrotz(-pi/2)*Xroty(-pi/2)*Xtrans([0 -BODY_LINK2 0]); % Waist
body.Xtree{2} = Xrotx(pi)*Xtrans([-BODY_LINK2 BODY_LINK1 -ARM_LINK1]); %Left arm 
body.Xtree{3} = Xrotx(pi)*Xtrans([-BODY_LINK2 BODY_LINK1 ARM_LINK1]); %Right arm
body.Xtree{4} = Xroty(pi/2)*Xrotz(pi/2)*Xtrans([-WAIST_LINK2 -WAIST_LINK1 -LEG_LINK1]); %Left leg
body.Xtree{5} = Xroty(pi/2)*Xrotz(pi/2)*Xtrans([-WAIST_LINK2 -WAIST_LINK1 LEG_LINK1]); %Right leg
body.Xtree{6} = Xrotz(pi/2)*Xrotx(pi/2);
body.Xtree{7} = Xrotz(pi/2)*Xrotx(pi/2);
body.Xtree{8} = Xrotz(pi/2)*Xrotx(pi/2);
body.Xtree{9} = Xrotz(pi/2)*Xrotx(pi/2);
body.Xtree{10} = Xrotx(pi/2)*Xroty(-pi/2);
body.Xtree{11} = Xrotx(pi/2)*Xroty(-pi/2);
body.Xtree{12} = Xrotx(pi/2);
body.Xtree{13} = Xrotx(pi/2);
body.Xtree{14} = Xrotx(pi/2)*Xtrans([0 0 ARM_LINK2]);
body.Xtree{15} = Xrotx(pi/2)*Xtrans([0 0 ARM_LINK2]);
body.Xtree{16} = Xtrans([-LEG_LINK2 0 0]);
body.Xtree{17} = Xtrans([-LEG_LINK2 0 0]);
body.Xtree{18} = Xtrans([-LEG_LINK3 0 0]);
body.Xtree{19} = Xtrans([-LEG_LINK3 0 0]);
body.Xtree{20} = Xrotx(-pi/2);
body.Xtree{21} = Xrotx(-pi/2);
% body.Xtree{10} = Xrotx(pi/2)*Xtrans([0 0 LEG_LINK2]);
% body.Xtree{11} = Xrotx(pi/2)*Xtrans([0 0 LEG_LINK2]);
% 
% body.Xtree{12} = Xrotz(pi/2)*Xrotx(pi/2);
% body.Xtree{13} = Xrotz(pi/2)*Xrotx(pi/2);
% body.Xtree{14} = Xrotx(pi/2)*Xroty(-pi/2);
% body.Xtree{15} = Xrotx(pi/2)*Xroty(-pi/2);
% body.Xtree{16} =Xtrans([0 LEG_LINK1 0]);
% body.Xtree{17} = Xrotx(pi/2)*Xtrans([0 0 LEG_LINK2]);
% body.Xtree{18} = Xtrans([0 0 LEG_LINK1]);
% body.Xtree{19} =Xtrans([0 0 LEG_LINK1]);
% body.Xtree{20} =Xtrans([0 0 LEG_LINK1]);
% body.Xtree{21} =Xtrans([0 0 LEG_LINK1]);

% Dibujo del robot
% body.appearance{1}={{'cyl',[0 0 0],0.08*fact, LEG_LINK1, 'Z'},...
%     {'cyl',[0 0 0],0.06*fact, 2*LEG_LINK1, 'X'},...
%     {'cyl',[0 0 LEG_LINK1/2],0.3*fact, 0.8*fact, 'Z'}}; %fixed base

body.appearance{1}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }}; 
body.appearance{2}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }}; 
body.appearance{3}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }};
body.appearance{4}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{5}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{6}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{7}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }};
body.appearance{8}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{9}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{10}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};

body.appearance{11}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{12}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }};
body.appearance{13}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{14}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};

body.appearance{15}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{16}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{17}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{18}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};

body.appearance{19}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{20}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{21}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
body.appearance{22}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};

% body.appearance{6}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
%    { 'cyl', [0 0 LEG_LINK2/2], 0.05*fact, LEG_LINK2, 'Z' }};
% body.appearance{7}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
%    { 'cyl', [0 0 LEG_LINK2/2], 0.05*fact, LEG_LINK2, 'Z' }};
% body.appearance{8}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
%    { 'cyl', [0 L3/2 0], 0.05*fact, L3, 'Y' }};
% body.appearance{9}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
%    { 'cyl', [0 L3/2 0], 0.05*fact, L3, 'Y' }};

%body.appearance{1}={{0}}; 
%body.appearance{2}={{0}}; 
% body.appearance{3}={{0}};
% body.appearance{4}={{0}};
% body.appearance{5}={{0}};
% body.appearance{6}={{0}};
% body.appearance{7}={{0}};
% body.appearance{8}={{0}};
% body.appearance{9}={{0}};
% body.appearance{10}={{0}};
% body.appearance{11}={{0}};
% body.appearance{12}={{0}};
% body.appearance{13}={{0}};
% body.appearance{14}={{0}};
% body.appearance{15}={{0}};
% body.appearance{16}={{0}};
% body.appearance{17}={{0}};
% body.appearance{18}={{0}};
% 
% body.appearance{19}={{0}};
% body.appearance{20}={{0}};
% body.appearance{21}={{0}};
% body.appearance{22}={{0}};

for i = 1:nb
    body.I{i}=mcI( 0, [0,0,0], zeros(3) );
    %trunk.I{i+1} = mcI( left_arm.mass{i}, left_arm.CoG{i},left_arm.I{i} );
end

drawmodel(body);
