theta = 0.9
mu    = 0.0


data = Matrix{Float64}(1,100)

old_eps = 0.0
for i = 1:length(data)
    r = randn()
    data[i] = old_eps + theta * r
    old_eps = r
end

writecsv("data_ma1.csv", data)
