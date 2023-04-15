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
println(time)
println(cost)

time_cap = n * 1.5

town_start = 1
town_stop = 10

model = Model(HigHS.Optimizer)

@variable(model, )

return time