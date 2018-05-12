

struct meta_parameters

    sigma::Float64

end

function new_point(x::Float64,sigma::Float64)
    
    x+sigma*randn()

end


function test(p1::Float64,p2::Float64)

    if p2>=p1
        return true
    end

    u=rand()

    if u<p2/p1
        return true
    end

    return false

end

function p(x::Float64)

    gap=1.5::Float64

    1/sqrt(2*pi)*(exp(-(x+gap)^2/2)+exp(-(x-gap)^2/2))*0.5

end

function histogram(x_list,n::Int64)

    min=minimum(x_list)
    max=maximum(x_list)

    dx=((max-min)/n)::Float64

    h=zeros(Float64,n+1)
    x_values=zeros(Float64,n+1)

    for i in 1:n+1
        x_values[i]=min+(i-1)*dx+dx/2
    end

    for x in x_list
        h[floor(Int64,(x-min)/dx)+1]+=1/dx
    end

    (x_values,h)

end

n_points=1000000::Int64

mp=meta_parameters(0.1)

x_initial=3.::Float64

x_list=Float64[x_initial]

for counter in 1:n_points

    x_proposed=new_point(x_list[end],mp.sigma)
    
    if test(p(x_list[end]),p(x_proposed))
        push!(x_list,x_proposed)
    else
        push!(x_list,x_list[end])
    end



end

n_histogram=100::Int64
burn_in=1000


xh=histogram(x_list[burn_in:end],n_histogram)

for i in 1:length(xh[1])
    println(xh[1][i]," ",xh[2][i]/(n_points-burn_in)," ",p(xh[1][i]))
end
