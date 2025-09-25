

/**
 * write by fengchengyu in 09/18/2025 for question1 in Homework3
 */

#include <iostream>
#include <vector>


/**
 * @brief Compute the minimum number of refueling stops required 
 *        to travel from USC (position 0) to Santa Monica.
 *
 * @param santa_monica_distance The total distance from USC to Santa Monica.
 * @param gas_stations A vector of gas station positions size == n.
 * @param p The maximum distance the car can travel on a full tank.
 *
 * @return A pair {canReach, minStops}:
 *         - first  : true if Santa Monica is reachable, false otherwise.
 *         - second : the minimum number of refueling stops needed 
 *                    (undefined if canReach == false).
 */
std::pair<bool, int> minimumGasStations(std::size_t santa_monica_distance, 
    const std::vector<std::size_t>& gas_stations, std::size_t p) {
    // create a vector include USC and Santa Monica
    std::vector<std::size_t> d;
    d.push_back(0); // USC
    d.insert(d.end(), gas_stations.begin(), gas_stations.end());
    d.push_back(santa_monica_distance); // Santa Monica

    std::size_t N = d.size();  // n = N - 2
    std::size_t i = 0; // Current index position
    std::size_t stops = 0; // result

    while(true) {
        std::size_t j = i;
        // go as far as possible within the current fuel range
        while(j + 1 < N && d[j + 1] - d[i] <= p) j++;
        if(j == i) return {false, -1};
        if(j == N - 1) return {true, stops};
        stops++;
        i = j;
    }
}

int main() {
    // USC to Santa Monica distance = 25
    // p = 10
    //gas stations: 4, 7, 12, 18, 21
    std::vector<std::size_t> stations = {4, 7, 12, 18, 21};
    auto p = minimumGasStations(25, stations, 10);
    if(p.first) std::cout << "min stops: " << p.second << std::endl;
    else std::cerr << "we cannot make it" << std::endl;
    return 0;
}