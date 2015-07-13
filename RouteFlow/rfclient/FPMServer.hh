#ifndef RFCLIENT_FPMSERVER_H_
#define RFCLIENT_FPMSERVER_H_

#include "fpm.h"
#include "FlowTable.hh"

class FPMServer {
    public:
        FPMServer(FlowTable *ft);
        void operator()();

    private:
        FlowTable *table;
        int server_sock;
        int sock;

        int create_listen_sock(int port, int* sock_p);
        int accept_conn(int listen_sock);
        void fpm_serve();
        void print_nhlfe(const nhlfe_msg_t *msg);
        fpm_msg_hdr_t* read_fpm_msg (char* buf, size_t buf_len);
        void process_fpm_msg(fpm_msg_hdr_t* hdr);
};

#endif /* RFCLIENT_FPMSERVER_H_ */
