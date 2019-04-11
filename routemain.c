/**********************************************************
 * main.c
 * Description: nat route module source code
 *
 * Copyright 2019  oracleloyal
 *
 * Create : zhaoxi
 *
 * Modify :
 *
 ***********************************************************/
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route.h"
#include"common/hashmap.h"
#include "mini/mini-parser.h"
#include"common/common.h"
#include"list/list.h"
#define TEST 1
map_t NetInterfaceMap; //
typedef struct ValueMap {
	in6_addr routeaddr;
	char InterfaceNAme[24];
	in6_addr saddr;
	char key[10];
} ValueMap;

void itoa(int n, char s[]) {
	int i, j, sign;
	if ((sign = n) < 0) 
		n = -n; 
	i = 0;
	do {
		s[i++] = n % 10 + '0'; 
	} while ((n /= 10) > 0); 
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	for (j = i; j >= 0; j--) 
	{

	}
}
void Init() {
	NetInterfaceMap = hashmap_new(10);
}
/*
 *Function des:更新路由表，创建id映射的hash表
 */
int InitRoute(RouterTrie *route, MiniFile *data) {
	assert(route!=NULL && data!=NULL);
	Section *sec;
	int num = 0;
	Input default_gateway_input;
	Input *address;

	for (sec = data->section; sec != NULL; sec = sec->next) {
		//	num++;
		printf("UpdateRouteMap ****************session :%s**************************\n",sec->name);
		SectionData *sdata;
		/*
		 * add default route
		 */
		if (strcmp(sec->name, "def") == 0) {
			for (sdata = sec->data; sdata != NULL; sdata = sdata->next) {
				default_gateway_input = rt_create_default_gateway_input(
						rt_convert_string_to_address(sdata->key), 0);
				rt_default_gateway(route, &default_gateway_input);
				ValueMap *value = malloc(sizeof(ValueMap));
				strncpy(value->InterfaceNAme, "def", 4);
				value->routeaddr = rt_convert_address_to_in6_addr(
						default_gateway_input.address);
				strncpy(value->InterfaceNAme, sdata->value, 24);
				itoa(0, value->key);
				hashmap_put(NetInterfaceMap, value->key, value);

#ifdef TEST
				ValueMap *val;
				int ret = hashmap_get(NetInterfaceMap, value->key,
						(void**) (&val));
				if (ret == 0) {
					printf("Find key:%s interface name:%s\n", value->key,
							value->InterfaceNAme);
				} else {
					printf("Not find key\n");
				}
				char buff[128] = { "\0" };
				if (inet_ntop(AF_INET6, &value->routeaddr, buff, 128) == NULL) {
					perror("Could not convert IP address to string");
					exit(-1);
				} else {
					printf("********Get Ipv6 route:%s\n", buff);
				}
#endif

			}
		} else { //add muti net interface route
			for (sdata = sec->data; sdata != NULL; sdata = sdata->next) {

				char *pos = search(sdata->key, "addr");
				if (pos) {
					printf("addr type UpdateRouteMap Get Key Value:%s\n",
							sdata->value);

				} else {
					++num;
					printf(
						"UpdateRouteMap UpdateRouteMap************session:%s,key:%s,prefix:%d,interface index:%d\n",
							sec->name, sdata->key, atoi(sdata->value), num);
					address = (Input*) malloc(sizeof(Input));
					address->prefix_length = atoi(sdata->value);
					address->interface = num;
					address->next_hop = rt_convert_string_to_address("::1"); //should add net gatway
					address->address = rt_convert_string_to_address(sdata->key);
					rt_insert(route, address);

					ValueMap *value = (ValueMap*) malloc(sizeof(ValueMap));
					strncpy(value->InterfaceNAme, sec->name, strlen(sec->name));
					value->routeaddr = rt_convert_address_to_in6_addr(
							address->address);
					itoa(num, value->key);
					hashmap_put(NetInterfaceMap, value->key, value);
//test
#ifdef TEST
					ValueMap *val;
					int ret = hashmap_get(NetInterfaceMap, value->key,
							(void**) (&val));
					if (ret == 0) {
						printf("Find key:%s interface name:%s\n", value->key,
								value->InterfaceNAme);
					} else {
						printf("Not find key\n");
					}
					char buff[128] = { "\0" };
					if (inet_ntop(AF_INET6, &value->routeaddr, buff,
							128) == NULL) {
						perror("Could not convert IP address to string");
						exit(-1);
					} else {
						printf("********Get Ipv6 route:%s\n", buff);
					}
#endif
				}

			}
		}

	}
	return 0;
}

int UpdateSourceAddr(RouterTrie *route, MiniFile *data) {
	printf("\n**********UpdateSourceAddr function into *****************\n ");
	assert(route!=NULL && data!=NULL);
	Section *sec;
	int num = 0;
	list_t *listall = list_new();
	for (sec = data->section; sec != NULL; sec = sec->next) {
		SectionData *sdata;
		/*
		 * add default route source addr
		 */

		if (strcmp(sec->name, "def") == 0) {
#if 0
			for (sdata = sec->data; sdata != NULL; sdata = sdata->next) {
				default_gateway_input = rt_create_default_gateway_input(
						rt_convert_string_to_address(sdata->key), 0);
				printf("default UpdateRouteMap session:%s,key:%s,value:%s\n", sec->name,
						sdata->key, sdata->value);
				rt_default_gateway(route, &default_gateway_input);
				ValueMap *value = malloc(sizeof(ValueMap));
				strncpy(value->InterfaceNAme, "def", 4);
				value->routeaddr = rt_convert_address_to_in6_addr(
						default_gateway_input.address);
				strncpy(value->InterfaceNAme, sdata->value, 24);
				itoa(0, value->key);
				hashmap_put(NetInterfaceMap, value->key, value);

#ifdef TEST
				ValueMap *val;
				int ret = hashmap_get(NetInterfaceMap, value->key,
						(void**) (&val));
				if (ret == 0) {
					printf("Find key:%s interface name:%s\n", value->key,
							value->InterfaceNAme);
				} else {
					printf("Not find key\n");
				}
				char buff[128] = {"\0"};
				if (inet_ntop(AF_INET6, &value->routeaddr, buff,
								128) == NULL) {
					perror("Could not convert IP address to string");
					exit(-1);
				} else {
					printf("********Get Ipv6 route:%s\n", buff);
				}
#endif
			}
#endif
		} else { //add muti net interface route
			list_t *list = list_new();
			for (sdata = sec->data; sdata != NULL; sdata = sdata->next) {

				char *pos = search(sdata->key, "addr");
				if (pos) {
					list_node_t *a = list_node_new(sdata->value);
					list_rpush(list, a);
					list_node_t *a1 = list_node_new(sdata->value);
					list_rpush(listall, a1);
#ifdef TEST
					printf("addr type UpdateRouteMap Get Key Value:%s\n",
							sdata->value);
#endif

				}
			}
			for (sdata = sec->data; sdata != NULL; sdata = sdata->next) {
				++num;
				list_iterator_t *it = list_iterator_new(list, LIST_HEAD);
				list_node_t *a = list_iterator_next(it);
				int max_len = 0;
				int index = 0;
				for (a; a != NULL; a = list_iterator_next(it)) {
					char *pos = search(sdata->key, "addr");
					if (pos) {
						continue;
					}
					if (a) {
						int slen = strlen(a->val);
						int dlen = strlen(sdata->key);
						int len = FindMaxSubstr(a->val, sdata->key);
						int lenstr = 0;
						lenstr = ((len == slen) ? 1 : 0);
						lenstr = (len == dlen ? 2 : 0);
						if (len > max_len && lenstr) {
							max_len = len;
							if (lenstr == 1) {
								char key[10] = { "\0" };
								ValueMap *val = NULL;
								itoa(num, key);
								int ret = hashmap_get(NetInterfaceMap, key,
										(void**) (&val));
								if (ret == 0) {								
									inet_pton(AF_INET6, (char *) sdata->key,
											&val->saddr);

								} else {
									printf("Not find key\n");
								}

							} else {
								char key[10] = { "\0" };
								ValueMap *val = NULL;
								itoa(num, key);
								int ret = hashmap_get(NetInterfaceMap, key,
										(void**) (&val));
								if (ret == 0) {
									
									inet_pton(AF_INET6, a->val, &val->saddr);
									char buff[128] = { "\0" };
									if (inet_ntop(AF_INET6, &val->saddr, buff,
											128) == NULL) {
										perror(
												" Could not convert IP address to string");
										exit(-1);
									} else {
										printf("match Ipv6 route:%s\n", buff);
									}
								} else {
									printf("Not find key\n");
								}
							}

						}

					}
				}
				list_iterator_destroy(it);

			}
			list_destroy(list);
		}

	}
	for (sec = data->section; sec != NULL; sec = sec->next) {
		//update def default saddr
		if (strcmp(sec->name, "def") == 0) {
			list_iterator_t *it = list_iterator_new(listall, LIST_HEAD);
			list_node_t *a = list_iterator_next(it);
			int max_len = 0;
			int index = 0;
			for (a; a != NULL; a = list_iterator_next(it)) {
				if (a) {
					char key[10] = { "\0" };
					ValueMap *val = NULL;
					itoa(0, key);
					int ret = hashmap_get(NetInterfaceMap, key,
							(void**) (&val));
					if (!val)
						break;
					if (ret == 0) {
						//寻找最匹配的IPv6地址
						char buff[128] = { "\0" };
						inet_ntop(AF_INET6, &val->routeaddr, buff, 128);
						memcpy(buff, sec->data->key, 128);
						int slen = strlen(a->val);
						int dlen = strlen(buff);

						char *buff1 = (char *) malloc(strlen(a->val));
						memcpy(buff1, a->val, strlen(a->val));

						int len = FindMaxSubstr(buff, buff1);
						int lenstr = 0;
						lenstr = ((len == slen) ? 1 : 0);
						lenstr = (len == dlen ? 2 : 0);
						if (len > max_len && lenstr) {
							max_len = len;
							if (lenstr == 1) {
								inet_pton(AF_INET6, (char *) buff, &val->saddr);
								printf("type 1: max match adress:%s\n", buff);
							} else {
								inet_pton(AF_INET6, (char *) a->val,
										&val->saddr);
								printf("type 2: max match adress:%s\n", a->val);
							}

						}
					}
				}
			}
			list_iterator_destroy(it);
			list_destroy(listall);

			printf("Leave def\n");
		}
	}
	printf("\n**********UpdateSourceAddr function leave *****************\n ");
	return 0;
}

int main(int argc, char **argv) {
	Input default_gateway_input;
	RouterTrie rt;
	default_gateway_input = rt_create_default_gateway_input(
			rt_convert_string_to_address("2001::1"), 10);

	rt_setup(&rt);
	rt_default_gateway(&rt, &default_gateway_input);
	MiniFile *mini_file;
	mini_file = mini_parse_file("route.ini");
	if (mini_file == NULL) {
		fprintf(stderr, "%s: Can't parse '%s' INI file!\n", argv[0], argv[1]);
		return -1;
	}
	Init();
	InitRoute(&rt, mini_file);
	UpdateSourceAddr(&rt, mini_file);
	{
	Input address;
	address.address = rt_convert_string_to_address("2400:a480:aaaa:200::100");
	const Entry* entry;
	entry = rt_match(&rt, &address.address);
	int Index = entry ? entry->interface : 0;
	printf("Address 2400:a480:aaaa:200::100 out  indexId:%d\n", entry ? entry->interface : 0);
	char key[10] = { "\0" };
	ValueMap *val = NULL;
	itoa(Index, key);
	int ret = hashmap_get(NetInterfaceMap, key, (void**) (&val));
	if (ret == 0) {
		char buff[128]={"\0"};
		inet_ntop(AF_INET6,  &val->saddr, buff, 128);
		char buff1[128]={"\0"};
		inet_ntop(AF_INET6,&val->routeaddr, buff1, 128);
        printf("find Out dev :%s saddr adress:%s\n",val->InterfaceNAme,buff);
	}
	}
	{
		  Input address;
			address.address = rt_convert_string_to_address("ff::2");
			const Entry* entry;
			entry = rt_match(&rt, &address.address);
			int Index = entry ? entry->interface : 0;
			printf("Address ff::2 out  indexId:%d\n", entry ? entry->interface : 0);
		//find interface src addr
			char key[10] = { "\0" };
			ValueMap *val = NULL;
			itoa(Index, key);
			int ret = hashmap_get(NetInterfaceMap, key, (void**) (&val));
			if (ret == 0) {
				char buff[128]={"\0"};
				inet_ntop(AF_INET6,  &val->saddr, buff, 128);
				char buff1[128]={"\0"};
				inet_ntop(AF_INET6,&val->routeaddr, buff1, 128);
		        printf("find Out dev :%s saddr adress:%s\n",val->InterfaceNAme,buff);
			}
	}

	return 0;
}
