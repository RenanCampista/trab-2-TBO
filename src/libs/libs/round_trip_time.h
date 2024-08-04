#if !defined(_ROUND_TRIP_TIME_H_)
#define _ROUND_TRIP_TIME_H_

typedef struct RoundTripTime RoundTripTime;

RoundTripTime *round_trip_time_construct(int src, int dest, long double rtt);

void round_trip_time_destruct(RoundTripTime *round_trip_time);

int round_trip_time_get_src(RoundTripTime *round_trip_time);

int round_trip_time_get_dest(RoundTripTime *round_trip_time);

long double round_trip_time_get_rtt(RoundTripTime *round_trip_time);

int round_trip_compare(const void *a, const void *b);

#endif // _ROUND_TRIP_TIME_H_
