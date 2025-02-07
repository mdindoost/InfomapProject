#ifndef INFOMAP_WRAPPER_H
#define INFOMAP_WRAPPER_H

#include <vector>
#include <string>

struct InfomapParams {
    InfomapParams() :
        num_trials(1),
        markov_time(1.0),
        random_seed(123),
        directed(false),
        use_weights(false),
        max_iterations(500),
        threshold(1e-10),
        hierarchical(false),
        num_threads(1),
        two_level(true),
        flow_model("undirected"),
        silent(false) {}

    int num_trials;
    double markov_time;
    int random_seed;
    bool directed;
    bool use_weights;
    int max_iterations;
    double threshold;
    bool hierarchical;
    int num_threads;
    bool two_level;
    std::string flow_model;
    bool silent;
};

struct InfomapResult {
    // Basic clustering results
    std::vector<int> cluster_assignments;
    int num_clusters;
    double codelength;
    bool success;
    std::string error_message;

    // Additional metrics
    double one_level_codelength;      // Codelength without modular structure
    double relative_codelength_saved; // How much better is the solution compared to one-level
    double entropy_rate;              // Network entropy rate
    double total_flow;               // Total flow in the network
    int num_nodes;                   // Total number of nodes
    int num_links;                   // Total number of links
    std::vector<int> module_sizes;   // Size of each module

    // Hierarchical information
    bool has_hierarchy;
    int num_levels;
    std::vector<double> level_codelengths;
    std::vector<int> level_sizes;
    
    // Validation flags
    bool is_network_connected;
    bool convergence_achieved;
    int iterations_performed;
};

InfomapResult run_Infomap(
    const std::vector<int>& src,
    const std::vector<int>& dst,
    const int num_nodes,
    const InfomapParams& params = InfomapParams()
);

#endif