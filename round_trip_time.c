#include <stdio.h>
#include <stdlib.h>

#include "round_trip_time.h"

struct RoundTripTime {
    int src;
    int dest;
    double rtt;
};

RoundTripTime *round_trip_time_construct(int src, int dest, double rtt) {
    RoundTripTime *round_trip_time = malloc(sizeof(RoundTripTime));
    round_trip_time->src = src;
    round_trip_time->dest = dest;
    round_trip_time->rtt = rtt;
    return round_trip_time;
}

void round_trip_time_destruct(RoundTripTime *round_trip_time) {
    free(round_trip_time);
}

int round_trip_time_get_src(RoundTripTime *round_trip_time) {
    return round_trip_time->src;
}

int round_trip_time_get_dest(RoundTripTime *round_trip_time) {
    return round_trip_time->dest;
}

double round_trip_time_get_rtt(RoundTripTime *round_trip_time) {
    return round_trip_time->rtt;
}