using JuMP
using Random
import HiGHS


m = 6
n = 6
k = 3
rng = MersenneTwister();

#conteners = rand(rng, 0:1, m, n)
conteners = [
    1  1  1  1  0  0;
    0  1  1  1  0  0;
    1  0  0  0  1  0;
    1  1  0  0  1  0;
    1  1  0  1  1  1;
    1  0  0  1  1  0
]
display(conteners)

model = Model(HiGHS.Optimizer)

@variable(model, var[1:m, 1:n], Bin)
# Ustawiamy że każde pole może zawierać albo kontener albo kamere, nie oba
@constraint(model, [i in 1:m, j in 1:n], var[i, j] + conteners[i, j] <= 1)
# Sprawdzamy czy każdy kontener ma kamere która go ogląda
for i in 1:m, j in 1:n; conteners[i, j] == 1
    col_range = max(1, i - k):min(m, i + k)
    row_range = max(1, j - k):min(n, j + k)
    @constraint(model, (sum(var[i, row_range]) + sum(var[col_range, j])) >= 1)
end
# Funkcja celu
@objective(model, Min, sum(var))

optimize!(model)
solution_summary(model)

println("\nUżytych lamp: ", round(Int, objective_value(model)))
print("Rozstawienie lamp:\n")
display(round.(Int, value.(var)))