function vector_output = replicate_vector (vector_input, n_times)
vector_output = vector_input;
for jj = 2 : n_times
    vector_output = [vector_output, vector_input];
end