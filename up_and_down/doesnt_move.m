function q_out=doesnt_move (Ts,T,q_in)
q_out=[];
n_times=T/Ts;
for i=1:n_times
    q_out=[q_out,q_in];
end
    