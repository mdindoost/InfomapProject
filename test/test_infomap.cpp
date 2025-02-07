#include "../include/infomap_wrapper.h"
#include <iostream>
#include <vector>
#include <iomanip>

void print_result(const InfomapResult& result) {
    if (!result.success) {
        std::cout << "Clustering failed: " << result.error_message << "\n";
        return;
    }

    std::cout << "============= Clustering Results =============\n";
    std::cout << "Basic Information:\n";
    std::cout << "  Number of nodes: " << result.num_nodes << "\n";
    std::cout << "  Number of links: " << result.num_links << "\n";
    std::cout << "  Number of clusters: " << result.num_clusters << "\n";
    
    std::cout << "\nQuality Metrics:\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "  Codelength: " << result.codelength << "\n";
    std::cout << "  One-level codelength: " << result.one_level_codelength << "\n";
    std::cout << "  Compression: " << result.relative_codelength_saved * 100 << "%\n";
    
    std::cout << "\nCluster Sizes:\n";
    for (size_t i = 0; i < result.module_sizes.size(); ++i) {
        std::cout << "  Cluster " << i << ": " << result.module_sizes[i] << " nodes\n";
    }
    
    std::cout << "\nNetwork Properties:\n";
    std::cout << "  Network is " << (result.is_network_connected ? "connected" : "disconnected") << "\n";
    
    if (result.has_hierarchy) {
        std::cout << "\nHierarchical Information:\n";
        std::cout << "  Number of levels: " << result.num_levels << "\n";
        for (size_t i = 0; i < result.level_codelengths.size(); ++i) {
            std::cout << "  Level " << i << " codelength: " << result.level_codelengths[i] << "\n";
        }
    }
    
    std::cout << "\nNode Assignments:\n";
    for (size_t i = 0; i < result.cluster_assignments.size(); ++i) {
        std::cout << "  Node " << i << " -> Cluster " << result.cluster_assignments[i] << "\n";
    }
    std::cout << "===========================================\n";
}

int main() {
    // Test graph
    std::vector<int> src = {0, 0, 1, 2};
    std::vector<int> dst = {1, 2, 2, 0};
    int num_nodes = 3;

    // Create parameters with default values
    InfomapParams params;
    params.hierarchical = true;  // Enable hierarchical analysis
    
    // Run Infomap
    InfomapResult result = run_Infomap(src, dst, num_nodes, params);
    
    // Print detailed results
    print_result(result);

    return 0;
}