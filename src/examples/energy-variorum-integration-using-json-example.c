// Copyright 2019-2023 Lawrence Livermore National Security, LLC and other
// Variorum Project Developers. See the top-level LICENSE file for details.
//
// SPDX-License-Identifier: MIT

#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <variorum.h>
#include <variorum_topology.h>

#ifdef SECOND_RUN
static inline double do_work(int input)
{
    int i;
    double result = (double)input;

    for (i = 0; i < 100000; i++)
    {
        result += i * result;
    }

    return result;
}
#endif

void parse_json_energy_obj(char *s, int num_sockets)
{

    const char *hostname = NULL;
    json_t *node_obj = NULL;
    json_t *energy_obj = json_loads(s, JSON_DECODE_ANY, NULL);
    void *iter = json_object_iter(energy_obj);

    /* This is tailored to the nested structure that we have created (see docs). */
    /* Just for the first level, we use the iterator to obtain the hostname,
     * as this is encoded as a key to reduce verbosity. */

    while (iter)
    {
        hostname = json_object_iter_key(iter);
        node_obj = json_object_iter_value(iter);
        if (node_obj == NULL)
        {
            printf("JSON object not found");
            exit(0);
        }
        /* The following should return NULL after the first call per our object. */
        iter = json_object_iter_next(energy_obj, iter);
    }

    uint64_t timestamp;

    //  Extract node-levels value from node object
    timestamp = json_integer_value(json_object_get(node_obj, "timestamp"));

    printf("Hostname: %s\n", hostname);
    printf("Timestamp: %lu\n", timestamp);

    // If we're on a GPU-only build, we don't have energy_node_joules.
    if (json_object_get(node_obj, "energy_node_joules") != NULL)
    {
        uint64_t  energy_node;
        energy_node = json_integer_value(json_object_get(node_obj,
                                         "energy_node_joules"));
        printf("Node Energy: %lu Joules\n", energy_node);
    }

    // Clean up memory.
    json_decref(energy_obj);
}


int main(void)
{
    int ret;
    int num_sockets = 0;
    char *s = NULL;
#ifdef SECOND_RUN
    int i;
    int size = 1E4;
    volatile double x = 0.0;
#endif

    /* Determine number of sockets */
    num_sockets = variorum_get_num_sockets();
    if (num_sockets <= 0)
    {
        printf("HWLOC returned an invalid number of sockets. Exiting.\n");
        exit(-1);
    }

    ret = variorum_get_energy_json(&s);
    if (ret != 0)
    {
        printf("First run: JSON get node energy failed!\n");
        free(s);
        exit(-1);
    }

    /* Print the entire JSON object and then the parsed JSON object */
    printf("\n*****JSON object received from first run is: \n");
    puts(s);
    parse_json_energy_obj(s, num_sockets);

#ifdef SECOND_RUN
    for (i = 0; i < size; i++)
    {
        x += do_work(i);
    }
    printf("Final result: %f\n", x);

    ret = variorum_get_energy_json(&s);
    if (ret != 0)
    {
        printf("Second run: JSON get node energy failed!\n");
        free(s);
        exit(-1);
    }

    printf("\n*****JSON object received from second run is: \n");
    puts(s);
    parse_json_energy_obj(s, num_sockets);
#endif

    /* Deallocate the string */
    free(s);

    return ret;
}
