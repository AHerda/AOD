using JuMP
import HiGHS

lotniska = Dict("Lotnisko1" => 110000,
    "Lotnisko2" => 220000,
    "Lotnisko3" => 330000,
    "Lotnisko4" => 440000)
L = keys(lotniska)

firmy = Dict("Firma1" => 275000,
    "Firma2" => 550000,
    "Firma3" => 660000)
F = keys(firmy)

ceny = Dict("Firma1 => Lotnisko1" => 10,
    "Firma1 => Lotnisko2" => 10,
    "Firma1 => Lotnisko3" => 9,
    "Firma1 => Lotnisko4" => 11,
    "Firma2 => Lotnisko1" => 7,
    "Firma2 => Lotnisko2" => 11,
    "Firma2 => Lotnisko3" => 12,
    "Firma2 => Lotnisko4" => 13,
    "Firma3 => Lotnisko1" => 8,
    "Firma3 => Lotnisko2" => 14,
    "Firma3 => Lotnisko3" => 4,
    "Firma3 => Lotnisko4" => 9)


model = Model(HiGHS.Optimizer)

@variable(model, 0 <= ilosc[F, L])
for f in F
    @constraint(model, sum(ilosc[f, :]) <= firmy[f])
end
for l in L
    @constraint(model, sum(ilosc[:, l]) >= lotniska[l])
end
@objective(model, Min, sum(ceny["$(f) => $(l)"] * ilosc[f, l] for f in F, l in L))

optimize!(model)
solution_summary(model)
println("\nCena ogólna: ", Int(sum(ceny["$(f) => $(l)"] * value(ilosc[f, l]) for f in F, l in L)), "\n")
for f in F, l in L
    println(f, " => ", l, ": ", value(ilosc[f, l]))
end
print("\n")
for l in L
    println(l, ": ", value(sum(ilosc[:, l])))
end
print("\n")
for f in F
    println(f, ": ", value(sum(ilosc[f, :])))
end