#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sht.h"


#define UUID_STR_LEN 40
/* b2609a90-1f0f-11e7-9938-419a253c5e53 - 36 characters excluding null terminator */

char example_uuid[][UUID_STR_LEN] = {
  "61edf266-0d34-11e7-996b-addd4f48de07",
  "bc29b1d4-1fd6-11e7-9643-b1cb1e494b41",
  "2b5ce2b2-1f4e-11e7-9643-b1cb1e494b41",
  "71b18b8e-0dd1-11e7-996b-addd4f48de07",
  "b2609a90-1f0f-11e7-9938-419a253c5e53",
  "9bd006bc-0547-11e7-8cb3-9f373ae1b20a",
  "2b026936-1fc6-11e7-9643-b1cb1e494b41",
  "ce50fa22-1fd9-11e7-9643-b1cb1e494b41",
  "b2607da8-1f0f-11e7-9938-419a253c5e53",
  "54b53f1e-1fd1-11e7-9643-b1cb1e494b41",
  "54b574ca-1fd1-11e7-9643-b1cb1e494b41",
  "bc29a626-1fd6-11e7-9643-b1cb1e494b41"
};

typedef struct http_cm {
  u32 http_port_glid_drop;
  u32 http_blacklist_drop;
  u32 http_tcp_auth_drop;
  u32 http_src_base_glid_drop;
  u32 http_tcp_service_drop;
  u32 http_auth_drop;
  u32 http_service_drop;
} http_cm_t;

int num_uuids = sizeof(example_uuid)/sizeof(example_uuid[0]);

int main(int argc, char *argv[])
{
  int i;
  u32 num_buckets;
  int values[num_uuids];
  sht_t *t = NULL;
  void *val;
  http_cm_t *cm_p;

  printf("%d UUIDs\n", num_uuids);

  printf("simple hash table:\n  alloc: %u, free: %u\n", g_sht.mem_alloc, g_sht.mem_free);

  num_buckets = num_uuids/3;
  printf(" num_buckets=%u", num_buckets);
  t = sht_alloc(num_buckets);
  
  for (i = 0; i < num_uuids; i++) {
    values[i] = i+100;
    cm_p = (http_cm_t *) malloc(sizeof(http_cm_t));
    memset(cm_p, 0, sizeof(http_cm_t));
    cm_p->http_auth_drop = values[i];
    printf("adding uuid %s with val %u\n", example_uuid[i], values[i]);
    //sht_insert_with_str(t, example_uuid[i], (void *) &values[i]);
    sht_insert_with_str(t, example_uuid[i], (void *) cm_p);
  }

  for (i = 0; i < num_uuids; i++) {
    void *env;
    //sht_visit_print_str(env, example_uuid[i], (void *) &values[i]);
    sht_visit_print_str(env, example_uuid[i], sht_find_with_str(t, example_uuid[i]));
  }

  for (i = 0; i < num_uuids; i++) {
    int v;
    values[i] = i+100;
    printf("find uuid %s - ", example_uuid[i]);
    val = sht_find_with_str(t, example_uuid[i]);
    //printf("val = 0x%llu", (u64) val);
    cm_p = (http_cm_t *)val;
    // v = *(u32 *)val;
    v = cm_p->http_auth_drop;
    printf("val = %u\n", v);
  }
}

