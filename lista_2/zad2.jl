using Random
using JuMP
import HiGHS

n = 10

rng = MersenneTwister(1234);
time = zeros(n, n)
cost = zeros(n, n)

for i in 1:n, j in i:n
    time[i, j] = rand(rng, 1:(1.5 * n))
    cost[i, j] = rand(rng, 1:(1.5 * n))
end

for i in 1:n, j in 1:i
    time[i, j] = typemax(time[i, j])
    cost[i, j] = typemax(time[i, j])
end

time_cap = n * 1.5

town_start = 1
town_stop = n

function valid_path(x, start, stop)
    node = start
    while sum(x[node, :]) == 1
        for i in 1:n
            if x[node, i] == 1
                node = i
            end
        end
    end
    if node == stop
        return true
    else
        return false
    end
end

model = Model(HiGHS.Optimizer)

@variable(model, var[1:n, 1:n], Bin)
@constraint(model, [i in 1:n], sum(var[:, i]) <= 1)
@constraint(model, [i in 1:n], sum(var[i, :]) <= 1)
@constraint(model, sum(var'*time) <= time_cap)
@objective(model, Min, sum(var'*cost))

return time