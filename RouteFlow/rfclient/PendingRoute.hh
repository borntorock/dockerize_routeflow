#ifndef PENDING_ROUTE_HH
#define PENDING_ROUTE_HH

#include <boost/thread/thread_time.hpp>

#include "defs.h"
#include "RouteEntry.hh"

/**
 * A PendingRoute consists of a type (insert/mod/delete), an entry describing
 * the route, and a time that we expect this route to be handled. Initially,
 * a pendingRoute expects to be handled immediately. This can be modified by
 * calling advance().
 */
class PendingRoute {
    public:
        RouteModType type;
        RouteEntry rentry;
        boost::system_time time;

        PendingRoute() { }

        PendingRoute(RouteModType rmt, const RouteEntry& re) {
            type = rmt;
            rentry = re;
            time = boost::get_system_time();
        }

        PendingRoute(const PendingRoute& other) {
            this->type = other.type;
            this->rentry = other.rentry;
            this->time = other.time;
        }

        /* Advance the time for this route to be handled, to the current time
         * plus the given number of milliseconds. */
        void advance(unsigned int milliseconds) {
            time = boost::get_system_time()
                   + boost::posix_time::milliseconds(milliseconds);
        }
};

#endif /* PENDING_ROUTE_HH */
