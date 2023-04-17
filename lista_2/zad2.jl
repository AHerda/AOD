using Random
using JuMP
import HiGHS
import LinearAlgebra

n = 10

rng = MersenneTwister();

time = zeros(n, n)
cost = zeros(n, n)
bilance = zeros(n)

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
bilance[town_start] = 1
bilance[town_end] = -1


model = Model(HiGHS.Optimizer)

@variable(model, var[1:n, 1:n], Bin)
# Nie może być połączenia tam gdzie cena == 0, połączenie nie istnieje
@constraint(model, [i in 1:n, j in 1:n, cost[i, j] == 0], var[i, j] == 0)
# Bilans wszystkich pubnktów, zachowanie poprawności ścieżki
@constraint(model, [i in 1:n], sum(var[i, :]) - sum(var[:, i]) == bilance[i])
#czas nie może przekraczać wyznaczonego ograniczenia
@constraint(model, sum(time .* var) <= time_cap)

@objective(model, Min, sum(cost .* var))

optimize!(model)
solution_summary(model)

print("\nKoszt najkrótszej drogi: ", objective_value(model))
print("Czas najkrótszej drogi: ", value(sum(time .* var)))
print("Ścieżka: ", value(var))

return time