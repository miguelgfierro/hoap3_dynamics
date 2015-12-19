% Manipulador fijo que simula el torso del HOAP
clear
clc
close all

% Length of arm's body in mm
L1=0.111; 
L2=L1;
L3=0.171;

% Modelo del robot
nb=8; 
trunk.NB=nb;
trunk.pitch = zeros(1,nb); % all revolute joints
trunk.parent=[0 0 1 2 3 4 5 6 7];
fact=0.15; %factor de tamaño

% trunk.Xtree{1} = Xroty(-pi/2)*Xtrans([L1 0 0]); % Brazo izquierdo
% trunk.Xtree{2} = Xroty(-pi/2)*Xtrans([-L1 0 0]); % Brazo derecho
% trunk.Xtree{3} = Xrotx(pi/2);
% trunk.Xtree{4} = Xrotx(pi/2);
% trunk.Xtree{5} = Xroty(pi/2);
% trunk.Xtree{6} = Xroty(pi/2);
% trunk.Xtree{7} = Xrotx(pi/2)*Xtrans([0 0 -L2]);
% trunk.Xtree{8} = Xrotx(pi/2)*Xtrans([0 0 -L2]);

% modo momia
trunk.Xtree{1} =Xrotz(-pi/2)*Xroty(pi/2)*Xtrans([L1 0 0]);
trunk.Xtree{2} =Xrotz(-pi/2)*Xroty(pi/2)*Xtrans([-L1 0 0]);
trunk.Xtree{3} = Xrotz(pi/2)*Xrotx(pi/2);
trunk.Xtree{4} = Xrotz(pi/2)*Xrotx(pi/2);
trunk.Xtree{5} = Xrotx(pi/2)*Xroty(-pi/2);
trunk.Xtree{6} = Xrotx(pi/2)*Xroty(-pi/2);
trunk.Xtree{7} = Xrotx(pi/2)*Xtrans([0 0 L2]);
trunk.Xtree{8} = Xrotx(pi/2)*Xtrans([0 0 L2]);

% Dibujo del robot
trunk.appearance{1}={{'cyl',[0 0 0],0.08*fact, L1, 'Z'},...
    {'cyl',[0 0 0],0.06*fact, 2*L1, 'X'},...
    {'cyl',[0 0 L1/2],0.3*fact, 0.8*fact, 'Z'}}; %fixed base
trunk.appearance{2}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }};
trunk.appearance{3}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' }};
trunk.appearance{4}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
trunk.appearance{5}={{'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z'}};
trunk.appearance{6}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
   { 'cyl', [0 0 L2/2], 0.05*fact, L2, 'Z' }};
trunk.appearance{7}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
   { 'cyl', [0 0 L2/2], 0.05*fact, L2, 'Z' }};
trunk.appearance{8}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
   { 'cyl', [0 L3/2 0], 0.05*fact, L3, 'Y' }};
trunk.appearance{9}={{ 'cyl', [0 0 0], 0.08*fact, 0.12*fact, 'Z' },...
   { 'cyl', [0 L3/2 0], 0.05*fact, L3, 'Y' }};

% Mass properties
[left_arm,right_arm]=mass_prop_HOAP_2arms;

for i = 1:nb/2 
    trunk.I{2*i-1}=mcI(left_arm.mass{i},left_arm.CoG{i}*1e-3,left_arm.I{i}*1e-6);
    trunk.I{2*i}=mcI(right_arm.mass{i},right_arm.CoG{i}*1e-3,right_arm.I{i}*1e-6);
end


% Constantes de tiempo
Ts=0.02;
T=4; % duración del movimiento

% Conversión que aparece en el manual
conversion=pi/180/209;
conversion_left_arm=pi/180/209*[-1 0 0 0;0 1 0 0;0 0 -1 0;0 0 0 1];
conversion_right_arm=pi/180/209*[1 0 0 0;0 1 0 0;0 0 -1 0;0 0 0 -1];

% Posición inicial
q0_left_arm=conversion_left_arm*[-18800; 2000; 0; -8800];
q0_right_arm=conversion_right_arm*[18810;-2000; 1; 8801];

% Puntos originales:
q1_left_arm = conversion_left_arm*[-11000; 4500; 4000; -21000];
q1_right_arm = conversion_right_arm*[11000; -4500; -4000; 21000];

q2_left_arm = conversion_left_arm*[-500; 12500; 2000; -16000];
q2_right_arm =conversion_right_arm*[500; -12500; -2000; 16000];


q_right_arm_ini = interpolate_variable (Ts, T/8, q0_right_arm, q1_right_arm);
q_left_arm_ini = interpolate_variable (Ts, T/8, q0_left_arm, q1_left_arm);

q_right_arm_med1 = interpolate_variable (Ts, T/16, q1_right_arm,q2_right_arm);
q_left_arm_med1 = interpolate_variable (Ts, T/16, q1_left_arm,q2_left_arm);

q_right_arm_med2 = interpolate_variable (Ts, T/16, q2_right_arm,q1_right_arm);
q_left_arm_med2 = interpolate_variable (Ts, T/16, q2_left_arm,q1_left_arm);

q_right_arm_med=[q_right_arm_med1,q_right_arm_med2];
q_left_arm_med=[q_left_arm_med1,q_left_arm_med2];

q_right_arm_med = replicate_vector (q_right_arm_med, 6);
q_left_arm_med = replicate_vector (q_left_arm_med, 6);

q_right_arm_fin = interpolate_variable (Ts, T/8, q1_right_arm,q0_right_arm);
q_left_arm_fin = interpolate_variable (Ts, T/8, q1_left_arm,q0_left_arm );

q_right_arm=[q_right_arm_ini,q_right_arm_med,q_right_arm_fin];
q_left_arm=[q_left_arm_ini,q_left_arm_med,q_left_arm_fin];



q=[q_left_arm(1,:);q_right_arm(1,:);q_left_arm(2,:);q_right_arm(2,:);q_left_arm(3,:);q_right_arm(3,:);q_left_arm(4,:);q_right_arm(4,:)];
qd=diff(q,1,2)/Ts;
qdd=diff(q,2,2)/(Ts*Ts);

% Calculo de los pares en cada articulación
for i=1:length(q)-2
    tau(:,i) = ID( trunk, q(:,i), qd(:,i), qdd(:,i));
end

% Simalación del movimiento
jnt_vals=q';
%drawmodel (trunk);
%drawmodel(trunk,Ts, jnt_vals );

% Gráficas de los posiciones de cada articulación
time=0:Ts:length(q)*Ts-Ts;     %time vector for positions
figure('Name','LEFT ARM LINK POSITIONS','NumberTitle','off')
for ii=1:nb/2
    subplot(2,2,ii);
    plot(time,q(2*ii-1,:),'b');
    %plot(time,range_q_right(ii,:)'*ones(1,length(time)),'r') % SIN HACER
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[rad]')
end
   figure('Name','RIGHT ARM LINK POSITIONS','NumberTitle','off')
for ii=1:nb/2
    subplot(2,2,ii);
    plot(time,q(2*ii,:),'b');
    %plot(time,range_q_right(ii,:)'*ones(1,length(time)),'r') % SIN HACER
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[rad]') 
end   

% Gráficas de los pares en cada articulación
time = 0:Ts:length(q)*Ts-3*Ts;     %time vector for torques
figure('Name','LEFT ARM LINKS TORQUES','NumberTitle','off')
for ii=1:nb/2
    subplot(2,2,ii);
    plot(time,tau(2*ii-1,:),'b');
    %plot(time,range_q_right(ii,:)'*ones(1,length(time)),'r') % SIN HACER
    title(['Joint ',num2str(ii)]);  
    xlabel('[s]')
    ylabel('[N.m]')
end
   figure('Name','RIGHT ARM LINK TORQUES','NumberTitle','off')
for ii=1:nb/2
    subplot(2,2,ii);
    plot(time,tau(2*ii,:),'b');
    %plot(time,range_q_right(ii,:)'*ones(1,length(time)),'r') % SIN HACER
    title(['Joint ',num2str(ii)]);
    xlabel('[s]')
    ylabel('[N.m]') 
end   

% % Calculo de las aceleraciones en cada articulación (Dinámica inversa)
% for i=1:T/Ts-2
%     qdd_aba(:,i) = FDab( trunk, q(:,i), qd(:,i), tau(:,i));
%     qdd_crba(:,i) = FDcrb( trunk, q(:,i), qd(:,i), tau(:,i));
% end
% 
% % Gráficas de las aceleraciones de cada articulación
% time = 0:Ts:length(q)*Ts-3*Ts;     %time vector for torques
% figure('Name','LEFT ARM LINK ACCELERATIONS','NumberTitle','off')
% for ii=1:nb/2
%     subplot(2,2,ii);
%     plot(time,qdd(2*ii-1,:),'b',time,qdd_aba(2*ii-1,:),'r',time,qdd_crba(2*ii-1,:),'g');
%     title(['Joint ',num2str(ii)]);  
%     xlabel('[s]')
%     ylabel('[m/s²]')
% end
%    figure('Name','RIGHT ARM LINK ACCELERATIONS','NumberTitle','off')
% for ii=1:nb/2
%     subplot(2,2,ii);
%     plot(time,qdd(2*ii,:),'b',time,qdd_aba(2*ii,:),'r',time,qdd_crba(2*ii,:),'g');
%     title(['Joint ',num2str(ii)]);
%     xlabel('[s]')
%     ylabel('[m/s²]') 
% end   

