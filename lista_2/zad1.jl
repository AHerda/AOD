using JuMP
import HiGHS

lotniska = [110000 220000 330000 440000]
L = 1:4

firmy = [275000, 550000, 660000]
F = 1:3

ceny = [
#   F1 F2 F3
    10 7 8;     # Lotnisko 1
    10 11 14;   # Lotnisko 2
    9 12 4;     # Lotnisko 3
    11 13 9     # Lotnisko 4
]

model = Model(HiGHS.Optimizer)

@variable(model, 0 <= var[L, F])
# Firmy nie mogą wysłać więcej niż mają
@constraint(model, [f in F], sum(var[:, f]) <= firmy[f])
# Ustawiamy najmniejszą ilość paliwa jakie każde lotnisko potrzebuje
@constraint(model, [l in L], sum(var[l, :]) >= lotniska[l])
# Funkcja celu
@objective(model, Min, sum((ceny .* var)))

optimize!(model)
solution_summary(model)
println("\nCena ogólna: ", round(Int, objective_value(model)), "\n")
for f in F, l in L
    println("Firma", f, " => Lotnisko", l, ": ", round(Int, value(var[l, f])))
end
print("\n")
for l in L
    println("Lotnisko", l, ": ", round(Int, value(sum(var[l, :]))))
end
print("\n")
for f in F
    println("Firma", f, ": ", round(Int, value(sum(var[:, f]))))
end