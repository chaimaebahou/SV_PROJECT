#include "random.h"
#include "network.h"
#include <algorithm> 
static bool sort_using_greater_than(double u, double v)
{
   return u > v;
} 

void Network::resize(const size_t& n)
{
    RandomNumbers RNG ;
    values.clear();
    for(size_t i(0) ; i<n ; ++ i)
    {    
        values.push_back(RNG.normal());
    }
}

bool Network::add_link(const size_t& a, const size_t& b)
{
    if(links.find(a)->first == b or links.find(b)->second == a or (values.size() < a-1 or values.size() < b-1 or a==b  )) 
    {
		return false;
	}else
	{
		links.insert(std::make_pair(a,b));
		links.insert(std::make_pair(b,a));
		if((links.find(a)->second) == b or (links.find(b)->second) == a ) return true ;
		else{ return false ;}
    }
}

size_t Network::random_connect(const double& mean_deg)
{
    links.clear();
    RandomNumbers RNG ;
    size_t nbr(0) ;
    
    std::vector <int> nodes (size());
	RNG.uniform_int(nodes,0,size()-1);

    for(size_t node (0) ; node < size() ; ++node)
    {
		int n(0);
		int deg(RNG.poisson(mean_deg));
		while(n < deg)
		{
			if(degree(nodes[node]) < size())
			{
				add_link(node,nodes[node]);
				++nbr;
				++n;
			}
		}
	}
	
		return nbr ;	
}

size_t Network::set_values(const std::vector<double>& new_values)
{
    values.clear();
    size_t success(0); 
    for(size_t i(0);i< new_values.size() ; ++i )
    {
        values.push_back(new_values[i]);
        ++success;
    }
    return success;
}

size_t Network::size() const
{
    
    return values.size();
}

size_t Network::degree(const size_t &n) const
{
    size_t i(0);
        if(links.find(n)->first == n or links.find(n)->second == n 
        )
        {
            ++i;
        }
    return i;
    
}

double Network::value(const size_t &_n) const
{
    return values[_n];
}

std::vector<double> Network::sorted_values() const
{
    std::vector<double> sorted_v(values) ;
    std::sort(sorted_v.begin(), sorted_v.end(), sort_using_greater_than);
    return sorted_v ;
}

std::vector<size_t> Network::neighbors(const size_t& a) const
{
    std::vector<size_t> neighbors_list ;

    for(auto x : links)
    {
        if(x.first == a) neighbors_list.push_back(x.second);
    }
    
    return neighbors_list ;
}
