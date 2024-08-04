#include <stdio.h>
#include <stdlib.h>

#include "../libs/round_trip_time.h"

struct RoundTripTime {
    int src;
    int dest;
    long double rtt;
};

RoundTripTime *round_trip_time_construct(int src, int dest, long double rtt) {
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

long double round_trip_time_get_rtt(RoundTripTime *round_trip_time) {
    return round_trip_time->rtt;
}

int round_trip_compare(const void *a, const void *b) {
    RoundTripTime *round_trip_time_a = *(RoundTripTime **)a;
    RoundTripTime *round_trip_time_b = *(RoundTripTime **)b;
    if (round_trip_time_a->rtt < round_trip_time_b->rtt)        return -1;
    else if (round_trip_time_a->rtt > round_trip_time_b->rtt)   return 1;
    else                                                        return 0;
}