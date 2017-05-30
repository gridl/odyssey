#ifndef OD_BACKEND_H
#define OD_BACKEND_H

/*
 * odissey.
 *
 * PostgreSQL connection pooler and request router.
*/

od_server_t*
od_backend_new(od_router_t*, od_route_t*);

int od_backend_reset(od_server_t*);
int od_backend_ready(od_server_t*, uint8_t*, int);
int od_backend_configure(od_server_t*, so_bestartup_t*);

#endif /* OD_BACKEND_H */