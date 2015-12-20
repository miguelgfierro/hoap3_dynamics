% This file reads the trajectory of fordward walking (m03.csv) and simulates 
%it.
% Nota: en este archivo salen unos gráficos muy malos, esto es porque
% tenemos un tiempo de muestreo muy bajo, 1ms. El que hizo la trayectoria
% haría una interpolación con números en formato double (p.ej) pero al
% pasarlo a variables del encoder, se pierde esa precisión de double. Como
% yo me creo la trayectoria a partir de la del encoder y no de la original
% aparce un error muy grande en la posición, da la sensación de que la
% trayectoria se traza con escalones (si se hace un zoom en la posición se
% observa este efecto)  Al derivar discretamente, obtenemos una velocidad
% que no es real ya que se ha creado un error muy grande y al volver a
% derivar (aceleración) pasa lo mismo. Por lo tanto concluyo que los pares
% obtenidos en esta función no son representativos ya que no se dispone de
% la trayectoria real, sino de una discretizada. 
clear
clc
close all
format long

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

conversion=[1;1;-1;1;1;-1;1;1;-1;-1;1;1;1;-1;-1;-1;-1;1;-1;1]*pi/180/209;


% m03 file
n_points=17901;
Ts=0.001;
T=n_points*Ts;
encoder_vals=csvread('../share/m03_sinRs.csv',1,2,[1 2 n_points 21]);
joint_position=ones(n_points,1)*conversion'.*encoder_vals;
%q_waist=zeros(n_points,1);

% Joint Positions in the correct order so they can be simulated
for i=1:nb-1
    q(:,pos_simulator(i))=joint_position(:,i);
end 

% Draws joint positions
time=0:Ts:T-Ts;     %time vector for positions
figure('Name','LEFT ARM JOINT POSITIONS','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,q(:,pos_left_arm(ii)),'b'); %better with q than with joint_position
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad]')
end
   figure('Name','RIGHT ARM JOINT POSITIONS','NumberTitle','off')
for ii=1:length(pos_right_arm)
    subplot(2,2,ii);
    plot(time,q(:,pos_right_arm(ii)),'b');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad]') 
end   
figure('Name','LEFT LEG JOINT POSITIONS','NumberTitle','off')
for ii=1:length(pos_left_leg)
    subplot(2,3,ii);
    plot(time,q(:,pos_left_leg(ii)),'b');
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad]')
end
   figure('Name','RIGHT LEG JOINT POSITIONS','NumberTitle','off')
for ii=1:length(pos_right_leg)
    subplot(2,3,ii);
    plot(time,q(:,pos_right_leg(ii)),'b');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad]') 
end   

% Joint velocity
qd=diff(q,1,1)/Ts;
% Draws joint velocity
time=0:Ts:T-2*Ts;     %time vector for positions
figure('Name','LEFT ARM JOINT VELOCITY','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,qd(:,pos_left_arm(ii)),'b'); %better with q than with joint_position
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad/s]')
end
   figure('Name','RIGHT ARM JOINT VELOCITY','NumberTitle','off')
for ii=1:length(pos_right_arm)
    subplot(2,2,ii);
    plot(time,qd(:,pos_right_arm(ii)),'b');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad/s]') 
end   
figure('Name','LEFT LEG JOINT VELOCITY','NumberTitle','off')
for ii=1:length(pos_left_leg)
    subplot(2,3,ii);
    plot(time,qd(:,pos_left_leg(ii)),'b');
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad/s]')
end
   figure('Name','RIGHT LEG JOINT VELOCITY','NumberTitle','off')
for ii=1:length(pos_right_leg)
    subplot(2,3,ii);
    plot(time,qd(:,pos_right_leg(ii)),'b');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad/s]') 
end   


qdd=diff(q,2,1)/(Ts*Ts);
% Draws joint aceleration
time=0:Ts:T-3*Ts;     %time vector for positions
figure('Name','LEFT ARM JOINT ACELERATION','NumberTitle','off')
for ii=1:length(pos_left_arm)
    subplot(2,2,ii);
    plot(time,qdd(:,pos_left_arm(ii)),'b'); %better with q than with joint_position
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad/s²]')
end
   figure('Name','RIGHT ARM JOINT ACELERATION','NumberTitle','off')
for ii=1:length(pos_right_arm)
    subplot(2,2,ii);
    plot(time,qdd(:,pos_right_arm(ii)),'b');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad/s²]') 
end   
figure('Name','LEFT LEG JOINT ACELERATION','NumberTitle','off')
for ii=1:length(pos_left_leg)
    subplot(2,3,ii);
    plot(time,qdd(:,pos_left_leg(ii)),'b');
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad/s²]')
end
   figure('Name','RIGHT LEG JOINT ACELERATION','NumberTitle','off')
for ii=1:length(pos_right_leg)
    subplot(2,3,ii);
    plot(time,qdd(:,pos_right_leg(ii)),'b');
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad/s²]') 
end   

close all
q=q';
qd=qd';
qdd=qdd';
% Calculo de los pares en cada articulación
% for i=1:T/Ts-3
%     tau(:,i) = ID( HOAP, q(:,i), qd(:,i), qdd(:,i));
% end

% % Calculo de las aceleraciones en cada articulación (Dinámica directa)
% for i=1:T/Ts-2
%     qdd_aba(:,i) = FDab( HOAP, q(:,i), qd(:,i), tau(:,i));
%     qdd_crba(:,i) = FDcrb( HOAP, q(:,i), qd(:,i), tau(:,i));
% end


%joint_vals=[q_waist q];
drawmodel(HOAP,Ts,q');