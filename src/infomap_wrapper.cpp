#include <iostream>
#include "run_infomap.h"

int main() {
    std::cout << "Testing Infomap clustering wrapper..." << std::endl;
    
    // Example edge list for a small graph.
    int64_t src[] = {0, 1, 2, 3, 4, 5};
    int64_t dst[] = {1, 2, 3, 4, 5, 0};
    int64_t NumEdges = sizeof(src) / sizeof(src[0]);
    int64_t NumNodes = 6;
    int64_t communities[NumNodes];

    // Use default options and resolution.
    int64_t options = DEFAULT_MODE;
    float64_t resolution = 0.1;

    // Call the C wrapper
    c_runInfomap(src, dst, NumEdges, NumNodes, options, resolution, communities);

    // Print community assignments.
    std::cout << "Community assignments:" << std::endl;
    for (int64_t i = 0; i < NumNodes; i++) {
        std::cout << "Node " << i << " -> Community " << communities[i] << std::endl;
    }

    return 0;
}

