using JuMP
using Random
import HiGHS

time_max = 60                   # czas (w godzinach) maksymalny jaki może pracować jedna maszyna w tygodniu
ppk = [9 7 6 5]                 # price per kilo produktów 1, 2, 3, 4
cpk = [4 1 1 1]                 # cost per kilo za produkty 1, 2, 3, 4
ipk = ppk - cpk                 # income per kilo za profukty 1, 2, 3, 4
cph = [2, 2, 3]                 # cost per hour dla maszyn 1, 2, 3
maks_demand = [400 100 150 500] # maksymalny tygodniowy popyt na produkty 1, 2, 3, 4

# minutes per kilogram dla produktów i maszyn
mpk = [
#   M1 M2 M3
    5 10 6; # P1
    3 6 4;  # P2
    4 5 3;  # P3
    4 2 1   # P4
]

model = Model(HiGHS.Optimizer)

@variable(model, 0 <= var[1:4, 1:3] <= time_max * 60, Int)
# Ustawianie maksymalnego czasu działania maszyn
@constraint(model, [i in 1:3], sum(var[:, i]) <= time_max * 60)
# Ustawianie maksymalnych popytow
@constraint(model, [i in 1:4], sum((var ./ mpk)[i, :]) <= maks_demand[i])
# Funkcja celu 
@objective(model, Max, sum(ipk * (var ./ mpk)) - sum((var ./ 60) * cph))

optimize!(model)
solution_summary(model)

println("\nTygodniowe czasy korzystania z maszyn, podzielone na produkty:")
display(round.(Int, value.(var)))
println("\nTygodniowe produkcje w kg:")
for i in 1:4
    println("\tProdukt $(i): ", round(Int, value(sum((var ./ mpk)[i, :]))), "kg")
end
println("\nZysk ze sprzedaży tygodniowej produkcji: ", "\$", round(Int, objective_value(model)))