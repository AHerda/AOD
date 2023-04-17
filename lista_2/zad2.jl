using Random
using JuMP
import HiGHS

n = 10

rng = MersenneTwister(1234);
time = zeros(n, n)
cost = zeros(n, n)

for i in 1:n, j in 1:(i + 4 - ((i + 4) % n))
    time[i, j] = rand(rng, 1:(1.5 * n))
    cost[i, j] = rand(rng, 1:(1.5 * n))
end

for i in 1:n, j in 1:i
    time[i, j] = typemax(time[i, j])
    cost[i, j] = typemax(time[i, j])
end

time_cap = n * 1.5

town_start = 1
town_end = n


model = Model(HiGHS.Optimizer)

@variable(model, 0 <= var[1:n, 1:n] <= 1, Bin)

# Nie może być połączenia tam gdzie cena == 0, połączenie nie istnieje
@constraint(model, [i in 1:n, j in 1:n, cost[i, j] == 0], var[i, j] == 0)

# Dla punktów tranzytowych
@constraint(model, [i in 1:n, i != town_start, i != town_end], sum(var[i, :]) == sum(var[:, i]))

# Blinas startowego punktu == 1, końcowego punktu == -1
@constraint(model, sum(var[town_start, :]) - sum(var[:, town_start]) == 1)
@constraint(model, sum(var[town_end, :]) - sum(var[:, town_end]) == -1)

#czas nie może przekraczać wyznaczonego ograniczenia
@constraint(model, sum(var'*time) <= time_cap)

@objective(model, Min, sum(var'*cost))

return time