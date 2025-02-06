#ifndef RUN_INFOMAP_H
#define RUN_INFOMAP_H

#include <stdint.h>

typedef double float64_t;

// Define options (for future extension)
enum InfomapOptions : int64_t {
    DEFAULT_MODE = 0
};

#ifdef __cplusplus
extern "C" {
#endif

// Infomap clustering function wrapper.
// Inputs:
//   - src, dst: arrays representing the edge list of the graph.
//   - NumEdges: number of edges (length of src and dst arrays).
//   - NumNodes: number of nodes in the graph.
//   - options: additional options for Infomap (currently not used).
//   - resolution: a parameter for clustering (if needed).
//   - communities: output array to hold the community assignment for each node.
void run_infomap(
    const int64_t src[], 
    const int64_t dst[], 
    int64_t NumEdges, 
    int64_t NumNodes, 
    int64_t options, 
    float64_t resolution, 
    int64_t communities[]
);

// C wrapper for Chapel integration.
// Returns 0 as a dummy value.
int64_t c_runInfomap(
    const int64_t src[], 
    const int64_t dst[], 
    int64_t NumEdges, 
    int64_t NumNodes, 
    int64_t options, 
    float64_t resolution, 
    int64_t communities[]
);

#ifdef __cplusplus
}
#endif

#endif // RUN_INFOMAP_H
