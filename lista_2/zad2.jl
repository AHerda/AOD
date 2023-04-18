using Random
using JuMP
import HiGHS
import LinearAlgebra

n = 10

rng = MersenneTwister();

time = zeros(n, n)
cost = zeros(n, n)
bilance = zeros(n)

for i in 1:n, j in 1:min(n, i + 5)
    time[i, j] = rand(rng, 1:10)
    cost[i, j] = rand(rng, 1:10)
end


time_cap = n * 1.5

town_start = 1
town_end = n
bilance[town_start] = 1
bilance[town_end] = -1


model = Model(HiGHS.Optimizer)

@variable(model, var[1:n, 1:n], Bin)
# Nie może być połączenia tam gdzie cena == 0, połączenie nie istnieje
@constraint(model, [i in 1:n, j in 1:n; cost[i, j] == 0], var[i, j] == 0)
# Wyjście i wejście z każdego node'a może byctylko jedno
@constraint(model, [i in 1:n], sum(var[i, :]) <= 1)
@constraint(model, [i in 1:n], sum(var[:, i]) <= 1)
# Bilans wszystkich pubnktów, zachowanie poprawności ścieżki
@constraint(model, [i in 1:n], sum(var[i, :]) - sum(var[:, i]) == bilance[i])
#czas nie może przekraczać wyznaczonego ograniczenia
@constraint(model, sum(var .* time) <= time_cap)

@objective(model, Min, sum(var .* cost))

optimize!(model)
solution_summary(model)

println("\nKoszt najkrótszej drogi: ", round(Int, objective_value(model)))
println("Czas najkrótszej drogi: ", round(Int, value(sum(time .* var))))
println("Ścieżka:")
display(round.(Int, value.(var)))