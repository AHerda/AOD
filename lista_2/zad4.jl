using JuMP
using Random
import HiGHS


m = 7
n = 10
k = 3

rng = MersenneTwister();

conteners = rand(rng, 0:1, m, n)
display(conteners)

model = Model(HiGHS.Optimizer)

@variable(model, var[1:m, 1:n], Bin)
@constraint(model, [i in 1:m, j in 1:n], var[i, j] + conteners[i, j] <= 1)
for i in 1:m, j in 1:n
    if conteners[i, j] == 1
        col_range = max(1, i - k):min(m, i + k)
        row_range = max(1, j - k):min(n, j + k)
        @constraint(model, (sum(var[i, row_range]) + sum(var[col_range, j])) >= 1)
    end
end
@objective(model, Min, sum(var))

optimize!(model)
solution_summary(model)

println("\nUżytych lamp: ", round(Int, objective_value(model)))
print("Rozstawienie lamp:\n")
display(round.(Int, value.(var)))