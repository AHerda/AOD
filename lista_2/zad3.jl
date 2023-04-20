using JuMP
import HiGHS

#=
miniówka
input penis into vedżajna
=#

min_auto = [
    2 4 3;
    3 6 5;
    5 7 6
]

max_auto = [
    3 7 5;
    5 7 10;
    8 12 10
]

min_shift = [10, 20, 18]
min_p = [10, 14, 13]

model = Model(HiGHS.Optimizer)

@variable(model, var[1:3, 1:3] >= 0)
# Liczba radiowozów musi mieścić się w widełkach
@constraint(model, [i in 1:3, j in 1:3], min_auto[i, j] <= var[i, j] <= max_auto[i, j])
# Liczba radiowozów w dzielnicach musi być większa od wymagań
@constraint(model, [i in 1:3], sum(var[i, :]) >= min_p[i])
# Liczba radiowozów w zmianach musi być większa od wymagań
@constraint(model, [i in 1:3], sum(var[:, i]) >= min_shift[i])

# Funkcja celu
@objective(model, Min, sum(var))

optimize!(model)
solution_summary(model)

print("\n")
for i in 1:3, j in 1:3
    print(Int(value(var[i, j])), " ")
    if j == 3
        print("\n")
    end
end
print("\n")
print("Użyte radiowozy: ", Int(value(sum(var))))