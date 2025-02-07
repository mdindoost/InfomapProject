#include "../include/infomap_wrapper.h"
#include "../extern/infomap/src/Infomap.h"
#include "../extern/infomap/src/io/Config.h"
#include "../extern/infomap/src/io/Network.h"
#include <memory>
#include <set>
#include <algorithm>

InfomapResult run_Infomap(
    const std::vector<int>& src,
    const std::vector<int>& dst,
    const int num_nodes,
    const InfomapParams& params) {
    
    InfomapResult result;
    result.success = false;

    try {
        // Input validation
        if (src.empty() || dst.empty()) {
            throw std::runtime_error("Empty input vectors");
        }
        if (src.size() != dst.size()) {
            throw std::runtime_error("Source and destination vectors must have same size");
        }
        if (num_nodes <= 0) {
            throw std::runtime_error("Number of nodes must be positive");
        }

        // Check for invalid node IDs
        for (size_t i = 0; i < src.size(); ++i) {
            if (src[i] < 0 || src[i] >= num_nodes || dst[i] < 0 || dst[i] >= num_nodes) {
                throw std::runtime_error("Invalid node ID found");
            }
        }

        // Create InfomapBase instance
        infomap::InfomapBase infomap;
        
        // Set parameters
        infomap.numTrials = params.num_trials;
        infomap.markovTime = params.markov_time;
        infomap.directed = params.directed;
        infomap.twoLevel = params.two_level;
        infomap.silent = params.silent;
        
        // Add edges to network
        auto& network = infomap.network();
        for (size_t i = 0; i < src.size(); ++i) {
            network.addLink(src[i], dst[i]);
        }

        // Run Infomap
        infomap.run();
        
        // Set basic results
        result.cluster_assignments.resize(num_nodes);
        result.num_clusters = 0;
        
        // Get leaf node clustering
        std::vector<int> module_counts;
        for (auto it = infomap.iterLeafNodes(); it != infomap.end(); ++it) {
            int nodeId = it->physicalId;
            int moduleId = it->parent ? it->parent->index : 0;
            if (nodeId < num_nodes) {
                result.cluster_assignments[nodeId] = moduleId;
                result.num_clusters = std::max(result.num_clusters, moduleId + 1);
                
                // Expand module_counts if needed
                if (moduleId >= static_cast<int>(module_counts.size())) {
                    module_counts.resize(moduleId + 1, 0);
                }
                module_counts[moduleId]++;
            }
        }
        
        // Set module sizes
        result.module_sizes = std::move(module_counts);
        
        // Set network statistics
        result.num_nodes = num_nodes;
        result.num_links = src.size();
        result.codelength = infomap.codelength();
        result.one_level_codelength = infomap.getOneLevelCodelength();
        result.relative_codelength_saved = infomap.getRelativeCodelengthSavings();
        
        // Set hierarchical information
        if (params.hierarchical) {
            result.has_hierarchy = true;
            result.num_levels = infomap.numLevels();
            result.level_sizes.push_back(infomap.numTopModules());
            result.level_codelengths.push_back(infomap.codelength());
        }
        
        // Check network connectivity (basic check)
        std::set<int> reachable_nodes;
        for (size_t i = 0; i < src.size(); ++i) {
            reachable_nodes.insert(src[i]);
            reachable_nodes.insert(dst[i]);
        }
        result.is_network_connected = (reachable_nodes.size() == static_cast<size_t>(num_nodes));
        
        result.success = true;
        
    } catch (const std::exception& e) {
        result.success = false;
        result.error_message = e.what();
    }
    
    return result;
}