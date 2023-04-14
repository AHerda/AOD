using Random
using JuMP
import HiGHS

n = 10

rng = MersenneTwister(1234);
time = rand(rng, 1:n, n, n)
cost = rand(rng, 1:n, n, n)

time_cap = n * 1.5

model = Model(HigHS.Optimizer)

@variable