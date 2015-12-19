function q_left=circulos(Ts,T,q_left_points)

n_points=size(q_left_points,2); 
n_joints=size(q_left_points,1);
paso=T/(n_points-1);
%intervalo=0:paso:T-paso;
intervalo=0:paso:T;
time=0:Ts:T-Ts;
for i=1:n_joints
    %yyR=q_right_points(i,:);
    yyL=q_left_points(i,:);
    %q_right(i,:)=spline(intervalo,yyR,time);
    q_left(i,:)=spline(intervalo,yyL,time);
end
    