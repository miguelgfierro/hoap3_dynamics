% This file reads a trajectory in csv format of the HOAP robot and simulates 
%it
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

%**************************************************************************
%                         TRAYECTORIA CIRCULOS
%**************************************************************************

% Simulación del robot en 4 pasos
Ts=0.02;
T=1; % duración del movimiento
n_points=T/Ts;

% Puntos originales:
conversion_left_arm=pi/180/209*[-1 0 0 0;0 1 0 0;0 0 -1 0;0 0 0 1];
conversion_right_arm=pi/180/209*[1 0 0 0;0 1 0 0;0 0 -1 0;0 0 0 -1];
q1_left_arm =conversion_left_arm*[-12000; 1000; 1; -18000]; 
q2_left_arm = conversion_left_arm*[-10000; 1000; 1; -20000];
q3_left_arm = conversion_left_arm*[-8000; 1000; 1; -18000]; 
q4_left_arm = conversion_left_arm*[-10000; 1000; 1; -16000]; 

q1_right_arm = conversion_right_arm*[12000; -1000; 1; 18000];
q2_right_arm = conversion_right_arm*[10000; -1000; 1; 20000];
q3_right_arm = conversion_right_arm*[8000; -1000; 1; 18000];
q4_right_arm = conversion_right_arm*[10000; -1000; 1; 16000];

q_left_points=[q1_left_arm q2_left_arm q3_left_arm q4_left_arm q1_left_arm];
q_left=circulos(Ts,T,q_left_points);

q_arms=[q_left(1,:);q_left(1,:);q_left(2,:);-q_left(2,:);q_left(3,:);-q_left(3,:);q_left(4,:);q_left(4,:)];
q_arms=q_arms';
q=zeros(n_points,nb);
for i=1:length(pos_left_arm)
    q(:,pos_left_arm(i))=q_arms(:,2*i-1);
    q(:,pos_right_arm(i))=q_arms(:,2*i);    
end

joint_vals=q;

q=q';
qd=[zeros(nb,1) diff(q,1,2)/Ts];
qdd=[zeros(nb,2) diff(q,2,2)/(Ts*Ts)];
    

% % Calculo de los pares en cada articulación
for i=1:n_points
    tau(:,i) = ID( HOAP, q(:,i), qd(:,i), qdd(:,i));
end

% Calculo de las aceleraciones en cada articulación (Dinámica directa)
for i=1:n_points
    qdd_aba(:,i) = FDab( HOAP, q(:,i), qd(:,i), tau(:,i));
    qdd_crba(:,i) = FDcrb( HOAP, q(:,i), qd(:,i), tau(:,i));
end


%joint_vals=[q_waist q];
drawmodel(HOAP,Ts,joint_vals); % Joint variable j in frame i

% Gráficas de los posiciones de cada articulación
time=0:Ts:T-Ts;     %time vector for positions
figure('Name','LEFT ARM LINK POSITIONS','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,q(pos_left_arm(ii),:),'b');
    %plot(time,range_q_right(ii,:)'*ones(1,length(time)),'r') % SIN HACER
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad]')
end
   figure('Name','RIGHT ARM LINK POSITIONS','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,q(pos_right_arm(ii),:),'b');
    %plot(time,range_q_right(ii,:)'*ones(1,length(time)),'r') % SIN HACER
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad]') 
end   

% Gráficas de los pares en cada articulación
time=0:Ts:T-Ts;     %time vector for torques
figure('Name','LEFT ARM LINK TORQUES FIXED BODY','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,tau(pos_left_arm(ii),:),'b');
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[N.m]')
end
   figure('Name','RIGHT ARM LINK TORQUES FIXED BODY','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,tau(pos_right_arm(ii),:),'b');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[N.m]') 
end   

% Gráficas de las aceleraciones de cada articulación
figure('Name','LEFT ARM LINK ACCELERATIONS FIXED BODY','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,qdd(pos_left_arm(ii),:),'b',time,qdd_aba(pos_left_arm(ii),:),'r',time,qdd_crba(pos_right_arm(ii),:),'g');
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[m/s²]')
    legend('qdd','qdd_a_b_a','qdd_c_r_b_a')
end
   figure('Name','RIGHT ARM LINK ACCELERATIONS FIXED BODY','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,qdd(pos_right_arm(ii),:),'b',time,qdd_aba(pos_right_arm(ii),:),'r',time,qdd_crba(pos_right_arm(ii),:),'g');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[m/s²]')
    legend('qdd','qdd_a_b_a','qdd_c_r_b_a')
end   
